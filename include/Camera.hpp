/*
** EPITECH PROJECT, 2023
** bootstrap_raytracer
** File description:
** Camera.hpp
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Vec3.hpp"
#include "Rect3.hpp"

namespace RayTracer
{
    class Camera
    {
    public:
        Vec3 origin;
        Rect3 screen;

        Ray ray(double u, double v) const;
        Camera(const Vec3& origin, Rect3& screen);
        Camera(const Vec3 &origin, const Rect3 &screen) : origin(origin), screen(screen) {}
    protected:
    private:
    };
}

#endif /* !CAMERA_HPP_ */
