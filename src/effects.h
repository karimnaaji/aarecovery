#ifndef EFFECTS_H
#define EFFECTS_H

#include "ppmimage.h"

void Threshold(PPMImage& image, float threshold);
void Luminance(PPMImage& image);
void ChangeColor(PPMImage& image, Vector3D color, float maxDistance);

#endif
