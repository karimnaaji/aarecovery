#include <iostream>

#include "pgmimage.h"
#include "pgmloader.h"
#include "aarecovery.h"

int main() {
    PGMImage original = PGMLoader::load("photograph");
    PGMImage filtered(original);
    PGMImage recovered;

    filtered.threshold(100, 255);

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    recovered = AARecovery::PerformAA(original, filtered);

    PGMLoader::save(filtered, "photograph_filtered");
    PGMLoader::save(recovered, "photograph_recovered");
    return 0;
}
