#include "pgmimage.h"

PGMImage::PGMImage(int length_, int width_, int grayscale_) : 
    length(length_), 
    width(width_), 
    grayscale(grayscale_) {
    data = new float[length*width];
}

PGMImage::~PGMImage() {
    delete[] data;
}

float PGMImage::operator()(int i, int j) const {
    return data[i*width+j];
}

float& PGMImage::operator()(int i, int j) {
    return data[i*width+j];
}

unsigned int PGMImage::getLength() {
    return length;
}

unsigned int PGMImage::getWidth() {
    return width;
}

unsigned int PGMImage::getGrayScale() {
    return grayscale;
}
