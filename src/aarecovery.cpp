#include "aarecovery.h"

PPMImage AARecovery::PerformAA(const PPMImage& original, const PPMImage& filtered) {
    NetPBMLoader loader;
    PPMImage recovered(original.getLength(), original.getWidth());
    PPMImage maxVarDir(original.getLength(), original.getWidth());
    PPMImage sobel(original.getLength(), original.getWidth());

    for(int i = 1; i < recovered.getLength() - 1; ++i) {
        for(int j = 1; j < recovered.getWidth() - 1; ++j) {
            PPMImage neighbors(3,3);
            PPMImage neighborsAliased(3,3);
            Vector3D pixel = original(i,j);
            Vector3D pixelAlias = filtered(i,j);
            float t = 0;
            float metric = 0;

            // construct neighbors
            for(int k = i-1; k <= i+1; ++k) {
                for(int l = j-1; l <= j+1; ++l) {
                    neighbors((k-i)+1, (l-j)+1) = original(k,l);
                }
            }

            for(int k = i-1; k <= i+1; ++k) {
                for(int l = j-1; l <= j+1; ++l) {
                    neighborsAliased((k-i)+1, (l-j)+1) = filtered(k,l);
                }
            }

            // colors are changing most rapidly considering this direction
            Vector3D varDir = MaximumVarianceDirection(neighbors);

            Vector2D maxColorPos;
            Vector2D minColorPos;

            // compute the two maximum colors along the straight line directed by varDir
            if(FindExtremeColors(neighbors, varDir, maxColorPos, minColorPos)) {
                Vector3D ca = neighbors(minColorPos.x, minColorPos.y);
                Vector3D cb = neighbors(maxColorPos.x, maxColorPos.y);
                Vector3D cacb = cb - ca;
                float d2cacb = cacb.dot(cacb);
                t = (pixel - ca).dot(cacb) / d2cacb;
                Vector3D d = pixel - (t * cacb) - ca;
                float dist2 = d.dot(d);
                metric = exp(-dist2/SIGMA_D);
            }

            float edge = Sobel(neighbors);
            edge *= Sobel(neighborsAliased);
            float fEdge = 1 - exp(-edge*edge / SIGMA_E);
            metric *= (fEdge >= 1e-2) ? 1 : 0;
            metric *= fEdge;

            Vector3D cbAliased = neighborsAliased(maxColorPos.x, maxColorPos.y);
            Vector3D caAliased = neighborsAliased(minColorPos.x, minColorPos.y);
            Vector3D interpColor = caAliased * (1-t) + cbAliased * t;

            recovered(i,j) = metric * interpColor + (1-metric) * pixelAlias;
            sobel(i,j) = Vector3D(sqrt(edge));
            maxVarDir(i,j) = varDir * 255;
        }
    }   

    loader.savePPM(maxVarDir, "max_variance_direction");
    loader.savePPM(sobel, "sobel");

    return recovered;
}

float AARecovery::Sobel(const PPMImage& neighbors) {
    Vector3D* h = new Vector3D[3];
    Vector3D* v = new Vector3D[3];

    for(int i = 0; i < 3; ++i) {
        h[i] = neighbors(i,0) + 2*neighbors(i,1) + neighbors(i,2);
        v[i] = neighbors(0,i) + 2*neighbors(1,i) + neighbors(2,i);
    }

    Vector3D gx = (Vector3D::abs(h[1]-h[2]) + Vector3D::abs(h[0]-h[1])) / 4.0;
    Vector3D gy = (Vector3D::abs(v[1]-v[2]) + Vector3D::abs(v[0]-v[1])) / 4.0;

    delete[] h;
    delete[] v;
    return gx.dot(gx) + gy.dot(gy);
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

            float t = varDir.dot(v);
            // construct the vector distance to the straight line directed 
            // by the maximum variance direction
            dist = pColor - (centerPixel + varDir * t);
            // compute the square distance of this vector
            float d2 = dist.dot(dist);

            // threshold too distant colors
            if(d2 >= 3*SIGMA_D) {
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
