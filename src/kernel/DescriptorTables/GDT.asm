[bits 64]
gdt_set:
   lgdt    [rdi]
   	         

   mov ax, 0x10 ; Data segment
   mov ds, ax  
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   
   pop rdi		  
   mov rax, 0x08 ; Code segment
   push rax		  
   push rdi		  
   retfq		     
GLOBAL gdt_set