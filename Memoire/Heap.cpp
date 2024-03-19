#include "Heap.h"

// allocation mémoire
#include "../Paginage/PTM.h"
#include "../Paginage/PFA.h"

void* HeapStart;
void* HeapEnd;
HeapSegHdr* LastHdr;

void InitializeHeap(void* HeapAddress, size_t PageCount){
    void* Position = HeapAddress;

    for (size_t i = 0; i < PageCount; i++){
        GlobalPageTableManager.MapMemory(Position, GlobalAllocator.RequestPage());
        Position = (void*)((size_t)Position + 0x1000);
    }

    size_t HeapLength = PageCount * 0x1000;

    HeapStart = HeapAddress;
    HeapEnd = (void*)((size_t)HeapStart + HeapLength);
    HeapSegHdr* StartSegment = (HeapSegHdr*)HeapAddress;
    StartSegment->Length = HeapLength - sizeof(HeapSegHdr);
    StartSegment->Next = NULL;
    StartSegment->Last = NULL;
    StartSegment->IsFree = true;
    LastHdr = StartSegment;
}

void Free(void* address){
    HeapSegHdr* segment = (HeapSegHdr*)address - 1;
    segment->IsFree = true;
    segment->CombineForward();
    segment->CombineBackward();
}

void* Malloc(size_t Size){
    if (Size % 0x10 > 0){ // La variable size DOIT être un multiple de 0x10 (16)
        Size -= (Size % 0x10);
        Size += 0x10;
    }

    if (Size == 0) return NULL;

    HeapSegHdr* CurrentSegment = (HeapSegHdr*) HeapStart;
    while(true){
        if(CurrentSegment->IsFree){
            if (CurrentSegment->Length > Size){
                CurrentSegment->Split(Size);
                CurrentSegment->IsFree = false;
                return (void*)((uint64_t)CurrentSegment + sizeof(HeapSegHdr));
            }
            if (CurrentSegment->Length == Size){
                CurrentSegment->IsFree = false;
                return (void*)((uint64_t)CurrentSegment + sizeof(HeapSegHdr));
            }
        }
        if (CurrentSegment->Next == NULL) break;
        CurrentSegment = CurrentSegment->Next;
    }
    ExpandHeap(Size);
    return Malloc(Size);
}

HeapSegHdr* HeapSegHdr::Split(size_t SplitLength){
    if (SplitLength < 0x10) return NULL;
    int64_t SplitSegmentLength = Length - SplitLength - (sizeof(HeapSegHdr));
    if (SplitSegmentLength < 0x10) return NULL;

    HeapSegHdr* NewSplitHdr = (HeapSegHdr*) ((size_t)this + SplitLength + sizeof(HeapSegHdr));
    Next->Last = NewSplitHdr;
    NewSplitHdr->Next = Next;
    Next = NewSplitHdr;
    NewSplitHdr->Last = this;
    NewSplitHdr->Length = SplitSegmentLength;
    NewSplitHdr->IsFree = IsFree;
    Length = SplitLength;

    if (LastHdr == this) LastHdr = NewSplitHdr;
    return NewSplitHdr;
}

void ExpandHeap(size_t Length){
    if (Length % 0x1000) {
        Length -= Length % 0x1000;
        Length += 0x1000;
    }

    size_t PageCount = Length / 0x1000;
    HeapSegHdr* NewSegment = (HeapSegHdr*)HeapEnd;

    for (size_t i = 0; i < PageCount; i++){
        GlobalPageTableManager.MapMemory(HeapEnd, GlobalAllocator.RequestPage());
        HeapEnd = (void*)((size_t)HeapEnd + 0x1000);
    }

    NewSegment->IsFree = true;
    NewSegment->Last = LastHdr;
    LastHdr->Next = NewSegment;
    LastHdr = NewSegment;
    NewSegment->Next = NULL;
    NewSegment->Length = Length - sizeof(HeapSegHdr);
    NewSegment->CombineBackward();

}

void HeapSegHdr::CombineForward(){
    if (Next == NULL) return;
    if (!Next->IsFree) return;

    if (Next == LastHdr) LastHdr = this;

    if (Next->Next != NULL){
        Next->Next->Last = this;
    }

    Length = Length + Next->Length + sizeof(HeapSegHdr);

    Next = Next->Next;
}

void HeapSegHdr::CombineBackward(){
    if (Last != NULL && Last->IsFree) Last->CombineForward();
}