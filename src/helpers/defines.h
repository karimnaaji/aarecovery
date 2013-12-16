#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <string>

#define MEDIA_PATH      std::string("media/")
#define PGM_EXT         std::string(".pgm")
#define PPM_EXT         std::string(".ppm")
#define COLOR_LEVELS    255.0f
#define EPSILON         1e-4f

#define GAUSS(x,sigma) exp(-pow(x,2)/sigma)

#endif
