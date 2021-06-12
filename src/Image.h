//
// Created by tan on 07/06/21.
//

#ifndef IMAGEPROCESSINGLIBRARY_IMAGE_H
#define IMAGEPROCESSINGLIBRARY_IMAGE_H

#include <cstdint>
#include <cstdio>

#include "Pixel.h"

enum ImageType {
    PNG, JPG, BMP, TGA
};

class Image {
private:
    uint8_t *data = nullptr;
    size_t size = 0;
    size_t pixels;
    int width;
    int height;
    int channels;

    size_t get_pixel_data_pointer_offset(size_t pixel_index) const;

    size_t get_pixel_data_pointer_offset_xy(size_t pixel_index_x, size_t pixel_index_y) const;

public:
    explicit Image(const char *filename);

    Image(int width, int height, int channels);

    Image(const Image &img);

    size_t get_pixels() const;

    ~Image();

    bool open(const char *filename);

    bool save(const char *filename);

    bool save_jpg(const char *filename, uint16_t quality);

    bool save_png(const char *filename);

    bool save_tga(const char *filename);

    static ImageType get_file_type(const char *filename);

    size_t get_size() const;

    void set_size(size_t size);

    int get_width() const;

    void set_width(int width);

    int get_height() const;

    void set_height(int height);

    int get_channels() const;

    void set_channels(int channels);

    uint8_t *get_data() const;

    Pixel *get_pixel(size_t pixel_index) const;

    Pixel *get_pixel(size_t pixel_index_x, size_t pixel_index_y) const;

    bool set_pixel(size_t pixel_index, const Pixel &pixel, bool force_min_channels);

    bool set_pixel(size_t pixel_index_x, size_t pixel_index_y, const Pixel &pixel, bool force_min_channels);
};


#endif //IMAGEPROCESSINGLIBRARY_IMAGE_H
