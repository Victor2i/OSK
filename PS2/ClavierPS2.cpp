#include "ClavierPS2.h"

bool IsLeftShiftPressed;
bool IsRightShiftPressed;
bool IsLeftControlPressed;
bool IsRightControlPressed;
bool IsLeftAltPressed;
bool IsRightAltPressed;
bool IsCapsLockActivated;
bool IsNumLockActivated;
bool IsScrollLockActivated;
uint8_t ScancodePS;
uint8_t DernierScancode;

void ClavierACK(void){
	while(!(InByte(0x60)==0xFA));
}

void ClavierLED(uint8_t LEDStatus){
	OutByte(0x60, 0xED);
	ClavierACK();
	OutByte(0x60, LEDStatus);
}

void ClavierLEDUpdate(void){
	ClavierLED(IsScrollLockActivated + (IsNumLockActivated << 1) + (IsCapsLockActivated << 2));
}

void HandlerClavierSpecial(uint8_t scancode) {
	switch (scancode) {
		case 0x1D: // Contr�le droit press�
			IsRightControlPressed = true;
			break;
		case 0x9D: // Contr�le droit rel�ch�
			IsRightControlPressed = false;
			break;
		case 0x35: // Clavier num�rique "/"
			RenduGlobal->CharPrint('/');
			break;
		case 0x38: // Alternatif droit (AltGr) press�
			IsRightAltPressed = true;
			break;
		case 0xB8: // Alternatif droit (AltGr) rel�ch�
			IsRightAltPressed = false;
			break;
		case 0x47: // Home
			RenduGlobal->CursorPosition = {(((RenduGlobal->TargetFramebuffer->Width) / 2) - (((RenduGlobal->TargetFramebuffer->Width) / 2) % 8)),(((RenduGlobal->TargetFramebuffer->Height) / 2) - (((RenduGlobal->TargetFramebuffer->Height) / 2) % 16))};
			break;
		case 0x48: // Fl�che haut
			if (RenduGlobal->CursorPosition.Y > 15){
				RenduGlobal->CursorPosition.Y -= 16;
			}
			break;
		case 0x49: // Page haut
			RenduGlobal->CursorPosition.Y = 0;
			break;
		case 0x4B: // Fl�che gauche
			if (RenduGlobal->CursorPosition.X < 7){
				if (RenduGlobal->CursorPosition.Y > 15){
					RenduGlobal->CursorPosition.X = (RenduGlobal->TargetFramebuffer->Width - 8);
					RenduGlobal->CursorPosition.Y -= 16;
				}
			}
			else{
				RenduGlobal->CursorPosition.X -= 8;
			}
			break;
		case 0x4D: // Fl�che droite
			if (RenduGlobal->CursorPosition.Y < (RenduGlobal->TargetFramebuffer->Height - 31)){
				RenduGlobal->CursorPosition.X += 8;
			}
			else{
				RenduGlobal->CursorPosition.X += 8;
			}
			break;
		case 0x4F: // Fin
			RenduGlobal->CursorPosition.Y = (RenduGlobal->TargetFramebuffer->Height - (RenduGlobal->TargetFramebuffer->Height % 16) - 16);
			break;
		case 0x50: // Fl�che bas
			if (RenduGlobal->CursorPosition.Y < (RenduGlobal->TargetFramebuffer->Height - 31)){
				RenduGlobal->CursorPosition.Y += 16;
			}
			break;
		case 0x51: // Page bas
			RenduGlobal->CursorPosition.Y = (RenduGlobal->TargetFramebuffer->Height - (RenduGlobal->TargetFramebuffer->Height % 16) - 16);
			break;
		case 0x52: // Insersion
			break;
		case 0x53: // Supprimer
			break;
		default:
			break;
	}
}

void HandlerClavierStandard(uint8_t scancode){
	switch (scancode){
		case Backspace:
			RenduGlobal->ClearChar();
			return;
		case LeftShift: // Shift gauche press�
			IsLeftShiftPressed = true;
			return;
        case LeftShift + 0x80: // Shift gauche rel�ch�
			IsLeftShiftPressed = false;
			return;
        case RightShift: // Shift droit press�
			IsRightShiftPressed = true;
			return;
        case RightShift + 0x80: // Shift droit rel�ch�
			IsRightShiftPressed = false;
            return;
		case LeftControl: // Contr�le gauche press�
			IsLeftControlPressed = true;
			return;
		case LeftControl + 0x80: // Contr�le gauche rel�ch�
			IsLeftControlPressed = false;
			return;
		case LeftAlt: // Alternatif gauche press�
			IsLeftAltPressed = true;
			return;
		case LeftAlt + 0x80: // Alternatif gauche rel�ch�
			IsLeftAltPressed = false;
			return;
        case Enter:
			RenduGlobal->NewLine();
			return;
		case CapsLock:
			switch (IsCapsLockActivated){
				case true:
					IsCapsLockActivated = false;
					ClavierLEDUpdate();
					return;
				case false:
					IsCapsLockActivated = true;
					ClavierLEDUpdate();
					return;
			}
		case NumberLock:
			switch (IsNumLockActivated){
				case true:
					IsNumLockActivated = false;
					ClavierLEDUpdate();
					return;
				case false:
					IsNumLockActivated = true;
					ClavierLEDUpdate();
					return;
			}
		case ScrollLock:
			switch (IsScrollLockActivated){
				case true:
					IsScrollLockActivated = false;
					ClavierLEDUpdate();
					return;
				case false:
					IsScrollLockActivated = true;
					ClavierLEDUpdate();
					return;
			}
		case Function5:
			RenduGlobal->Mouse1Color = 0xFFFFFEFF;
			return;
		case Function6:
			RenduGlobal->Mouse1Color ^= 0x00FF0000;
			return;
		case Function7:
			RenduGlobal->Mouse1Color ^= 0x0000FE00;
			return;
		case Function8:
			RenduGlobal->Mouse1Color ^= 0x000000FF;
			return;
		case NumStar:
			RenduGlobal->CharPrint('*');
			return;
		case Spacebar:
			RenduGlobal->CharPrint(' ');
			return;
		case NumMinus:
			RenduGlobal->CharPrint('-');
			return;
		case NumPlus:
			RenduGlobal->CharPrint('+');
			return;
		case Num1:
			switch (IsNumLockActivated){
				case true: // 1
					RenduGlobal->CharPrint('1');
					return;
				case false: // Fin
					RenduGlobal->CursorPosition.Y = (RenduGlobal->TargetFramebuffer->Height - (RenduGlobal->TargetFramebuffer->Height % 16) - 16);
					return;
			}
		case Num2:
			switch (IsNumLockActivated){
				case true: // 2
					RenduGlobal->CharPrint('2');
					return;
				case false: // Fl�che bas
					if (RenduGlobal->CursorPosition.Y < (RenduGlobal->TargetFramebuffer->Height - 31)){
						RenduGlobal->CursorPosition.Y += 16;
					}
					return;
			}
		case Num3:
			switch (IsNumLockActivated){
				case true: // 3
					RenduGlobal->CharPrint('3');
					return;
				case false: // Page bas
					RenduGlobal->CursorPosition.Y = (RenduGlobal->TargetFramebuffer->Height - (RenduGlobal->TargetFramebuffer->Height % 16) - 16);
					return;
			}
		case Num4:
			switch (IsNumLockActivated){
				case true: // 4
					RenduGlobal->CharPrint('4');
					return;
				case false: // Fl�che gauche
					if (RenduGlobal->CursorPosition.X < 7){
						if (RenduGlobal->CursorPosition.Y > 15){
							RenduGlobal->CursorPosition.X = (RenduGlobal->TargetFramebuffer->Width - 8);
							RenduGlobal->CursorPosition.Y -= 16;
						}
					}
					else{
						RenduGlobal->CursorPosition.X -= 8;
					}
					return;
			}
		case Num5:
			switch (IsNumLockActivated){
				case true: // 5
					RenduGlobal->CharPrint('5');
					return;
				case false: // Aucune action
					return;
			}
		case Num6:
			switch (IsNumLockActivated){
				case true: // 6
					RenduGlobal->CharPrint('6');
					return;
				case false: // Fl�che droite
					if (RenduGlobal->CursorPosition.Y < (RenduGlobal->TargetFramebuffer->Height - 31)){
						RenduGlobal->CursorPosition.X += 8;
					}
					else{
						RenduGlobal->CursorPosition.X += 8;
					}
					return;
			}
		case Num7:
			switch (IsNumLockActivated){
				case true: // 7
					RenduGlobal->CharPrint('7');
					return;
				case false: // Home
					RenduGlobal->CursorPosition = {(((RenduGlobal->TargetFramebuffer->Width) / 2) - (((RenduGlobal->TargetFramebuffer->Width) / 2) % 8)),(((RenduGlobal->TargetFramebuffer->Height) / 2) - (((RenduGlobal->TargetFramebuffer->Height) / 2) % 16))};
					return;
			}
		case Num8:
			switch (IsNumLockActivated){
				case true: // 8
					RenduGlobal->CharPrint('8');
					return;
				case false: // Fl�che haut
					if (RenduGlobal->CursorPosition.Y > 15){
						RenduGlobal->CursorPosition.Y -= 16;
					}
					return;
			}
		case Num9:
			switch (IsNumLockActivated){
				case true: // 9
					RenduGlobal->CharPrint('9');
					return;
				case false: // Page haut
					RenduGlobal->CursorPosition.Y = 0;
					return;
			}
		case Num0:
			switch (IsNumLockActivated){
				case true: // 0
					RenduGlobal->CharPrint('0');
					return;
				case false: // Insertion
					return;
			}
		case NumDot:
			switch (IsNumLockActivated){
				case true: // .
					RenduGlobal->CharPrint('.');
					return;
				case false: // Supprimer
					return;
			}
	}
	char ascii = AZERTY_Keyboard::Translate(scancode, IsLeftShiftPressed | IsRightShiftPressed | IsCapsLockActivated, IsRightAltPressed);
	
	if (ascii != 0){
		RenduGlobal->CharPrint(ascii);
	}
}

void HandleKeyboard(uint8_t scancode){
	switch (DernierScancode){
		case 0xE0:
			HandlerClavierSpecial(scancode);
			break;
		default:
			HandlerClavierStandard(scancode);
	}
	DernierScancode = scancode;
}