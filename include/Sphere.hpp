/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Sphere.hpp
*/

#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include "Ray.hpp"
#include "Vec3.hpp"
#include "Object.hpp"

class Sphere : public Object
{
public:
    Vec3 center;
    float radius;

    Sphere(const Vec3 &center, float radius, const sf::Color &color) : Object(color), center(center), radius(radius) {}

    bool intersect(const Ray &ray, float &t) const override;
    void translate(const Vec3 &translation) override;
    Vec3 getPosition() const override { return center; }
};

#endif /* !SPHERE_HPP_ */
