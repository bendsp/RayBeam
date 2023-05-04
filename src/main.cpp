/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** main.cpp
*/

#include <iostream>
#include <fstream>
#include "raytracer.hpp"
#include "primitives.hpp"
#include "core.hpp"

Math::Vector3D color(const RayTracer::Ray& ray, const RayTracer::Sphere& sphere) {
    if (sphere.hits(ray)) {
        return Math::Vector3D(1, 0, 0); // Red sphere
    }
    // Light blue background
    Math::Vector3D unitDirection = ray.getDirection();
    unitDirection /= unitDirection.length();
    double t = 0.5 * (unitDirection.getY() + 1.0);
    return Math::Vector3D(0.5, 0.7, 1.0) * t + Math::Vector3D(1.0, 1.0, 1.0) * (1.0 - t);
}

int main(int ac, char **av)
{
    Core core;
    parse_file(av[1], &core);
    core.display_scene();
    return (0);
}