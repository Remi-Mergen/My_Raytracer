/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Rect3.hpp
*/

#ifndef RECT3_HPP_
#define RECT3_HPP_

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Object.hpp"

class Rect3 : public Object
{
public:
    Vec3 origin;
    Vec3 bottom_side;
    Vec3 left_side;

    Rect3(const Vec3 &origin, const Vec3 &bottom_side, const Vec3 &left_side, const sf::Color& color) : Object(color), origin(origin), bottom_side(bottom_side), left_side(left_side) {}

    bool intersect(const Ray &ray, float &t) const override;
    void translate(const Vec3 &translation) override;

    Vec3 getPosition() const override { return origin; }
    Vec3 pointAtParameter(double u, double v) const;

protected:
private:
};

#endif /* !RECT3_HPP_ */
