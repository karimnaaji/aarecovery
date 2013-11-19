#include <iostream>

#include "pgmimage.h"
#include "ppmimage.h"
#include "netpbmloader.h"
#include "aarecovery.h"

int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " ppm_filename" << std::endl; 
        std::cerr << "Note: the file should be included in the " + MEDIA_PATH + " folder" << std::endl; 
        return EXIT_FAILURE;
    }

    std::string filename = std::string(argv[1]);
    NetPBMLoader loader;
    PPMImage original = loader.loadPPM(filename);
    PPMImage filtered(original);
    PPMImage recovered;

    //filtered.threshold(100, 255);

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    recovered = AARecovery::PerformAA(original, filtered);

    loader.savePPM(filtered, filename + std::string("_filtered"));
    loader.savePPM(recovered, filename + std::string("_recovered"));

    return EXIT_SUCCESS;
}
