cmake_minimum_required(VERSION 3.10)
project(wbr VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(wbr src/main.cpp)

# Include directories
target_include_directories(wbr PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Installation
install(TARGETS wbr DESTINATION bin)
