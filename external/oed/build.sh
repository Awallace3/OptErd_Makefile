#/usr/bin/bash
rm -rf build
mkdir -p build
cmake -S. -Bbuild -G Ninja -DCMAKE_Fortran_COMPILER=x86_64-conda-linux-gnu-f95
ninja -C build
