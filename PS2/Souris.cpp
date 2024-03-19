#include "Souris.h"

void MouseWait(){
    uint64_t Timeout = 100000;
    while (Timeout--){
        if ((InByte(0x64) & 0b10) == 0){
            return;
        }
    }
}

void MouseWaitInput(){
    uint64_t Timeout = 100000;
    while (Timeout--){
        if (InByte(0x64) & 0b1){
            return;
        }
    }
}

void MouseWrite(uint8_t Value){
    MouseWait();
    OutByte(0x64, 0xD4);
    MouseWait();
    OutByte(0x60, Value);
}

uint8_t MouseRead(){
    MouseWaitInput();
    return InByte(0x60);
}

uint8_t MouseCycle = 0;
uint8_t MousePacket[4];
bool MousePacketReady = false;
Point MousePosition;
Point MousePositionOld;

void HandleMouse(uint8_t Data){
	ProcessMousePacket();
    static bool Skip = true;
    if (Skip) { Skip = false; return; }

    switch(MouseCycle){
        case 0:
            if ((Data & 0b00001000) == 0) break;
            MousePacket[0] = Data;
            MouseCycle++;
            break;
        case 1:
            MousePacket[1] = Data;
            MouseCycle++;
            break;
        case 2:
            MousePacket[2] = Data;
            MousePacketReady = true;
            MouseCycle = 0;
            break;
    }
}

void ProcessMousePacket(){
    if (!MousePacketReady) return;

        bool XNegative, YNegative, XOverflow, YOverflow;

        if (MousePacket[0] & MouseXSign){
            XNegative = true;
        }else XNegative = false;

        if (MousePacket[0] & MouseYSign){
            YNegative = true;
        }else YNegative = false;

        if (MousePacket[0] & MouseXOverflow){
            XOverflow = true;
        }else XOverflow = false;

        if (MousePacket[0] & MouseYOverflow){
            YOverflow = true;
        }else YOverflow = false;

        if (!XNegative){
            MousePosition.X += MousePacket[1];
            if (XOverflow){
                MousePosition.X += 255;
            }
        } else
        {
            MousePacket[1] = 256 - MousePacket[1];
            MousePosition.X -= MousePacket[1];
            if (XOverflow){
                MousePosition.X -= 255;
            }
        }

        if (!YNegative){
            MousePosition.Y -= MousePacket[2];
            if (YOverflow){
                MousePosition.Y -= 255;
            }
        } else
        {
            MousePacket[2] = 256 - MousePacket[2];
            MousePosition.Y += MousePacket[2];
            if (YOverflow){
                MousePosition.Y += 255;
            }
        }

        if (MousePosition.X < 0) MousePosition.X = 0;
        if (MousePosition.X > RenduGlobal->TargetFramebuffer->Width-1) MousePosition.X = RenduGlobal->TargetFramebuffer->Width-1;
        
        if (MousePosition.Y < 0) MousePosition.Y = 0;
        if (MousePosition.Y > RenduGlobal->TargetFramebuffer->Height-1) MousePosition.Y = RenduGlobal->TargetFramebuffer->Height-1;
        
        RenduGlobal->ClearMouseCursor(MousePointer, MousePositionOld);
        RenduGlobal->DrawOverlayMouseCursor(MousePointer, MousePosition, 0xffffffff);

        if (MousePacket[0] & MouseLeftbutton){
			uint32_t oldcolor = RenduGlobal->Color;
            RenduGlobal->Color = RenduGlobal->Mouse1Color;
			RenduGlobal->CharPrint(0x9B, MousePosition.X, MousePosition.Y);
			RenduGlobal->Color = oldcolor;
        }
        if (MousePacket[0] & MouseMiddlebutton){
            // je sais pas. lol
			// J'AI PAS D'IDEES POUR LE MIDDLE CLICK POUR LE MOMENT
        }
        if (MousePacket[0] & MouseRightbutton){
            uint32_t oldcolor = RenduGlobal->Color;
            RenduGlobal->Color = RenduGlobal->Mouse2Color;
            RenduGlobal->CharPrint(0x9B, MousePosition.X, MousePosition.Y);
            RenduGlobal->Color = oldcolor;
        }
    MousePacketReady = false;
    MousePositionOld = MousePosition;
}

void InitMouse(){
    OutByte(0x64, 0xA8);
    MouseWait();
    OutByte(0x64, 0x20);
    MouseWaitInput();
    uint8_t Status = InByte(0x60);
    Status |= 0b10;
    MouseWait();
    OutByte(0x64, 0x60);
    MouseWait();
    OutByte(0x60, Status);
    MouseWrite(0xF6);
    MouseRead();
    MouseWrite(0xF4);
    MouseRead();
	MousePosition = {(RenduGlobal->TargetFramebuffer->Width / 2),(RenduGlobal->TargetFramebuffer->Height / 2)};
}