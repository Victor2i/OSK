#include "HexDisplay.h"

void DisplayMemory(uint64_t Address){
	uint16_t Line, MaxLines;
	uint8_t ReadByte;
	uint8_t* AddrPtr;
	AddrPtr = (uint8_t*)Address;
	
	Line = 0;
	MaxLines = ((RenduGlobal->TargetFramebuffer->Height - (RenduGlobal->TargetFramebuffer->Height % 16)) / 16 - 2);
	
	RenduGlobal->Clear();
	
	while (Line < MaxLines){
		RenduGlobal->CursorPosition = {(((RenduGlobal->TargetFramebuffer->Width - (RenduGlobal->TargetFramebuffer->Width % 8)) / 8 / 2 - 102 / 2) * 8),(16 * (Line + 1))};
		RenduGlobal->Print(ToHexString(Address));
		RenduGlobal->Print(" - ");
		for (uint8_t i = 1; i <= 16; i++){
			ReadByte = *AddrPtr;
			RenduGlobal->Print(ToHexString(ReadByte));
			RenduGlobal->Print(" ");
			AddrPtr++;
		}
		RenduGlobal->Print("- ");
		AddrPtr -= 0x10;
		for (uint8_t i = 1; i <= 16; i++){
			ReadByte = *AddrPtr;
			RenduGlobal->CharPrint(ReadByte);
			RenduGlobal->Print(" ");
			AddrPtr++;
		}
		Address += 0x10;
		Line++;
	}
}