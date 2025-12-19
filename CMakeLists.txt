cmake_minimum_required(VERSION 3.17)
project(STK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define your source files here
set(SOURCES
        src/lexer/main.cpp
        src/lexer/lexer.cpp
        src/lexer/lexer.hpp
        src/lexer/tokens.hpp
)

# FIXED: Renamed target from 'STK' back to 'Cpp' to match your build configuration
add_executable(Cpp ${SOURCES})

# Add the include directory so main.cpp can find "lexer.hpp"
target_include_directories(Cpp PRIVATE src/lexer)