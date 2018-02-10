   ;;===========================================================
   ;; Assembly implementations of the bare ISR's
   ;;===========================================================

   [bits 32]

   [global interrupt_done]

   [extern kernel_panic]
   [extern interrupt_done]
   
   ;;===========================================================
   ;; Basic isr routine macro definition
   ;;===========================================================
   
   %macro ISR_ROUTINE 1

   [global %1_irq]
   [extern %1_handler]

%1_irq:
   cli                          ; Clear interrupts
   pushad                       ; Push all state to stack
   cld                          ; EDX must be cleared on c-code entry.

   call  %1_handler             ; Call the c handler.

   popad                        ; Restore state.
   sti                          ; Enable new interrupts
   iret                         ; Return from interrupt.

   %endmacro 

                                
   ISR_ROUTINE divide_by_zero   
   ISR_ROUTINE debug
   ISR_ROUTINE non_maskable_interrupt
   ISR_ROUTINE breakpoint
   ISR_ROUTINE overflow
   ISR_ROUTINE bound_range
   ISR_ROUTINE invalid_opcode
   ISR_ROUTINE device_not_available
   ISR_ROUTINE double_fault
   ISR_ROUTINE invalid_tss
   ISR_ROUTINE seg_not_present
   ISR_ROUTINE stack_seg_fault
   ISR_ROUTINE general_protection_fault
   ISR_ROUTINE page_fault
   ISR_ROUTINE FPU_exception
   ISR_ROUTINE alignment_check
   ISR_ROUTINE machine_check
   ISR_ROUTINE SIMD_floating_point
   ISR_ROUTINE virtualization
   ISR_ROUTINE security