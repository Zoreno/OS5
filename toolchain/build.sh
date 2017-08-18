# toolchain/build.sh Builds the cross compiler tool chain

#=========================================================
# Fetch all needed files
#=========================================================

# Get Binutils 2.28
wget ftp://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz

# Get GCC 6.4.0
wget ftp://ftp.gnu.org/gnu/gcc/gcc-6.4.0/gcc-6.4.0.tar.gz

# Get Installation Requisites
sudo apt-get install libgmp3-dev libmpfr-dev libisl-dev libcloog-isl-dev libmpc-dev texinfo

# Unpack source to src folder

mkdir -p src

tar -xf binutils-2.28.tar.gz -C src
tar -xf gcc-6.4.0.tar.gz -C src

# Cleanup when done

rm -f binutils-2.28.tar.gz
rm -f gcc-6.4.0.tar.gz

#=========================================================
# Build Binutils
#=========================================================

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

chmod +x src/*

cd src

mkdir -p build-binutils
cd build-binutils

../binutils-2.28/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror

make
make install

cd ..

#=========================================================
# Build GCC
#=========================================================

mkdir -p build-gcc
cd build-gcc

../gcc-6.4.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers

make all-gcc
make all-target-libgcc

make install-gcc
make install-target-libgcc

#=========================================================
# Final Cleanup
#=========================================================

rm -rf src
