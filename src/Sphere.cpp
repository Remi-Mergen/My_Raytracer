/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"
#include "Vec3.hpp"
#include <cmath>

bool Sphere::intersect(const Ray& ray, float& t) const {
    Vec3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0 * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    } else {
        t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        return true;
    }
}

void Sphere::translate(const Vec3& translation) {
    center += translation;
}
