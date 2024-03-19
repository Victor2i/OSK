#pragma once
#include "../Hardware/IO.h"
#include "../RenduLent.h"

#define MouseLeftbutton 0b00000001
#define MouseRightbutton 0b00000010
#define MouseMiddlebutton 0b00000100
#define MouseXSign 0b00010000
#define MouseYSign 0b00100000
#define MouseXOverflow 0b01000000
#define MouseYOverflow 0b10000000

extern uint8_t MousePointer[];

void InitMouse();
void HandleMouse(uint8_t Data);
void ProcessMousePacket();
extern Point MousePosition;