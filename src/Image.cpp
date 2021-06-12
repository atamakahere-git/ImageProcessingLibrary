//
// Created by tan on 07/06/21.
//

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

#include <exception>
#include <stdexcept>

Image::Image(const char *filename) {
    if (Image::open(filename)) {
        printf("Successfully opened file");
    } else {
        printf("Failed to read %s", filename);
    }
    Image::pixels = Image::height * Image::width;
    Image::size = Image::pixels * Image::channels;
}

Image::Image(int width, int height, int channels)
        : width{width}, height{height}, channels{channels} {
    Image::pixels = width * height;
    Image::size = Image::pixels * channels;
    Image::data = new uint8_t[size];
}

Image::Image(const Image &img) : Image(img.get_width(), img.get_height(), img.get_channels()) {
    memcpy(Image::data, img.get_data(), Image::size);
}

bool Image::open(const char *filename) {
    int *h = &height;
    int *w = &width;
    int *c = &channels;
    Image::data = stbi_load(filename, w, h, c, 0);
    return Image::data != nullptr;
}

bool Image::save(const char *filename) {
    ImageType type = get_file_type(filename);
    int success;
    switch (type) {
        case PNG:
            success = stbi_write_png(filename, Image::width, Image::height, Image::channels, data,
                                     Image::width * Image::channels);
            break;
        case BMP:
            success = stbi_write_bmp(filename, Image::width, Image::height, Image::channels, data);
            break;
        case JPG:
            success = stbi_write_jpg(filename, Image::width, Image::height, Image::channels, data, 100);
            break;
        case TGA:
            success = stbi_write_tga(filename, Image::width, Image::height, Image::channels, data);
            break;
    }
    return success != 0;
}


bool Image::save_png(const char *filename) {
    return stbi_write_png(filename, Image::width, Image::height, Image::channels, data,
                          Image::width * Image::channels);
}

bool Image::save_jpg(const char *filename, uint16_t quality = 100) {
    if (quality > 100) quality = 100;
    return stbi_write_jpg(filename, Image::width, Image::height, Image::channels, data, 100);
}

bool Image::save_tga(const char *filename) {
    return stbi_write_tga(filename, Image::width, Image::height, Image::channels, data);
}


ImageType Image::get_file_type(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (ext != nullptr) {
        if (strcmp(ext, ".png") == 0) {
            return PNG;
        } else if (strcmp(ext, ".jpg") == 0) {
            return JPG;
        } else if (strcmp(ext, ".bmp") == 0) {
            return BMP;
        } else if (strcmp(ext, ".tga") == 0) {
            return TGA;
        }
    }
    return PNG;
}


Image::~Image() {
    stbi_image_free(Image::data);
}

size_t Image::get_size() const {
    return size;
}

void Image::set_size(size_t size) {
    Image::size = size;
}

int Image::get_width() const {
    return width;
}

void Image::set_width(int width) {
    Image::width = width;
}

int Image::get_height() const {
    return height;
}

void Image::set_height(int height) {
    Image::height = height;
}

int Image::get_channels() const {
    return channels;
}

void Image::set_channels(int channels) {
    Image::channels = channels;
}

uint8_t *Image::get_data() const {
    return data;
}

size_t Image::get_pixel_data_pointer_offset(size_t pixel_index) const {
    if (pixel_index > Image::pixels) {
        throw std::out_of_range("Image :: get_pixel_data_pointer_offset() : index is out of range");
    }
    size_t data_pointer_offset = pixel_index * Image::channels;
    return data_pointer_offset;
}

size_t Image::get_pixel_data_pointer_offset_xy(size_t pixel_index_x, size_t pixel_index_y) const {
    size_t pixel_index = pixel_index_y * Image::width + pixel_index_x;
    return Image::get_pixel_data_pointer_offset(pixel_index);
}

Pixel *Image::get_pixel(size_t pixel_index) const {
    size_t data_pointer_offset = Image::get_pixel_data_pointer_offset(pixel_index);
    return new Pixel(Image::get_data() + data_pointer_offset, Image::channels);
}

Pixel *Image::get_pixel(size_t pixel_index_x, size_t pixel_index_y) const {
    size_t pixel_index = pixel_index_y * Image::width + pixel_index_x;
    return Image::get_pixel(pixel_index);
}

bool Image::set_pixel(size_t pixel_index, const Pixel &pixel, bool force_min_channels = false) {
    if (pixel_index > Image::pixels) {
        throw std::out_of_range("Image :: set_pixel() : index is out of range");
    }
    if ((!force_min_channels) and pixel.get_channels() != Image::channels) {
        throw std::range_error("Image :: set_pixel() : Pixel and Image channels doesn't match");
    }
    uint16_t channel = Image::channels;
    if (force_min_channels) { channel = std::min(channel, pixel.get_channels()); }
    size_t data_pointer_offset = Image::get_pixel_data_pointer_offset(pixel_index);
    switch (channel) {
        case 4:
            *(Image::get_data() + data_pointer_offset + 3) = pixel.get_alpha();
        case 3:
            *(Image::get_data() + data_pointer_offset + 2) = pixel.get_blue();
        case 2:
            *(Image::get_data() + data_pointer_offset + 1) = pixel.get_green();
        case 1:
            *(Image::get_data() + data_pointer_offset + 0) = pixel.get_red();
    }

}

bool Image::set_pixel(size_t pixel_index_x, size_t pixel_index_y, const Pixel &pixel, bool force_min_channels = false) {
    size_t pixel_index = Image::get_pixel_data_pointer_offset_xy(pixel_index_x, pixel_index_y);
    Image::set_pixel(pixel_index, pixel, force_min_channels);
}

size_t Image::get_pixels() const {
    return Image::pixels;
}
