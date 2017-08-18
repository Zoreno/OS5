# Launch Qemu and setup debugging port

qemu-system-i386 -s -S -cdrom OS5.iso &

# Too much needless text
ddd --gdb -command=gdbdebug > /dev/null

