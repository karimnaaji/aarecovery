#include "effects.h"

void Luminance(PPMImage& image) {
    for(int i = 0; i < image.getLength(); ++i) {
        for(int j = 0; j < image.getWidth(); ++j) {
            Vector3D color = image(i,j);
            image(i,j) = Vector3D((color.r + color.g + color.b) / 3);
        }
    }
}

void Threshold(PPMImage& image, float threshold) {
    for(int i = 0; i < image.getLength(); ++i) {
        for(int j = 0; j < image.getWidth(); ++j) {
            Vector3D color = image(i,j);
            image(i,j) = Vector3D((color.r + color.g + color.b) / 3);
            if(image(i,j).r > threshold)
                image(i,j) = Vector3D(255);
            else 
                image(i,j) = Vector3D(0);
        }
    }
}

void ChangeColor(PPMImage& image, Vector3D colorIn, float maxDistance) {
    for(int i = 0; i < image.getLength(); ++i) {
        for(int j = 0; j < image.getWidth(); ++j) {
            Vector3D color = image(i, j);
            float dist = (color - colorIn).length();
            if(dist <= maxDistance) {
                image(i, j) = (colorIn * color) / 255;
            }
        }   
    }
}
