# cmake_minimum_required(VERSION <specify CMake version here>)
project(ImageProcessingLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcessingLibrary main.cpp Image.cpp Image.h include/stb_image.h include/stb_image_write.h)