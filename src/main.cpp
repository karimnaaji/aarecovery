#include <iostream>

#include "pgmimage.h"
#include "pgmloader.h"

int main() {
    PGMImage image = PGMLoader::load("photograph");
    //std::cout << image(image.getLength() - 1, image.getWidth() - 1) << std::endl;
    PGMLoader::save(image, "example");
    return 0;
}
