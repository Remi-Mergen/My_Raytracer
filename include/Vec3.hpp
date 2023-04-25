/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Vector3D.hpp
*/

#ifndef VECTOR3D_HPP_
#define VECTOR3D_HPP_

#include <cmath>
#include <limits>
#include <vector>

class Vec3
{
public:
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator+=(const Vec3 &other);
    float dot(const Vec3 &other) const;
    static float dot(const Vec3 &a, const Vec3 &b);
    Vec3 normalize() const;
    Vec3 cross(const Vec3 &other) const;
    static Vec3 cross(const Vec3& v1, const Vec3& v2);
    float squaredLength() const;
};

#endif /* !VECTOR3D_HPP_ */
