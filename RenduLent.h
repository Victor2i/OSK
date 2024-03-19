#pragma once
#include "BufferImage.h"
#include "BitmapFont.h"
#include <stdint.h>

struct Point{
	long X;
	long Y;
};

class RenduLent{
	public:
	RenduLent(Framebuffer* NewTargetFramebuffer, FNT1_FONT* NewFNT1Font);
	Point CursorPosition;
	Framebuffer* TargetFramebuffer;
	FNT1_FONT* FNT1Font;
    uint32_t MouseCursorBuffer[16 * 16];
    uint32_t MouseCursorBufferAfter[16 * 16];
	unsigned int Color;
	unsigned int ClearColor;
	unsigned int Mouse1Color;
	unsigned int Mouse2Color;
	void CharPrint(unsigned char chr, unsigned int OffsetX, unsigned int OffsetY);
	void CharPrint(unsigned char chr);
	void PrintPix(uint32_t x, uint32_t y, uint32_t color);
    uint32_t GetPix(uint32_t x, uint32_t y);
	void ClearChar();
	void Print(const char* str);
	void Clear();
	void NewLine();
	void DrawOverlayMouseCursor(uint8_t* mouseCursor, Point position, uint32_t color);
    void ClearMouseCursor(uint8_t* mouseCursor, Point position);
    bool MouseDrawn;
};

extern RenduLent* RenduGlobal;