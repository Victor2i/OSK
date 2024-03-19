#include "ERRORPHATALBAZOKA.h"
#include "RenduLent.h"

void Panic(const char* PanicMessage){
	RenduGlobal->ClearColor = 0xFF0000FF;
    RenduGlobal->Clear();
    RenduGlobal->CursorPosition = {0, 0};
    RenduGlobal->Color = 0xFFFFFFFF;
    RenduGlobal->Print("Erreur fatale lors de l'ex�cution du kernel: ");

    RenduGlobal->Print(PanicMessage);
	
	RenduGlobal->NewLine();
	RenduGlobal->NewLine();
	RenduGlobal->Print("Syst�me arr�t�.");
}