#include "Init.h"

void teste(uint64_t x){
	double y;
	y = *(double*)&x;

	RenduGlobal->Print(ToString(y, 7));
	RenduGlobal->NewLine();

	return;
}

void teste2(double x){
	RenduGlobal->Print(ToString(x, 20));
	RenduGlobal->NewLine();

	return;
}

void teste3(uint32_t x){
	float y;
	y = *(float*)&x;

	RenduGlobal->Print(ToString(y, 7));
	RenduGlobal->NewLine();

	return;
}

void teste4(float x){
	RenduGlobal->Print(ToString(x, 20));
	RenduGlobal->NewLine();

	return;
}

extern "C" void _start(BootInfo* bootInfo){
    KernelInfo kernelInfo = InitializeKernel(bootInfo);
	
	RenduGlobal->ClearColor = 0xFF000000;
	RenduGlobal->Clear();
	RenduGlobal->CursorPosition = {0,0};
	
    RenduGlobal->Print("C'est bon!\r\n2021, 2023\r\n\r\n64-bit\r\n\r\n");
	
	RenduGlobal->Print("Teste des nombres flottants (double precision):");
	RenduGlobal->NewLine();
	teste(0x0000000000000000);
	teste(0x7FEFFFFFFFFFFFFF);
	teste(0x7FF0000000000000);
	teste(0x7FF0000000000001);
	teste(0x7FFFFFFFFFFFFFFF);
	teste(0x8000000000000000);
	teste(0xFFEFFFFFFFFFFFFF);
	teste(0xFFF0000000000000);
	teste(0xFFF0000000000001);
	teste(0xFFFFFFFFFFFFFFFF);
	teste2(35278575923551.0872350573285752);
	teste2(935278575923551.0872350573285752);
	teste2(9935278575923551.0872350573285752);
	teste2(99935278575923551.0872350573285752);
	teste2(999935278575923551.0872350573285752);
	RenduGlobal->NewLine();

	RenduGlobal->Print("Teste des nombres flottants (single precision):");
	RenduGlobal->NewLine();
	teste3(0x00000000);
	teste3(0x7F7FFFFF);
	teste3(0x7F800000);
	teste3(0x7FF00001);
	teste3(0x7FFFFFFF);
	teste3(0x80000000);
	teste3(0xFF7FFFFF);
	teste3(0xFF800000);
	teste3(0xFF800001);
	teste3(0xFFFFFFFF);
	teste4(35278575923551.0872350573285752f);
	teste4(935278575923551.0872350573285752f);
	teste4(9935278575923551.0872350573285752f);
	teste4(99935278575923551.0872350573285752f);
	teste4(999935278575923551.0872350573285752f);

    while(true){
		asm("hlt");
	}
}