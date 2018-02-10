
# Create a new folder for the iso
mkdir -p iso/boot/grub

# Copy the kernel
cp bin/OS5.bin iso/boot/OS5.bin

# Copy test module
cp initrd iso/boot/initrd

# Copy the GRUB config file
cp grub.cfg iso/boot/grub/grub.cfg

# Make the rescue disc
grub-mkrescue -o OS5.iso iso
