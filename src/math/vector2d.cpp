#include "vector2d.h"

Vector2D::Vector2D() {
    x = 0;
    y = 0;
}

Vector2D::Vector2D(float x_, float y_) {
    x = x_;
    y = y_;
}

Vector2D::Vector2D(const Vector2D& v) {
    x = v.x;
    y = v.y;
}

Vector2D::Vector2D(const Vector2D& from,const Vector2D& to) {
    x = to.x - from.x;
    y = to.y - from.y;
}

Vector2D& Vector2D::operator= (const Vector2D& v) {
    x = v.x;
    y = v.y;
    return *this;
}

Vector2D& Vector2D::operator+= (const Vector2D& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2D Vector2D::operator+ (const Vector2D& v) const {
    Vector2D t = *this;
    t += v;
    return t;
}

Vector2D & Vector2D::operator-= (const Vector2D& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& v) const {
    Vector2D t = *this;
    t -= v;
    return t;
}

Vector2D & Vector2D::operator*=(const float a) {
    x *= a;
    y *= a;
    return *this;
}

Vector2D Vector2D::operator*(const float a)const {
    Vector2D t = *this;
    t *= a;
    return t;
}

Vector2D operator*(const float a, const Vector2D & v) {
    return Vector2D(v.x*a, v.y*a);
}

Vector2D& Vector2D::operator/=(const float a) {
    x /= a;
    y /= a;
    return *this;
}

Vector2D Vector2D::operator/(const float a)const {
    Vector2D t = *this;
    t /= a;
    return t;
}

float Vector2D::length() const {
    return sqrt(x*x+y*y);
}

Vector2D& Vector2D::normalize() {
    (*this) /= length();
    return (*this);
}
