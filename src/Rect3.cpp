/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Rect3
*/

#include "Rect3.hpp"
#include "Vec3.hpp"

bool Rect3::intersect(const Ray &ray, float &t) const
{
    Vec3 normal = Vec3::cross(bottom_side, left_side).normalize();

    float denom = Vec3::dot(normal, ray.direction);
    if (std::abs(denom) > 1e-6)
    {
        t = Vec3::dot(origin - ray.origin, normal) / denom;
        if (t >= 0)
        {
            Vec3 intersectionPoint = ray.pointAtParameter(t);
            Vec3 localPoint = intersectionPoint - origin;

            // Check if the intersection point lies within the rectangle's boundaries
            float u = Vec3::dot(localPoint, bottom_side);
            float v = Vec3::dot(localPoint, left_side);

            if (u >= 0 && u <= bottom_side.squaredLength() && v >= 0 && v <= left_side.squaredLength())
            {
                return true;
            }
        }
    }
    return false;
}

Vec3 Rect3::pointAtParameter(double u, double v) const
{
    return origin + bottom_side * u + left_side * v;
}

void Rect3::translate(const Vec3 &translation)
{
    origin += translation;
}
