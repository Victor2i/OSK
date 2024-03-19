#include "Interruptions.h"
#include "PIT.h"
#include "../ERRORPHATALBAZOKA.h"
#include "../Hardware/IO.h"
#include "../Conversion.h"

__attribute__((interrupt)) void DivideByZero_Handler(struct interrupt_frame* frame){
    Panic("Division par z�ro");
    while(true);
}
__attribute__((interrupt)) void Debug_Handler(struct interrupt_frame* frame){
    Panic("D�bogage");
    while(true);
}
__attribute__((interrupt)) void NonMaskableInterrupt_Handler(struct interrupt_frame* frame){
    Panic("Interruption non masquable");
    while(true);
}
__attribute__((interrupt)) void Breakpoint_Handler(struct interrupt_frame* frame){
    Panic("Point d'arr�t");
    while(true);
}
__attribute__((interrupt)) void Overflow_Handler(struct interrupt_frame* frame){
    Panic("D�passement");
    while(true);
}
__attribute__((interrupt)) void BoundRangeExceeded_Handler(struct interrupt_frame* frame){
    Panic("D�passement de plage");
    while(true);
}
__attribute__((interrupt)) void IllegalInstruction_Handler(struct interrupt_frame* frame){
    Panic("Instruction non document�e");
    while(true);
}
__attribute__((interrupt)) void DeviceNotAvaible_Handler(struct interrupt_frame* frame){
    Panic("Dispositif non disponible");
    while(true);
}
__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame){
    Panic("Erreur double");
    while(true);
}
__attribute__((interrupt)) void CoprocessorSegmentOverrun_Handler(struct interrupt_frame* frame){
    Panic("D�passement de segment de coprocesseur");
    while(true);
}
__attribute__((interrupt)) void InvalidTSS_Handler(struct interrupt_frame* frame){
    Panic("TSS invalide");
    while(true);
}
__attribute__((interrupt)) void SegmentNotPresent_Handler(struct interrupt_frame* frame){
    Panic("Segment non pr�sent");
    while(true);
}
__attribute__((interrupt)) void StackSegmentFault_Handler(struct interrupt_frame* frame){
    Panic("Erreur de segment de pile");
    while(true);
}
__attribute__((interrupt)) void GeneralProtectionFault_Handler(struct interrupt_frame* frame){
    Panic("Erreur de protection g�n�rale");
    while(true);
}
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame){
	Panic("D�faut de page d�tect�");
    while(true);
}
__attribute__((interrupt)) void FloatingPointException_Handler(struct interrupt_frame* frame){
	Panic("Erreur d'instruction � virgule flottante");
    while(true);
}
__attribute__((interrupt)) void AlignmentCheck_Handler(struct interrupt_frame* frame){
	Panic("V�rification alignement");
    while(true);
}
__attribute__((interrupt)) void MachineCheck_Handler(struct interrupt_frame* frame){
	Panic("V�rification machine");
    while(true);
}
__attribute__((interrupt)) void SIMD_FloatingPointException_Handler(struct interrupt_frame* frame){
	Panic("Erreur d'instruction � donn�es multiples");
    while(true);
}
__attribute__((interrupt)) void VirtualizationException_Handler(struct interrupt_frame* frame){
	Panic("Erreur de virtualisation");
    while(true);
}
__attribute__((interrupt)) void PIT_Handler(struct interrupt_frame* frame){
    PIT::Tick();
    PIC_EndMaster();
}
__attribute__((interrupt)) void Keyboard_Handler(struct interrupt_frame* frame){
	uint8_t scancode = InByte(0x60);
	HandleKeyboard(scancode);
	PIC_EndMaster();
}
__attribute__((interrupt)) void Mouse_Handler(struct interrupt_frame* frame){
	uint8_t mouseData = InByte(0x60);
	HandleMouse(mouseData);
	PIC_EndSlave();
}

void PIC_EndMaster(){
    OutByte(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave(){
    OutByte(PIC2_COMMAND, PIC_EOI);
    OutByte(PIC1_COMMAND, PIC_EOI);
}
   

void RemapPIC(){
    uint8_t a1, a2; 

    a1 = InByte(PIC1_DATA);
    IOWait();
    a2 = InByte(PIC2_DATA);
    IOWait();

    OutByte(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    IOWait();
    OutByte(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    IOWait();

    OutByte(PIC1_DATA, 0x20);
    IOWait();
    OutByte(PIC2_DATA, 0x28);
    IOWait();

    OutByte(PIC1_DATA, 4);
    IOWait();
    OutByte(PIC2_DATA, 2);
    IOWait();

    OutByte(PIC1_DATA, ICW4_8086);
    IOWait();
    OutByte(PIC2_DATA, ICW4_8086);
    IOWait();

    OutByte(PIC1_DATA, a1);
    IOWait();
    OutByte(PIC2_DATA, a2);
}