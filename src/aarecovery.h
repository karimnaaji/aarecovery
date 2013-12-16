#ifndef __AA_RECOVERY_H__
#define __AA_RECOVERY_H__

#include "ppmimage.h"
#include "vector2d.h"
#include "vector3d.h"
#include "netpbmloader.h"
#include "defines.h"

#include <vector>
#include <cmath>

const float SIGMA_D = 0.5 * COLOR_LEVELS;
const float SIGMA_E = 0.05 * COLOR_LEVELS;

PPMImage PerformAA(const PPMImage& original, const PPMImage& filtered);
float Sobel(const PPMImage& neighbors);
Vector3D MaximumVarianceDirection(PPMImage& neighbors);
bool FindExtremeColors(const PPMImage& neighbors, const Vector3D& varDir, Vector2D& maxColorPos, Vector2D& minColorPos);
void EM(Vector3D* average, int n, Vector3D& direction, int nNeighbor);

#endif
