//
// Created by tan on 10/06/21.
//

#ifndef IMAGEPROCESSINGLIBRARY_PIXEL_H
#define IMAGEPROCESSINGLIBRARY_PIXEL_H

#include <cstdint>

class Pixel {
    uint8_t red, green, blue, alpha;
    uint16_t channels;

public:
    Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint16_t channels);

    Pixel(const uint8_t *data, uint16_t channels);

    Pixel();

    Pixel(const Pixel &pix);

    uint8_t get_red() const;

    void set_red(uint8_t red);

    uint8_t get_green() const;

    void set_green(uint8_t green);

    uint8_t get_blue() const;

    void set_blue(uint8_t blue);

    uint8_t get_alpha() const;

    void set_alpha(uint8_t alpha);

    uint16_t get_channels() const;

    void set_all(uint8_t all);

    static uint8_t prevent_overflow(int16_t value);
};


#endif //IMAGEPROCESSINGLIBRARY_PIXEL_H
