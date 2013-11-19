#include <iostream>

#include "pgmimage.h"
#include "netpbmloader.h"
#include "aarecovery.h"
#include "vector3d.h"

int main() {
    NetPBMLoader loader;
    PGMImage original = loader.loadPGM("photograph");
    PGMImage filtered(original);
    PGMImage recovered;

    PPMImage image = loader.loadPPM("test");

    loader.savePPM(image, "test");

    filtered.threshold(100, 255);

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    recovered = AARecovery::PerformAA(original, filtered);

    loader.savePGM(filtered, "photograph_filtered");
    loader.savePGM(recovered, "photograph_recovered");

    return 0;
}
