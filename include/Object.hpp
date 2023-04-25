/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Object.hpp
*/

#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include "Ray.hpp"
#include <SFML/Graphics.hpp>

class Object
{
public:
    sf::Color color;
    Object(const sf::Color& color) : color(color) {}

    virtual bool intersect(const Ray &ray, float &t) const = 0;
    virtual void translate(const Vec3 &translation) = 0;
    virtual Vec3 getPosition() const = 0;

    virtual ~Object() = default;
};

#endif /* !OBJECT_HPP_ */
