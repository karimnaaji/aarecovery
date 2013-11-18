#include "aarecovery.h"

PGMImage AARecovery::PerformAA(const PGMImage& original, const PGMImage& filtered) {
    PGMImage recovered(original.getLength(), original.getWidth(), original.getGrayscale());

    return recovered;
}
