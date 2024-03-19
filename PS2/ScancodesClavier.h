#pragma once
#include <stdint.h>

namespace QWERTY_Keyboard{
	#define Escape 0x01
	#define Backspace 0x0E
	#define Tabulation 0x0F
	#define Enter 0x1C
	#define LeftControl 0x1D
    #define LeftShift 0x2A
    #define RightShift 0x36
	#define NumStar 0x37
	#define LeftAlt 0x38
    #define Spacebar 0x39
    #define CapsLock 0x3A
    #define Function1 0x3B
    #define Function2 0x3C
    #define Function3 0x3D
    #define Function4 0x3E
    #define Function5 0x3F
    #define Function6 0x40
    #define Function7 0x41
    #define Function8 0x42
    #define Function9 0x43
    #define Function10 0x44
    #define NumberLock 0x45
    #define ScrollLock 0x46
    #define Num7 0x47
    #define Num8 0x48
    #define Num9 0x49
	#define NumMinus 0x4A
	#define Num4 0x4B
	#define Num5 0x4C
	#define Num6 0x4D
	#define NumPlus 0x4E
	#define Num1 0x4F
	#define Num2 0x50
	#define Num3 0x51
	#define Num0 0x52
	#define NumDot 0x53
	#define Function11 0x57
	#define Function12 0x58

    extern const unsigned char QWERTY_Table[];
    char Translate(uint8_t scancode, bool uppercase);
}

namespace AZERTY_Keyboard{
    #define Escape 0x01
	#define Backspace 0x0E
	#define Tabulation 0x0F
	#define Enter 0x1C
	#define LeftControl 0x1D
    #define LeftShift 0x2A
    #define RightShift 0x36
	#define NumStar 0x37
	#define LeftAlt 0x38
    #define Spacebar 0x39
    #define CapsLock 0x3A
    #define Function1 0x3B
    #define Function2 0x3C
    #define Function3 0x3D
    #define Function4 0x3E
    #define Function5 0x3F
    #define Function6 0x40
    #define Function7 0x41
    #define Function8 0x42
    #define Function9 0x43
    #define Function10 0x44
    #define NumberLock 0x45
    #define ScrollLock 0x46
    #define Num7 0x47
    #define Num8 0x48
    #define Num9 0x49
	#define NumMinus 0x4A
	#define Num4 0x4B
	#define Num5 0x4C
	#define Num6 0x4D
	#define NumPlus 0x4E
	#define Num1 0x4F
	#define Num2 0x50
	#define Num3 0x51
	#define Num0 0x52
	#define NumDot 0x53
	#define Function11 0x57
	#define Function12 0x58

    extern const unsigned char AZERTY_Table[];
    char Translate(uint8_t scancode, bool uppercase, bool alternate);
}