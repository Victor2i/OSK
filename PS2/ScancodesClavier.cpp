#include "ScancodesClavier.h"

namespace QWERTY_Keyboard{
    const unsigned char QWERTY_Table[] ={
		0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
		0, 0, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
		0, 0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
		0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0
	};

    char Translate(uint8_t scancode, bool uppercase){
        if (scancode > 58) return 0;

        if (uppercase){
            switch (scancode){
				case 0x02:
					return '!';
				case 0x03:
					return '@';
				case 0x04:
					return '#';
				case 0x05:
					return '$';
				case 0x06:
					return '%';
				case 0x07:
					return '^';
				case 0x08:
					return '&';
				case 0x09:
					return '*';
				case 0x0A:
					return '(';
				case 0x0B:
					return ')';
				case 0x0C:
					return '_';
				case 0x0D:
					return '+';
				case 0x1A:
					return '{';
				case 0x1B:
					return '}';
				case 0x27:
					return ':';
				case 0x28:
					return '\"';
				case 0x29:
					return '~';
				case 0x2B:
					return '|';
				case 0x33:
					return '<';
				case 0x34:
					return '>';
				case 0x35:
					return '?';
				default:
					return QWERTY_Table[scancode] - 32; // Lettres
			}
        }
        else return QWERTY_Table[scancode];
    }
}

namespace AZERTY_Keyboard{
	const unsigned char AZERTY_Table[] ={
		0, 0, '&', 233, '\"', '\'', '(', '-', 232, '_', 231, 224, ')', '=',
		0, 0, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$',
		0, 0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 249, 178,
		0, '*', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0
	};
	
	char Translate(uint8_t scancode, bool uppercase, bool alternate){
        if (scancode > 58) return 0;
		
		if (uppercase & alternate){
			return 0;
		}
		
        if (uppercase){
			switch (scancode){
				case 0x02:
					return '1';
				case 0x03:
					return '2';
				case 0x04:
					return '3';
				case 0x05:
					return '4';
				case 0x06:
					return '5';
				case 0x07:
					return '6';
				case 0x08:
					return '7';
				case 0x09:
					return '8';
				case 0x0A:
					return '9';
				case 0x0B:
					return '0';
				case 0x0C:
					return '°';
				case 0x0D:
					return '+';
				case 0x1A:
					return '¨';
				case 0x1B:
					return '£';
				case 0x28:
					return '%';
				case 0x29:
					return 0;
				case 0x2B:
					return 'µ';
				case 0x32:
					return '?';
				case 0x33:
					return '.';
				case 0x34:
					return '/';
				case 0x35:
					return '§';
				default: // Lettres
					return AZERTY_Table[scancode] - 32;
			}
		}
		if (alternate){
			switch (scancode){
				case 0x02:
					return 0;
				case 0x03:
					return '~';
				case 0x04:
					return '#';
				case 0x05:
					return '{';
				case 0x06:
					return '[';
				case 0x07:
					return '|';
				case 0x08:
					return '`';
				case 0x09:
					return '\\';
				case 0x0A:
					return '^';
				case 0x0B:
					return '@';
				case 0x0C:
					return ']';
				case 0x0D:
					return '}';
				case 0x1A:
					return 0;
				case 0x1B:
					return '¤';
				case 0x28:
					return 0;
				case 0x29:
					return 0;
				case 0x2B:
					return 0;
				case 0x32:
					return 0;
				case 0x33:
					return 0;
				case 0x34:
					return 0;
				case 0x35:
					return 0;
				default:
					return 0;
			}
        }
        else return AZERTY_Table[scancode];
    }
}