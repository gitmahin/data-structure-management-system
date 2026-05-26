## Software Compatibility

- GCC Version: 16.x.x
- Operating System: Linux
- Clang Version: 22.x.x


## Download CMake (If not installed)

- [Windows x64 Installer](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-windows-x86_64.msi)
- [macOS 10.13 or later](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-macos-universal.dmg)
- [macOS 10.10 or later](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-macos10.10-universal.dmg)
- [Linux x86_64](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-linux-x86_64.sh)
- [Linux aarch64](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-linux-aarch64.sh)

### Windows Setup
- Download & Install CMake
- Install MinGW for c++ compiler
Update GCC to 16.x.x
```shell
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-gcc
gcc --version
```
```shell
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B build
cmake --build build
```
