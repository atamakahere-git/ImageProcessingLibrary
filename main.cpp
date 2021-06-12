#include <iostream>
#include "src/Image.h"
#include "src/Pixel.h"

using std::cout;
using std::endl;

int main() {
    cout << "Test file" << endl;
    Image img = Image("test.jpg");
    for (int i = 0; i < img.get_pixels() - 1; ++i) {
        Pixel *px = img.get_pixel(i);
        px->set_blue(Pixel::prevent_overflow(px->get_blue()+30));
        px->set_green(Pixel::prevent_overflow(px->get_green()+30));
        px->set_red(Pixel::prevent_overflow(px->get_red() + 30));
        img.set_pixel(i, *px, true);
        delete px;
    }
    img.save_png("test.png");

    return 0;
}
