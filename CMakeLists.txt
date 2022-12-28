# cmake_minimum_required(VERSION <specify CMake version here>)
project(ImageProcessingLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcessingLibrary main.cpp src/Image.cpp src/Image.h stb/stb_image.h stb/stb_image_write.h src/Pixel.cpp src/Pixel.h)