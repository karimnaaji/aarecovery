#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <iostream>
#include <cmath>

class Vector2D {
    public:
        float x;
        float y;
        
        Vector2D();
        Vector2D(float x, float y);
        Vector2D(const Vector2D& v);
        Vector2D(const Vector2D& from,const Vector2D & to);
    
        Vector2D& operator=(const Vector2D & v);    
        Vector2D& operator+=(const Vector2D & v);
        Vector2D operator+(const Vector2D & v) const;
        Vector2D& operator-=(const Vector2D & v);
        Vector2D operator-(const Vector2D & v) const;
        Vector2D& operator*=(const float a);
        Vector2D operator*(const float a)const;
        Vector2D& operator/=(const float a);
        Vector2D operator/(const float a)const;
        friend Vector2D operator*(const float a,const Vector2D & v);

        float length()const;
        Vector2D& normalize();
};
#endif 
