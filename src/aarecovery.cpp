#include "aarecovery.h"

PPMImage PerformAA(const PPMImage& original, const PPMImage& filtered) {
    NetPBMLoader loader;
    PPMImage recovered(original.getLength(), original.getWidth());
    PPMImage maxVarDir(original.getLength(), original.getWidth());
    PPMImage sobel(original.getLength(), original.getWidth());

    for(int i = 0; i < recovered.getLength(); ++i) {
        for(int j = 0; j < recovered.getWidth(); ++j) {
            // don't treat border pixels
            if(i == 0 || j == 0 || i == recovered.getLength()-1 || j == recovered.getWidth()-1) {
                recovered(i,j) = filtered(i,j);
                continue;
            }
            PPMImage neighbors(3,3);
            PPMImage neighborsAliased(3,3);
            Vector3D pixel = original(i,j);
            Vector3D pixelAlias = filtered(i,j);
            float alpha = 0;
            float beta = 0;
            float dp = 0;
            float Gd = 0;
            float ep = 0;
            float Ge = 0;

            // construct neighbors of aliased and original images
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
                Vector3D d;

                alpha = (pixel - ca).dot(cacb) / cacb.dot(cacb);
                d = pixel - (alpha * cacb) - ca;
                dp = d.length();
                Gd = GAUSS(dp, SIGMA_D);
            }

            float eo = Sobel(neighbors);
            float ef = Sobel(neighborsAliased);
            ep = ef * eo;
            Ge = GAUSS(ep, SIGMA_E);

            Vector3D cbAliased = neighborsAliased(maxColorPos.x, maxColorPos.y);
            Vector3D caAliased = neighborsAliased(minColorPos.x, minColorPos.y);

            beta = Gd * (1- Ge);
            recovered(i,j) = beta * (caAliased * (1-alpha) + cbAliased * alpha) + (1-beta) * pixelAlias;
            maxVarDir(i,j) = varDir * 255;
            sobel(i,j) = Vector3D(sqrt(eo));
        }
    }   

    loader.savePPM(maxVarDir, "max_variance_direction");
    loader.savePPM(sobel, "sobel");

    return recovered;
}

float Sobel(const PPMImage& neighbors) {
    Vector3D h[3];
    Vector3D v[3];

    for(int i = 0; i < 3; ++i) {
        h[i] = neighbors(i,0) + 2*neighbors(i,1) + neighbors(i,2);
        v[i] = neighbors(0,i) + 2*neighbors(1,i) + neighbors(2,i);
    }

    Vector3D gx = (Vector3D::abs(h[1]-h[2]) + Vector3D::abs(h[0]-h[1])) / 4.0;
    Vector3D gy = (Vector3D::abs(v[1]-v[2]) + Vector3D::abs(v[0]-v[1])) / 4.0;

    return gx.dot(gx) + gy.dot(gy);
}

bool FindExtremeColors(const PPMImage& neighbors, const Vector3D& varDir, Vector2D& maxColorPos, Vector2D& minColorPos) {
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

Vector3D MaximumVarianceDirection(PPMImage& neighbors) {
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
