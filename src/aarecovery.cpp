#include "aarecovery.h"

PGMImage AARecovery::PerformAA(const PGMImage& original, const PGMImage& filtered) {
    PGMImage recovered(original.getLength(), original.getWidth(), original.getGrayscale());

    // for each pixel of recovered image {
    //      1. compute maximum variance direction in original image :
    //         - for each neighbor {
    //              
    //           }
    // }
    
    for(int i = 0; i < recovered.getLength(); ++i) {
        for(int j = 0; j < recovered.getWidth(); ++j) {
            Vector2D vec(4,4);
        }
    }

    return recovered;
}
