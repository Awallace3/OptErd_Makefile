#/usr/bin/bash
rm -rf build
mkdir -p build
cmake -S. -Bbuild -G Ninja -DCMAKE_INSTALL_PREFIX=..
ninja -C build install
