#include <iostream>

#include "pgmimage.h"
#include "ppmimage.h"
#include "netpbmloader.h"
#include "aarecovery.h"
#include "effects.h"

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
        char changeColor;
        filtered = PPMImage(original);

        std::cout << "Change color algorithm? (y/n) ";
        std::cin >> changeColor;

        if(changeColor == 'y') {
            Vector3D color;
            float maxDistance;

            std::cout << "x: ";
            std::cin >> color.x;
            std::cout << "y: ";
            std::cin >> color.y;
            std::cout << "z: ";
            std::cin >> color.z;
            std::cout << "Max distance: ";
            std::cin >> maxDistance;

            ChangeColor(filtered, color, maxDistance);
        } else {
            std::cout << "Perfoming a simple threshold on original image" << std::endl;
            std::cout << "Threshold value: ";
            std::cin >> threshold;
            std::cout << "Performing thresholding" << std::endl;

            Threshold(filtered, threshold);
        }
    } else {
        filtered = loader.loadPPM(filteredFilename);
    }

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    const clock_t begin = clock();
    recovered = PerformAA(original, filtered);
    std::cout << "Time: " << (float)(clock() - begin) /  CLOCKS_PER_SEC << "s." << std::endl;

    loader.savePPM(filtered, originalFilename + std::string("_filtered"));
    loader.savePPM(recovered, originalFilename + std::string("_recovered"));

    return EXIT_SUCCESS;
}
