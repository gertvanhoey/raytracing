#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>

class Vector3D
{
public:
    Vector3D() = default;
    Vector3D(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }
    double r() const { return e[0]; }
    double g() const { return e[1]; }
    double b() const { return e[2]; }

    const Vector3D& operator+() const { return *this; }
    Vector3D operator-() const { return Vector3D(-e[0], -e[1], -e[2]); }

    double operator[](int i) const { return e[i]; }
    double&  operator[](int i) { return e[i]; }

    Vector3D& operator+=(const Vector3D&);
    Vector3D& operator-=(const Vector3D&);
    Vector3D& operator*=(const Vector3D&);
    Vector3D& operator/=(const Vector3D&);
    Vector3D& operator*=(const double);
    Vector3D& operator/=(const double);

    double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    void make_unit_vector();

    double e[3] = {0.0, 0.0, 0.0};
};

inline Vector3D& Vector3D::operator+=(const Vector3D &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vector3D& Vector3D::operator*=(const Vector3D &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vector3D& Vector3D::operator/=(const Vector3D &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vector3D& Vector3D::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vector3D& Vector3D::operator/=(const double t) {
    const double k = 1.0 / t;
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline void Vector3D::make_unit_vector()
{
    double k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}


inline std::istream& operator>>(std::istream &is, Vector3D &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vector3D &t) {
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}


inline Vector3D operator+(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vector3D operator-(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vector3D operator*(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vector3D operator*(const Vector3D &v, double t) {
    return Vector3D(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vector3D operator*(double t, const Vector3D &v) {
    return Vector3D(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vector3D operator/(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vector3D operator/(const Vector3D &v, double t) {
    return Vector3D(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline double dot(const Vector3D &v1, const Vector3D &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vector3D cross(const Vector3D &v1, const Vector3D &v2) {
    return Vector3D(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline Vector3D unit_vector(const Vector3D &v) {
    return v / v.length();
}

#endif // VECTOR3D_H
