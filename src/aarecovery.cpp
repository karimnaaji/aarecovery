#include "aarecovery.h"

PPMImage AARecovery::PerformAA(const PPMImage& original, const PPMImage& filtered) {
    NetPBMLoader loader;
    PPMImage recovered(original.getLength(), original.getWidth());
    PPMImage maxVarDir(original.getLength(), original.getWidth());

    for(int i = 1; i < recovered.getLength() - 1; ++i) {
        for(int j = 1; j < recovered.getWidth() - 1; ++j) {
            PPMImage neighbors(3,3);

            // construct neighbors
            for(int k = i-1; k <= i+1; ++k) {
                for(int l = j-1; l <= j+1; ++l) {
                    neighbors((k-i)+1, (l-j)+1) = original(k,l);
                }
            }

            // colors are changing most rapidly considering this direction
            Vector3D varDir = MaximumVarianceDirection(neighbors);

            Vector2D maxColorPos;
            Vector2D minColorPos;
            if(FindExtremeColors(neighbors, varDir, maxColorPos, minColorPos)) {
                std::cout << minColorPos.x << " " << minColorPos.y << std::endl;   
                std::cout << maxColorPos.x << " " << maxColorPos.y << std::endl;   
            }

            // only for visualization
            maxVarDir(i,j) = varDir * 255;
        }
    }   

    loader.savePPM(maxVarDir, "max_variance_direction");

    return recovered;
}

bool AARecovery::FindExtremeColors(const PPMImage& neighbors, const Vector3D& varDir, Vector2D& maxColorPos, Vector2D& minColorPos) {
    float tmin = 1.0;
    float tmax = -1.0;

    for(int i = 0; i < neighbors.getLength(); ++i) {
        for(int j = 0; j < neighbors.getWidth(); ++j) {
            // don't treat the current pixel 
            if(i == 1 && j == 1) 
                continue;

            Vector3D pColor = neighbors(i,j);
            Vector3D centerPixel = neighbors(1,1);
            Vector3D v = pColor - centerPixel;
            Vector3D dist;

            // project the vector directed by the current pixel to the center pixel
            // on the direction of the maximum variance
            float t = varDir.dot(v);
            // construct the vector distance to the straight line directed 
            // by the maximum variance direction
            dist = pColor - (centerPixel + varDir * t);
            // compute the square distance of this vector
            float d = dist.dot(dist);

            // threshold too distant colors
            if(d > 3*SIGMA_D) {
                continue;
            }

            if(t < tmin) {
                tmin = t;
                minColorPos = Vector2D(i,j);
            }
            if(t > tmax) {
                tmax = t;
                maxColorPos = Vector2D(i,j);
            }
        }
    }
    return tmin <= 0 && tmax >= 0 && abs(tmin - tmax) > EPSILON;
}

Vector3D AARecovery::MaximumVarianceDirection(PPMImage& neighbors) {
    // the distance vector from the average value of neighbors
    Vector3D* dAverage = new Vector3D[neighbors.getSize()];
    // the average value computed considering the neighbors
    Vector3D average;
    // the variance direction
    Vector3D vDirection;

    // compute the average
    for(int i = 0; i < neighbors.getLength(); ++i) {
        for(int j = 0; j < neighbors.getWidth(); ++j) {
            average += neighbors(i,j);
        }
    }
    average /= neighbors.getSize();
    // compute the distance from the average color value
    for(int i = 0; i < neighbors.getLength(); ++i) {
        for(int j = 0; j < neighbors.getWidth(); ++j) {
            dAverage[i*neighbors.getLength()+j] = neighbors(i,j) - average;
        }
    }

    // expectation maximization iterations
    vDirection = Vector3D(average.normalize() + 1e-3);
    for(int emIter = 0; emIter < 3; ++emIter) {
        Vector3D t(1e-4);
        for(int i = 0; i < neighbors.getSize(); ++i) {
            t += dAverage[i] * dAverage[i].dot(vDirection);
        }
        vDirection = t.normalize();
    }

    delete[] dAverage;

    return vDirection;
}
