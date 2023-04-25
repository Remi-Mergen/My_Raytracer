/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Vec3.cpp
*/

#include "Vec3.hpp"

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator+=(const Vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

float Vec3::dot(const Vec3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

float Vec3::dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::normalize() const
{
    float magnitude = std::sqrt(x * x + y * y + z * z);
    return Vec3(x / magnitude, y / magnitude, z / magnitude);
}

Vec3 Vec3::cross(const Vec3 &other) const
{
    return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Vec3 Vec3::cross(const Vec3 &v1, const Vec3 &v2)
{
    return Vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x);
}

float Vec3::squaredLength() const
{
    return x * x + y * y + z * z;
}
