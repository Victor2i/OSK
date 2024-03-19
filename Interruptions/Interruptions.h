#pragma once
#include "../RenduLent.h"
#include "../PS2/ClavierPS2.h"
#include "../PS2/Souris.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

struct interrupt_frame;
__attribute__((interrupt)) void DivideByZero_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Debug_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void NonMaskableInterrupt_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Breakpoint_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Overflow_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void BoundRangeExceeded_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void IllegalInstruction_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void DeviceNotAvaible_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void DoubleFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void CoprocessorSegmentOverrun_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void InvalidTSS_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void SegmentNotPresent_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void StackSegmentFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void GeneralProtectionFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void PageFault_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void FloatingPointException_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void AlignmentCheck_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void MachineCheck_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void SIMD_FloatingPointException_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void VirtualizationException_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void PIT_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Keyboard_Handler(struct interrupt_frame* frame);
__attribute__((interrupt)) void Mouse_Handler(struct interrupt_frame* frame);

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();