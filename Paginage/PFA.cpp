#include "PFA.h"

uint64_t FreeMemory;
uint64_t ReservedMemory;
uint64_t UsedMemory;
bool Initialized = false;
PageFrameAllocator GlobalAllocator;

bool Bitmap::operator[](uint64_t index){
    return Get(index);
}

bool Bitmap::Get(uint64_t index){
    if (index > Size * 8) return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if ((Buffer[byteIndex] & bitIndexer) > 0){
        return true;
    }
    return false;
}

bool Bitmap::Set(uint64_t index, bool value){
    if (index > Size * 8) return false;
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    Buffer[byteIndex] &= ~bitIndexer;
    if (value){
        Buffer[byteIndex] |= bitIndexer;
    }
    return true;
}

void PageFrameAllocator::ReadEFIMemoryMap(EFI_MEMORY_DESCRIPTOR* MemoryMapFirstDescriptor, size_t MemoryMapSize, size_t MemoryMapDescriptorSize){
    if (Initialized) return;

    Initialized = true;

    uint64_t MemoryMapEntries = MemoryMapSize / MemoryMapDescriptorSize;

    void* LargestFreeMemorySegment = NULL;
    size_t LargestFreeMemorySegmentSize = 0;

    for (int i = 0; i < MemoryMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* Descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)MemoryMapFirstDescriptor + (i * MemoryMapDescriptorSize));
        if (Descriptor->Type == 7){
            if (Descriptor->NumPages * 4096 > LargestFreeMemorySegmentSize)
            {
                LargestFreeMemorySegment = Descriptor->PhysicalAddress;
                LargestFreeMemorySegmentSize = Descriptor->NumPages * 4096;
            }
        }
    }

    uint64_t MemorySize = GetMemorySize(MemoryMapFirstDescriptor, MemoryMapEntries, MemoryMapDescriptorSize);
    FreeMemory = MemorySize;
    uint64_t BitmapSize = MemorySize / 4096 / 8 + 1;

    InitBitmap(BitmapSize, LargestFreeMemorySegment);

    ReservePages(0, MemorySize / 4096 + 1);
    for (int i = 0; i < MemoryMapEntries; i++){
        EFI_MEMORY_DESCRIPTOR* Descriptor = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)MemoryMapFirstDescriptor + (i * MemoryMapDescriptorSize));
        if (Descriptor->Type == 7){
            UnreservePages(Descriptor->PhysicalAddress, Descriptor->NumPages);
        }
    }
    ReservePages(0, 0x100);
    LockPages(PageBitmap.Buffer, PageBitmap.Size / 4096 + 1);
}

void PageFrameAllocator::InitBitmap(size_t BitmapSize, void* BufferAddress){
    PageBitmap.Size = BitmapSize;
    PageBitmap.Buffer = (uint8_t*)BufferAddress;
    for (int i = 0; i < BitmapSize; i++){
        *(uint8_t*)(PageBitmap.Buffer + i) = 0;
    }
}
uint64_t PageBitmapIndex = 0;
void* PageFrameAllocator::RequestPage(){
    for (; PageBitmapIndex < PageBitmap.Size * 8; PageBitmapIndex++){
        if (PageBitmap[PageBitmapIndex] == true) continue;
        LockPage((void*)(PageBitmapIndex * 4096));
        return (void*)(PageBitmapIndex * 4096);
    }

    return NULL;
}

void PageFrameAllocator::FreePage(void* Address){
    uint64_t Index = (uint64_t)Address / 4096;
    if (PageBitmap[Index] == false) return;
    if (PageBitmap.Set(Index, false)){
        FreeMemory += 4096;
        UsedMemory -= 4096;
        if (PageBitmapIndex > Index) PageBitmapIndex = Index;
    }
}

void PageFrameAllocator::FreePages(void* Address, uint64_t PageCount){
    for (int t = 0; t < PageCount; t++){
        FreePage((void*)((uint64_t)Address + (t * 4096)));
    }
}

void PageFrameAllocator::LockPage(void* Address){
    uint64_t Index = (uint64_t)Address / 4096;
    if (PageBitmap[Index] == true) return;
    if (PageBitmap.Set(Index, true)){
        FreeMemory -= 4096;
        UsedMemory += 4096;
    }
}

void PageFrameAllocator::LockPages(void* Address, uint64_t PageCount){
    for (int t = 0; t < PageCount; t++){
        LockPage((void*)((uint64_t)Address + (t * 4096)));
    }
}

void PageFrameAllocator::UnreservePage(void* Address){
    uint64_t Index = (uint64_t)Address / 4096;
    if (PageBitmap[Index] == false) return;
    if (PageBitmap.Set(Index, false)){
        FreeMemory += 4096;
        ReservedMemory -= 4096;
        if (PageBitmapIndex > Index) PageBitmapIndex = Index;
    }
}

void PageFrameAllocator::UnreservePages(void* Address, uint64_t PageCount){
    for (int t = 0; t < PageCount; t++){
        UnreservePage((void*)((uint64_t)Address + (t * 4096)));
    }
}

void PageFrameAllocator::ReservePage(void* Address){
    uint64_t Index = (uint64_t)Address / 4096;
    if (PageBitmap[Index] == true) return;
    if (PageBitmap.Set(Index, true)){
        FreeMemory -= 4096;
        ReservedMemory += 4096;
    }
}

void PageFrameAllocator::ReservePages(void* Address, uint64_t PageCount){
    for (int t = 0; t < PageCount; t++){
        ReservePage((void*)((uint64_t)Address + (t * 4096)));
    }
}

uint64_t PageFrameAllocator::GetFreeRAM(){
    return FreeMemory;
}
uint64_t PageFrameAllocator::GetUsedRAM(){
    return UsedMemory;
}
uint64_t PageFrameAllocator::GetReservedRAM(){
    return ReservedMemory;
}