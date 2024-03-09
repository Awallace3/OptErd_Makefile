#/usr/bin/bash
rm -rf build
mkdir -p build
cmake -S. -Bbuild -G Ninja
ninja -C build
