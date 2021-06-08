#include <iostream>
#include "Image.h"

using std::cout;
using std::endl;

int main() {
    cout << "Test file" << endl;
    Image img = Image("test.png");
    img.save("new_test.png");
    img.save_jpg("new_test.jpg",50);
    Image img2(img);
    img2.save_tga("new_test.tga");
    img2.save("copy.png");
    return 0;
}
