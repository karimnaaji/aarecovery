#include "aarecovery.h"

PGMImage AARecovery::PerformAA(const PGMImage& original, const PGMImage& filtered) {
    PGMImage recovered(original.getLength(), original.getWidth());
    /*const int emIterations = 3;
    
    for(int i = 1; i < recovered.getLength() - 1; ++i) {
        for(int j = 1; j < recovered.getWidth() - 1; ++j) {
            float varianceDir;
            float center = 0;

            for(int k = i-1; k <= i+1; ++k) {
                for(int l = j-1; l <= j+1; ++l) {
                    center += original(k, l); 
                }
            }
            center /= 8;
        
            //varianceDir = 
        }
    }*/

    return recovered;
}

