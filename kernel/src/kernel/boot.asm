   ;;
   ;; boot.asm
   ;;
   ;; Defines the entry point of the kernel image.
   ;;

   [global _start]

   [extern kernel_main]

   ;; Setup Multiboot constants
MBALIGN equ 1<<0                ; Multiboot align flag
MEMINFO equ 1<<1                ; Memory Info  flag

FLAGS equ MBALIGN | MEMINFO     ; Define multiboot flags
MAGIC equ 0x1BADB002            ; Define multiboot magic number
CHECKSUM equ -(MAGIC + FLAGS)   ; Define the Checksum

STACKSIZE equ 0x4000            ; Define stack size

KERNEL_VIRTUAL_BASE equ 0xC0000000 ; Address of the base of the kernel in virtual memory
KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22) ; The page number of the kernel

PD_PRESENT    equ 0x01
PD_WRITABLE   equ 0x02
PD_USER       equ 0x04
PD_PWT        equ 0x08
PD_PCD        equ 0x10
PD_ACCESSED   equ 0x20
PD_DIRTY      equ 0x40
PD_4MB        equ 0x80
PD_CPU_GLOBAL equ 0x100
PD_LV4_GLOBAL equ 0x200

PD_FLAGS equ PD_4MB | PD_WRITABLE | PD_PRESENT

   ;; Marker to indicate the beginning of the kernel
_begin:

   ;; The temporary page directory used while booting the OS.
   ;; It is a very simple mapping using 4MB pages that maps the
   ;; first 4MB to itself and maps the kernel to 0xC0000000 to achieve
   ;; the "higher half" effect where the kernel is mapped to 3GB virtual
   ;; but is loaded at 1MB physical.
   section .data
   align 0x1000
BootPageDirectory:
   dd    0x00000000 | PD_FLAGS  ; ID map 4MB
   times (KERNEL_PAGE_NUMBER - 1) dd 0 ; Null some pages
   dd    0x00000000 | PD_FLAGS  ; Map kernel to 3GB
   times (1024 - KERNEL_PAGE_NUMBER - 1) dd ; Null rest

   ;; Multiboot section
   ;; This is where multiboot magic and flags are stored so the bootloader can
   ;; verify thats this image is multiboot-compliant.
   section .multiboot
   align 4

   dd    MAGIC                  ; Multiboot magic
   dd    FLAGS                  ; Multiboot flags
   dd    CHECKSUM               ; Multiboot checksum


   ;; Text section where the actual boot code is placed
   section .text
_start:

   ;; First we activate paging so we can refenence stuff by address.
   ;; This is done in 3 steps:
   ;;
   ;; 1. Load address of page directory to CR3
   ;; 2. Set Paging bit in CR0 and Page Size Extension (PSE) bit in CR3.
   ;; 3. Perform a far jump.
   mov   ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE) ; Load physical address of boot page dir
   mov   cr3, ecx               ; Load into CR3

   mov   ecx, cr4               ; Get currnent CR3 value
   or    ecx, 0x00000010        ; Set PSE Bit
   mov   cr4, ecx               ; Store in CR3

   mov   ecx, cr0               ; Get current CR0 value
   or    ecx, 0x80000000        ; Set Paging Bit
   mov   cr0, ecx               ; Store in CR0

   lea   ecx, [_start_high]     ; Load our high half loading code
   jmp   ecx                    ; Perform the jump

_start_high:

   ;; We do in fact need the first 4MB to ease the process of setting up the real
   ;; virtual memory manager
   ;; mov dword [BootPageDirectory], 0 ; Unmap the ID-mapped first 4MB
   ;; invlpg [0]                       ; Mark as invalid

   mov   esp, stack_top         ; Set stack pointer

   push  eax                    ; Push multiboot magic number

   add   ebx, KERNEL_VIRTUAL_BASE ; Account for that we now reference memory at 3GB
   push  ebx                    ; Push pointer to multiboot structure

   call  kernel_main            ; Call the kernel main function.
   cli                          ; If we return, just hang the kernel

.hang:
   hlt   
   jmp   .hang

   ;; bss section with all data that should be initiated to 0
   section .bss

   align 16
stack_bottom:
   resb  STACKSIZE              ; Reserve memory for the stack
stack_top:

   
.end:                           ; Mark to indicate the end of the program
