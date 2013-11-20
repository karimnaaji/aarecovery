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

    PPMImage testImage(3,3);
    testImage(0,0) = Vector3D(80,10,20);
    testImage(0,1) = Vector3D(123,200,179);
    testImage(0,2) = Vector3D(150,200,190);
    testImage(1,0) = Vector3D(159,201,180);
    testImage(1,1) = Vector3D(153,200,200);
    testImage(1,2) = Vector3D(151,201,198);
    testImage(2,0) = Vector3D(149,203,195);
    testImage(2,1) = Vector3D(150,205,200);
    testImage(2,2) = Vector3D(180,230,230);

    //filtered.threshold(100, 255);
    for(int i = 0; i < filtered.getLength(); ++i) {
        for(int j = 0; j < filtered.getWidth(); ++j) {
            Vector3D color = filtered(i,j);
            filtered(i,j) = Vector3D((color.r + color.g + color.b) / 3);
            if(filtered(i,j).r > 180) filtered(i,j) = Vector3D(255);
        }
    }

    std::cout << "Performing anti-aliasing recovery" << std::endl;
    recovered = AARecovery::PerformAA(original, filtered);
    loader.savePPM(testImage, "testImage8x8");

    loader.savePPM(filtered, filename + std::string("_filtered"));
    loader.savePPM(recovered, filename + std::string("_recovered"));

    return EXIT_SUCCESS;
}
