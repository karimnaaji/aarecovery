#ifndef __PPM_IMAGE_H__
#define __PPM_IMAGE_H__

#include <string>

#include "vector3d.h"

class PPMImage {
    public:
        PPMImage();
        PPMImage(int length, int width);
        PPMImage(const PPMImage& image);
        PPMImage& operator=(const PPMImage& image);
        ~PPMImage();
    
        Vector3D operator()(int i, int j) const;
        Vector3D& operator()(int i, int j);
        unsigned int getLength() const;
        unsigned int getWidth() const;
        unsigned int getGrayscale() const;
    private:
        unsigned int length;
        unsigned int width;
        unsigned int grayscale;
        Vector3D* data;
};

#endif
