#include "PG.h"

void PageDirectoryEntry::SetFlag(PT_Flag Flag, bool Enabled){
    uint64_t BitSelector = (uint64_t)1 << Flag;
    Value &= ~BitSelector;
    if (Enabled){
        Value |= BitSelector;
    }
}

bool PageDirectoryEntry::GetFlag(PT_Flag Flag){
    uint64_t BitSelector = (uint64_t)1 << Flag;
    return Value & BitSelector > 0 ? true : false;
}

uint64_t PageDirectoryEntry::GetAddress(){
    return (Value & 0x000FFFFFFFFFF000) >> 12;
}

void PageDirectoryEntry::SetAddress(uint64_t Address){
    Address &= 0x000000FFFFFFFFFF;
    Value &= 0xFFF0000000000FFF;
    Value |= (Address << 12);
}