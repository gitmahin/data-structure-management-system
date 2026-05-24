cmake_minimum_required(VERSION 3.23)

# Name the project
project(App)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create new library named AppLib
add_library(AppLib)

# Name the executable file
add_executable(App)

# Include all header files
file(GLOB_RECURSE HEADERS
    "./src/include/*.h"      
)

# Include all source files
file(GLOB_RECURSE SOURCES
    "./src/lib/*.cpp"  
)

# Include directories as public need to make AppLib
target_include_directories(AppLib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lib 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)


# Build the library
target_sources(AppLib
    PRIVATE
        ${SOURCES}

    PUBLIC
    FILE_SET HEADERS

    FILES
        ${HEADERS}
    
)

# Create the "App"
target_sources(App
    PRIVATE
        # include app's main file
        src/main.cpp
)

# link all the libraries to the created "App"
target_link_libraries(App
    PRIVATE
        AppLib
)