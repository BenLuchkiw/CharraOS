wsl clear

wsl make clean
wsl make 

qemu-system-x86_64.exe -boot d -cdrom CharraOS.iso -m 512

rem objcopy -I elf64-x86-64 -O efi-app-x86_64 kernel_x64.elf BOOTX64.EFI
rem dd if=/dev/zero of=fat.img bs=1k count=1440
rem mformat -i fat.img -f 1440 ::
rem mmd -i fat.img ::/EFI
rem mmd -i fat.img ::/EFI/BOOT
rem mcopy -i fat.img BOOT*.EFI ::/EFI/BOOT