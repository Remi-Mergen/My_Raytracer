/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"
#include "Rect3.hpp"
#include "Vec3.hpp"

namespace RayTracer
{
    Ray Camera::ray(double u, double v) const
    {
        Vec3 dir = screen.pointAtParameter(u, v) - origin;
        return Ray(origin, dir);
    }
}

RayTracer::Camera::Camera(const Vec3& origin, Rect3& screen)
    : origin(origin), screen(screen) {}