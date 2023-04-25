/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Ray.hpp
*/

#ifndef RAY_HPP_
#define RAY_HPP_

#include "Vec3.hpp"

class Ray
{
public:
    Vec3 origin, direction;

    Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction) {}

    Vec3 pointAtParameter(float t) const;
};

#endif /* !RAY_HPP_ */
