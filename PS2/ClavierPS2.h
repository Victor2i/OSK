#pragma once
#include <stdint.h>
#include "ScancodesClavier.h"
#include "../Hardware/IO.h"
#include "../RenduLent.h"

void ClavierACK(void);
void ClavierLED(uint8_t LEDStatus);
void ClavierLEDUpdate(void);
void HandleKeyboard(uint8_t scancode);