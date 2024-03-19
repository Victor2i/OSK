#include "PMI.h"

PageMapIndexer::PageMapIndexer(uint64_t VirtualAddress){
    VirtualAddress >>= 12;
    P_i = VirtualAddress & 0x1FF;
    VirtualAddress >>= 9;
    PT_i = VirtualAddress & 0x1FF;
    VirtualAddress >>= 9;
    PD_i = VirtualAddress & 0x1FF;
    VirtualAddress >>= 9;
    PDP_i = VirtualAddress & 0x1FF;
}

