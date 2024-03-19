#pragma once
#include "PG.h"
#include "PFA.h"
#include "PMI.h"

#include <stdint.h>
#include "../Memoire/Memoire.h"

class PageTableManager {
    public:
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};

extern PageTableManager GlobalPageTableManager;