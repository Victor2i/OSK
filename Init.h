#pragma once
#include <stdint.h>
#include "GDT/GDT.h"
#include "Interruptions/IDT.h"
#include "Interruptions/Interruptions.h"
#include "Hardware/IO.h"
#include "RenduLent.h"
#include "Conversion.h"
#include "Hardware/MemoireEFI.h"
#include "Memoire/Memoire.h"
#include "Paginage/PG.h"
#include "Paginage/PFA.h"
#include "Paginage/PMI.h"
#include "Paginage/PTM.h"
#include "PS2/ClavierPS2.h"
#include "PS2/Souris.h"
#include "Memoire/Heap.h"
#include "Interruptions/PIT.h"

// drivers
#include "drivers/acpi/acpi.h"
#include "drivers/acpi/pci.h"

struct BootInfo {
	Framebuffer* BootFramebuffer;
	FNT1_FONT* FNT1Font;
	EFI_MEMORY_DESCRIPTOR* MemoryMapFirstDescriptor;
	uint64_t MemoryMapSize;
	uint64_t MemoryMapDescriptorSize;
	ACPI::RSDP2* RSDP;
} ;

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;

struct KernelInfo {
    PageTableManager* KernelPageTableManager;
};

KernelInfo InitializeKernel(BootInfo* BootInfo);