/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Ray.cpp
*/

#include "Ray.hpp"
#include "Vec3.hpp"

Vec3 Ray::pointAtParameter(float t) const
{
    return origin + direction * t;
}
