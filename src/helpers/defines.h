#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <string>

#define MEDIA_PATH      std::string("media/")
#define PGM_EXT         std::string(".pgm")
#define PPM_EXT         std::string(".ppm")
#define COLOR_LEVELS    255
// value to perform threshold of too distant vectors
#define SIGMA_D         0.2 * COLOR_LEVELS
// edge threshold
#define SIGMA_E         0.05 * COLOR_LEVELS
#define EPSILON         1e-4

#endif
