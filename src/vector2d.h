#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <iostream>
#include <cmath>

class Vector2D {
    public:
        double x;
        double y;
        
        Vector2D();
        Vector2D(double x, double y);
        Vector2D(const Vector2D& v);
        Vector2D(const Vector2D& from,const Vector2D & to);
    
        Vector2D& operator=(const Vector2D & v);    
        Vector2D& operator+=(const Vector2D & v);
        Vector2D operator+(const Vector2D & v) const;
        Vector2D& operator-=(const Vector2D & v);
        Vector2D operator-(const Vector2D & v) const;
        Vector2D& operator*=(const double a);
        Vector2D operator*(const double a)const;
        Vector2D& operator/=(const double a);
        Vector2D operator/(const double a)const;
        friend Vector2D operator*(const double a,const Vector2D & v);

        double length()const;
        Vector2D& normalize();
};
#endif 
