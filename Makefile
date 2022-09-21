override KERNEL := CharraOS.elf
override BOOTLOADER := Bootloader.elf
 
CC := $$HOME/opt/cross/x86_64-elf/bin/x86_64-elf-gcc
LD := $$HOME/opt/cross/x86_64-elf/bin/x86_64-elf-ld
ASMC := nasm

SRCDIR := src
OBJDIR := build
BOOTDIR := Boot
INCLUDEDIRS := -Isrc/libc/include
INCLUDEDIRS += -Isrc
 
# User controllable CFLAGS.
CFLAGS ?= -Wpedantic -Wall

# User controllable linker flags. We set none by default.
LDFLAGS ?=

ASMFLAGS ?=
 
# Internal linker flags that should not be changed by the user.
override INTERNALLDFLAGS :=    \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

override INTERNALCFLAGS :=   \
	-I.                  \
	-std=gnu11           \
	-ffreestanding       \
	-fno-stack-protector \
	-fno-pic             \
	-mabi=sysv           \
	-mno-80387           \
	-mno-mmx             \
	-mno-3dnow           \
	-mno-sse             \
	-mno-sse2            \
	-mno-red-zone        \
	-mcmodel=kernel      \
	-MMD

rwildcard=$(foreach d, $(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

override CFILES := $(call rwildcard,$(SRCDIR), *.c)
override ASMFILES := $(call rwildcard,$(SRCDIR), *.asm)
override BOOTFILES := $(call rwildcard,$(BOOTDIR), *.c)

override OBJ := $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CFILES))
override OBJ += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%_asm.o, $(ASMFILES))
override BOOTOBJ := $(patsubst $(BOOTDIR)/%.c, $(OBJDIR)/$(BOOTDIR)/%.o, $(BOOTFILES))

override HEADER_DEPS := $(OBJDIR)/$(CFILES:.c=.d)

# For todolist
override ALLFILES := $(CFILES) $(ASMFILES) $(call rwildcard,$(SRCDIR), *.h) $(BOOTFILES) $(call rwildcard,$(BOOTDIR), *.h)

# Default target.
.PHONY: all
all:
# Fresh rebuild
	@clear
	@make kernel
	@make bootloader
	@make image
 
.PHONY: kernel
kernel: $(KERNEL)

-include $(HEADER_DEPS)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@ echo !=== COMPILING $^
	@$ mkdir -p $(@D)
	@$(CC) $(INCLUDEDIRS) $(CFLAGS) $(INTERNALCFLAGS) -c $^ -o $@

# Compilation rules for *.asm files.
$(OBJDIR)/%_asm.o: $(SRCDIR)/%.asm
	@ echo !=== COMPILING $^
	@$ mkdir -p $(@D)
	@$(ASMC) $(ASMFLAGS) $^ -f elf64 -o $@

$(KERNEL): $(OBJ)
	@ echo !=== LINKING
	@ $(LD) $(OBJ) $(INTERNALLDFLAGS) -Tlinker.ld -o $@

.PHONY: bootloader
bootloader: $(BOOTLOADER)
	
-include $(HEADER_DEPS)
$(OBJDIR)/$(BOOTDIR)/%.o: $(BOOTDIR)/%.c
	@ echo !=== COMPILING $^
	@$ mkdir -p $(@D)
	@$(CC) $(INCLUDEDIRS) -ffreestanding -fpic -fno-stack-protector -fshort-wchar -mno-red-zone -mgeneral-regs-only -mabi=ms -Wall -Wextra -Wpedantic -O3 -c $^ -o $@ 

$(BOOTLOADER): $(BOOTOBJ)
	@ echo !=== LINKING
	@ $(LD) $(BOOTOBJ) $(INTERNALLDFLAGS) -T$(BOOTDIR)/linker.ld -o $@

.PHONY: image
image:

# Create the boot image and iso 
	@objcopy -I elf64-x86-64 -O efi-app-x86_64 Bootloader.elf BOOTX64.EFI
	@dd if=/dev/zero of=CharraOS.iso bs=1k count=1440
# Place Bootloader.elf into ::/EFI/BOOT
	@mformat -i CharraOS.iso -f 1440 ::
	@mmd -i CharraOS.iso ::/EFI
	@mmd -i CharraOS.iso ::/EFI/BOOT
	@mcopy -i CharraOS.iso BOOTX64.EFI ::/EFI/BOOT
# Place CharraOS.elf into ::/BIN
	@mmd -i CharraOS.iso ::/BIN
	@mcopy -i CharraOS.iso CharraOS.elf ::/BIN


.PHONY: clean
clean:
	@rm -rf $(OBJDIR)/
	@rm -rf CharraOS.elf
	@rm -rf Bootloader.elf
	@rm -rf BOOTX64.EFI
	@rm -rf CharraOS.iso

todolist:
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true