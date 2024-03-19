; Macro pour inclure des données binaires

%macro InclureBinaire 2
	SECTION .rodata
	GLOBAL %1
%1:
	incbin %2
	%1_size: dq %1_size - %1
%endmacro

; Ci-dessous, on utilise la macro

InclureBinaire MousePointer, "source/Kernel/PS2/MousePointer.bin"