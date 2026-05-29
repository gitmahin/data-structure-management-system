## Software Compatibility

- GCC Version: 16.x.x
- Supported Operating System: Cross-platform
- Clang Version: 22.x.x

## Download CMake (If not installed)

- [Windows x64 Installer](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-windows-x86_64.msi)
- [macOS 10.13 or later](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-macos-universal.dmg)
- [macOS 10.10 or later](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-macos10.10-universal.dmg)
- [Linux x86_64](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-linux-x86_64.sh)
- [Linux aarch64](https://github.com/Kitware/CMake/releases/download/v4.3.2/cmake-4.3.2-linux-aarch64.sh)

### POSIX-compliant Systems Setup
Arch:
```bash
sudo pacman -Syu
gcc --version
```

Debian:
```bash
sudo apt install gcc-16 g++-16
```

Mac:
```shell
brew install gcc@16
```

Enter into the project root and run
```bash
cmake -B build
cd build
make
./App
```

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

Enter into the project root and run
```shell
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -B build
cmake --build build
cd build
./App
```

## Application UI:
### Home Page:
```bash
========================================
DATA STRUCTURE MANAGEMENT SYSTEM
========================================

========================================
|          Data Structure Menu         |
========================================
| a -> Array Operations                |
| b -> Linked List Operations          |
| c -> Stack Operations                |
| d -> Queue Operations                |
| e -> Searching Operations            |
| f -> Sorting Operations              |
| g -> Graph Operations                |
| h -> Tree Operations                 |
========================================
| z -> Exit                            |
========================================
Choose an option: 
```
---
### Array Operations
```bash
========================================
DATA STRUCTURE MANAGEMENT SYSTEM
[Array Operations]
========================================

========================================
|            Operations Menu           |
========================================
| a -> Create Array                    |
| b -> Traverse Array                  |
| c -> Insert at Beginning             |
| d -> Insert at End                   |
| e -> Insert at Any Position          |
| f -> Delete from Beginning           |
| g -> Delete from End                 |
| h -> Delete from Any Position        |
========================================
| z -> Main Menu                       |
========================================
Choose an array operation: 
```
#### Create Array
```bash
=====================================
|           Choose Data Type        |
=====================================
| a -> int                          |
| b -> double                       |
| c -> string                       |
| d -> char                         |
=====================================
| z -> Back                         |
=====================================
Select the data type you want: 
```

#### Insertion
```bash
Current Array State:
23
24

Inserting element at the beginning.
Enter element [int]: 
```
#### Deletion By Index
```bash
!!!!!! Performing Deletion !!!!!!
Current Array State: [2] elements.
23
24
Enter index between 0 to 1: 1   
Element deleted successfully.

Deletion Result
Previous Number of Elements: 2
Current Number of Elements: 1
Deleted Element: 24 [Index: 1]
Press any key to return to the Array Operations menu....
```
---