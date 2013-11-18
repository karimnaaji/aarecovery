#ifndef __PGM_IMAGE_H__
#define __PGM_IMAGE_H__

#include <string>
#include <iostream>

class PGMImage {
    public:
        PGMImage();
        PGMImage(int length, int width, int grayscale);
        PGMImage(const PGMImage& image);
        PGMImage& operator=(const PGMImage& image);
        ~PGMImage();
    
        float operator()(int i, int j) const;
        float& operator()(int i, int j);
        unsigned int getLength() const;
        unsigned int getWidth() const;
        unsigned int getGrayscale() const;

        void threshold(float threshold, float newValue);
    private:
        std::string filename;
        unsigned int length;
        unsigned int width;
        unsigned int grayscale;
        float* data;
};

#endif
