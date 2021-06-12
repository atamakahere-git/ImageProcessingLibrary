//
// Created by tan on 10/06/21.
//

#include "Pixel.h"

Pixel::Pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, uint16_t channels)
        : red{red}, green{green}, blue{blue}, alpha{alpha}, channels{channels} {}

Pixel::Pixel(const uint8_t *data, uint16_t channels) {
    switch (channels) {
        case 4 :
            Pixel::set_alpha(*(data + 3));
        case 3 :
            Pixel::set_blue(*(data + 2));
        case 2 :
            Pixel::set_green(*(data + 1));
        case 1 :
            Pixel::set_red(*(data + 0));
            break;
        default:
            Pixel::set_all(0);
    }
}


Pixel::Pixel(const Pixel &pix) : Pixel(pix.get_red(), pix.get_green(), pix.get_blue(), pix.get_alpha(),
                                       pix.get_channels()) {

}

uint8_t Pixel::get_red() const {
    return red;
}

void Pixel::set_red(uint8_t red) {
    Pixel::red = red;
}

uint8_t Pixel::get_green() const {
    return green;
}

void Pixel::set_green(uint8_t green) {
    Pixel::green = green;
}

uint8_t Pixel::get_blue() const {
    return blue;
}

void Pixel::set_blue(uint8_t blue) {
    Pixel::blue = blue;
}

uint8_t Pixel::get_alpha() const {
    return alpha;
}

void Pixel::set_alpha(uint8_t alpha) {
    Pixel::alpha = alpha;
}

uint16_t Pixel::get_channels() const {
    return channels;
}

void Pixel::set_all(uint8_t all) {
    Pixel::set_red(all);
    Pixel::set_green(all);
    Pixel::set_blue(all);
    Pixel::set_alpha(all);
}

Pixel::Pixel() : Pixel(0, 0, 0, 0, 0) {

}

uint8_t Pixel::prevent_overflow(int16_t value) {
    if (value > UINT8_MAX) value = UINT8_MAX;
    else if (value < 0) value = 0;
    return value;
}
