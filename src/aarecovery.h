#ifndef __AA_RECOVERY_H__
#define __AA_RECOVERY_H__

#include "pgmimage.h"

class AARecovery {
    public:
        static PGMImage PerformAA(const PGMImage& original, const PGMImage& filtered);
};

#endif
