#ifndef __PGM_LOADER_H__
#define __PGM_LOADER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <ctime>

#include "defines.h"
#include "pgmimage.h"

class PGMLoader {
    public:
        PGMLoader();
        ~PGMLoader();
        static PGMImage load(std::string filename);
        static void save(PGMImage& pgmimage, std::string filename);
};

#endif
