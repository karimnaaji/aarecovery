#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <string>
#include <iostream>

class PGMImage {
    public:
        PGMImage(int length, int width, int grayscale);
        ~PGMImage();
    
        float operator()(int i, int j) const;
        float& operator()(int i, int j);
        unsigned int getLength();
        unsigned int getWidth();
        unsigned int getGrayScale();
    private:
        std::string filename;
        unsigned int length;
        unsigned int width;
        unsigned int grayscale;
        float* data;
};

#endif
