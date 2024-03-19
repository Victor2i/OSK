#include "Init.h"

KernelInfo kernelInfo; 

void PrepareMemory(BootInfo* BootInfo){
    uint64_t mMapEntries = BootInfo->MemoryMapSize / BootInfo->MemoryMapDescriptorSize;

    GlobalAllocator = PageFrameAllocator();
    GlobalAllocator.ReadEFIMemoryMap(BootInfo->MemoryMapFirstDescriptor, BootInfo->MemoryMapSize, BootInfo->MemoryMapDescriptorSize);

    uint64_t kernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;
    uint64_t kernelPages = (uint64_t)kernelSize / 4096 + 1;

    GlobalAllocator.LockPages(&_KernelStart, kernelPages);

    PageTable* PML4 = (PageTable*)GlobalAllocator.RequestPage();
    Memset(PML4, 0, 0x1000);

    GlobalPageTableManager = PageTableManager(PML4);
	
	// TODO: résoudre le crash entraîné par cette boucle ci-dessous
    for (uint64_t t = 0; t < GetMemorySize(BootInfo->MemoryMapFirstDescriptor, mMapEntries, BootInfo->MemoryMapDescriptorSize); t+= 0x1000){
        GlobalPageTableManager.MapMemory((void*)t, (void*)t);
		// ci-dessous des tests pour tenter de comprendre le bug
		RenduGlobal->Print(ToString(t/1000));
		RenduGlobal->Print(" ");
		if (t % 1000000 == 0){
			RenduGlobal->Clear();
			RenduGlobal->CursorPosition.X = 0;
			RenduGlobal->CursorPosition.Y = 0;
		}
    }

    uint64_t fbBase = (uint64_t)BootInfo->BootFramebuffer->BaseAddress;
    uint64_t fbSize = (uint64_t)BootInfo->BootFramebuffer->BufferSize + 0x1000;
    GlobalAllocator.LockPages((void*)fbBase, fbSize/ 0x1000 + 1);
    for (uint64_t t = fbBase; t < fbBase + fbSize; t += 4096){
        GlobalPageTableManager.MapMemory((void*)t, (void*)t);
    }

    asm ("mov %0, %%cr3" : : "r" (PML4));

    kernelInfo.KernelPageTableManager = &GlobalPageTableManager;
}

IDTR idtr;
void SetIDTGate(void* handler, uint8_t entryOffset, uint8_t type_attr, uint8_t selector){
    IDTDescEntry* interrupt = (IDTDescEntry*)(idtr.Offset + entryOffset * sizeof(IDTDescEntry));
    interrupt->SetOffset((uint64_t)handler);
    interrupt->type_attr = type_attr;
    interrupt->selector = selector;
}

void PrepareInterrupts(){
    idtr.Limit = 0x0FFF;
    idtr.Offset = (uint64_t)GlobalAllocator.RequestPage();
	
	SetIDTGate((void*)DivideByZero_Handler, 0x00, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)Debug_Handler, 0x01, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)NonMaskableInterrupt_Handler, 0x02, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)Breakpoint_Handler, 0x03, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)Overflow_Handler, 0x04, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)BoundRangeExceeded_Handler, 0x05, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)IllegalInstruction_Handler, 0x06, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)DeviceNotAvaible_Handler, 0x07, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)DoubleFault_Handler, 0x08, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)CoprocessorSegmentOverrun_Handler, 0x09, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)InvalidTSS_Handler, 0x0A, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)SegmentNotPresent_Handler, 0x0B, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)StackSegmentFault_Handler, 0x0C, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)GeneralProtectionFault_Handler, 0x0D, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)PageFault_Handler, 0x0E, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)FloatingPointException_Handler, 0x10, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)AlignmentCheck_Handler, 0x11, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)MachineCheck_Handler, 0x12, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)SIMD_FloatingPointException_Handler, 0x13, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)VirtualizationException_Handler, 0x14, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)PIT_Handler, 0x20, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)Keyboard_Handler, 0x21, IDT_TA_InterruptGate, 0x08);
	SetIDTGate((void*)Mouse_Handler, 0x2C, IDT_TA_InterruptGate, 0x08);
	
    asm ("lidt %0" : : "m" (idtr));
	
	RemapPIC();
}

void PrepareACPI(BootInfo* BootInfo){
    ACPI::SDTHeader* XSDT = (ACPI::SDTHeader*)(BootInfo->RSDP->XSDTAddress);
    
    ACPI::MCFGHeader* MCFG = (ACPI::MCFGHeader*)ACPI::FindTable(XSDT, (char*)"MCFG");

    PCI::EnumeratePCI(MCFG);
}

RenduLent r = RenduLent(NULL, NULL);

KernelInfo InitializeKernel(BootInfo* BootInfo){
	r = RenduLent(BootInfo->BootFramebuffer, BootInfo->FNT1Font);
    RenduGlobal = &r;
	
	GDTDescriptor GDTDescriptor;
    GDTDescriptor.Size = sizeof(GDT) - 1;
    GDTDescriptor.Offset = (uint64_t)&DefaultGDT;
    LoadGDT(&GDTDescriptor);

    PrepareMemory(BootInfo);

    Memset(BootInfo->BootFramebuffer->BaseAddress, 0, BootInfo->BootFramebuffer->BufferSize);
	
	InitializeHeap((void*)0x0000100000000000, 0x20);
	
	PrepareInterrupts();
	
	InitMouse();
	
	PrepareACPI(BootInfo);
	
	OutByte(PIC1_DATA, 0b11111000);
    OutByte(PIC2_DATA, 0b11101111);
	
	asm("sti");
	
    return kernelInfo;
}