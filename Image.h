//
// Created by tan on 07/06/21.
//

#ifndef IMAGEPROCESSINGLIBRARY_IMAGE_H
#define IMAGEPROCESSINGLIBRARY_IMAGE_H

#include <stdint.h>
#include <cstdio>

enum ImageType {
    PNG, JPG, BMP, TGA
};

class Image {
private:
    uint8_t *data = nullptr;
    size_t size = 0;
    int width;
    int height;
    int channels;

public:
    explicit Image(const char *filename);

    Image(int width, int height, int channels);

    Image(const Image &img);

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
};


#endif //IMAGEPROCESSINGLIBRARY_IMAGE_H
