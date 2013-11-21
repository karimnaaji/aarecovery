#include <iostream>

#include "pgmimage.h"
#include "ppmimage.h"
#include "netpbmloader.h"
#include "aarecovery.h"

int error(char* argv0) {
    std::cerr << "Usage: " << argv0 << " -o original -f filtered" << std::endl; 
    std::cerr << "Note: the file should be included in the " + MEDIA_PATH + " folder ";
    std::cerr << "and should be PPM (24bits) format" << std::endl; 
    return EXIT_FAILURE;
}

int main(int argc, char** argv) {
    std::string originalFilename;
    std::string filteredFilename;
    char c;

    if(argc < 2) {
        return error(argv[0]);
    }

    while((c = getopt(argc, argv, "o:f:")) != -1) {
        switch(c) {
            case 'o':
                originalFilename = std::string(optarg);
                break;
            case 'f':
                filteredFilename = std::string(optarg);
                break;
            case '?':
                return error(argv[0]);
        }
    }

    NetPBMLoader loader;
    PPMImage original = loader.loadPPM(originalFilename);
    PPMImage filtered;
    PPMImage recovered;

    if(filteredFilename.empty()) {
        int threshold;
        filtered = PPMImage(original);
        std::cout << "Perfoming a simple threshold on original image" << std::endl;
        std::cout << "Threshold value : ";
        std::cin >> threshold;

        for(int i = 0; i < filtered.getLength(); ++i) {
            for(int j = 0; j < filtered.getWidth(); ++j) {
                Vector3D color = filtered(i,j);
                filtered(i,j) = Vector3D((color.r + color.g + color.b) / 3);
                if(filtered(i,j).r > threshold)
                    filtered(i,j) = Vector3D(255);
            }
        }
    } else {
        filtered = loader.loadPPM(filteredFilename);
    }

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    recovered = AARecovery::PerformAA(original, filtered);

    loader.savePPM(filtered, originalFilename + std::string("_filtered"));
    loader.savePPM(recovered, originalFilename + std::string("_recovered"));

    return EXIT_SUCCESS;
}
