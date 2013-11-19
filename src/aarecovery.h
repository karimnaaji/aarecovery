#ifndef __AA_RECOVERY_H__
#define __AA_RECOVERY_H__

#include "ppmimage.h"
#include "vector2d.h"
#include "vector3d.h"

class AARecovery {
    public:
        static PPMImage PerformAA(const PPMImage& original, const PPMImage& filtered);
};

#endif
