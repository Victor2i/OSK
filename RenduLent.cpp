#include "RenduLent.h"

RenduLent* RenduGlobal;

RenduLent::RenduLent(Framebuffer* NewTargetFramebuffer, FNT1_FONT* NewFNT1Font){
	TargetFramebuffer = NewTargetFramebuffer;
	FNT1Font = NewFNT1Font;
	Color = 0xFFFFFFFF;
	ClearColor = 0xFF000000;
	Mouse1Color = 0xFFFFFEFF;
	Mouse2Color = 0xFF000000;
	CursorPosition = {0, 0};
}

void RenduLent::PrintPix(uint32_t x, uint32_t y, uint32_t color){
	if (y < TargetFramebuffer->Height){
		if (x < TargetFramebuffer->Width){
			*(uint32_t*)((uint64_t)TargetFramebuffer->BaseAddress + (x*4) + (y * TargetFramebuffer->PixelsPerScanLine * 4)) = color;
		}
	}
}

uint32_t RenduLent::GetPix(uint32_t x, uint32_t y){
    if (y < TargetFramebuffer->Height){
		if (x < TargetFramebuffer->Width){
			return *(uint32_t*)((uint64_t)TargetFramebuffer->BaseAddress + (x*4) + (y * TargetFramebuffer->PixelsPerScanLine * 4));
		} else return 0x12345678;
	}
	else return 0x12345678;
}

void RenduLent::ClearMouseCursor(uint8_t* mouseCursor, Point position){
    if (!MouseDrawn) return;

    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8))))
            {
                if (GetPix(position.X + x, position.Y + y) == MouseCursorBufferAfter[x + y *16]){
                    PrintPix(position.X + x, position.Y + y, MouseCursorBuffer[x + y * 16]);
                }
            }
        }
    }
}

void RenduLent::DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color){
    int xMax = 16;
    int yMax = 16;
    int differenceX = TargetFramebuffer->Width - position.X;
    int differenceY = TargetFramebuffer->Height - position.Y;

    if (differenceX < 16) xMax = differenceX;
    if (differenceY < 16) yMax = differenceY;

    for (int y = 0; y < yMax; y++){
        for (int x = 0; x < xMax; x++){
            int bit = y * 16 + x;
            int byte = bit / 8;
            if ((mouseCursor[byte] & (0b10000000 >> (x % 8)))){
                MouseCursorBuffer[x + y * 16] = GetPix(position.X + x, position.Y + y);
                PrintPix(position.X + x, position.Y + y, color);
                MouseCursorBufferAfter[x + y * 16] = GetPix(position.X + x, position.Y + y);
            }
        }
    }
    MouseDrawn = true;
}

void RenduLent::CharPrint(unsigned char chr, unsigned int OffsetX, unsigned int OffsetY){
	unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
	char* fontPtr = (char*)FNT1Font->GlyphBuffer + (chr * FNT1Font->FNT1Header->CharSize);
	for (unsigned long y = OffsetY; y < OffsetY + 16; y++){
		for (unsigned long x = OffsetX; x < OffsetX + 8; x++){
			if ((*fontPtr & (0b10000000 >> (x - OffsetX))) > 0){
				if (y < (TargetFramebuffer->Height)){
					if (x < (TargetFramebuffer->Width)){
						*(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Color;
					}
				}
			}
		}
		fontPtr++;
	}
}

void RenduLent::CharPrint(unsigned char chr){
    CharPrint(chr, CursorPosition.X, CursorPosition.Y);
    CursorPosition.X += 8;
    if (CursorPosition.X + 8 > TargetFramebuffer->Width){
        CursorPosition.X = 0; 
        CursorPosition.Y += 16;
    }
}

void RenduLent::Print(const char* str){
	unsigned char* chr = (unsigned char*)str;
	while(*chr != 0){
		switch (*chr) {
			case 10:
				CursorPosition.Y += 16;
				break;
			case 13:
				CursorPosition.X = 0;
				break;
			default:
			CharPrint(*chr, CursorPosition.X, CursorPosition.Y);
			CursorPosition.X+=8;
			if(CursorPosition.X + 8 > TargetFramebuffer->Width){
				CursorPosition.X = 0;
				CursorPosition.Y += 16;
			}
		}
		chr++;
	}
}

void RenduLent::ClearChar(){
    if (CursorPosition.X == 0){
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }

    unsigned int xOff = CursorPosition.X;
    unsigned int yOff = CursorPosition.Y;

    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    for (unsigned long y = yOff; y < yOff + 16; y++){
        for (unsigned long x = xOff - 8; x < xOff; x++){
            *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = ClearColor;
        }
    }

    CursorPosition.X -= 8;

    if (CursorPosition.X < 0){
        CursorPosition.X = TargetFramebuffer->Width;
        CursorPosition.Y -= 16;
        if (CursorPosition.Y < 0) CursorPosition.Y = 0;
    }
}

void RenduLent::Clear(){
    uint64_t fbBase = (uint64_t)TargetFramebuffer->BaseAddress;
    uint64_t bytesPerScanline = TargetFramebuffer->PixelsPerScanLine * 4;
    uint64_t fbHeight = TargetFramebuffer->Height;
    uint64_t fbSize = TargetFramebuffer->BufferSize;

    for (int verticalScanline = 0; verticalScanline < fbHeight; verticalScanline ++){
        uint64_t pixPtrBase = fbBase + (bytesPerScanline * verticalScanline);
        for (uint32_t* pixPtr = (uint32_t*)pixPtrBase; pixPtr < (uint32_t*)(pixPtrBase + bytesPerScanline); pixPtr ++){
            *pixPtr = ClearColor;
        }
    }
}

void RenduLent::NewLine(){
    CursorPosition.X = 0;
    CursorPosition.Y += 16;
}