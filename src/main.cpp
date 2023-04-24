/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** main.cpp
*/

#include <iostream>
#include "raytracer.hpp"

void write_color(Math::Vector3D &color)
{
    std::cout << static_cast<int>(256 * color.x) << ' '
              << static_cast<int>(256 * color.y) << ' '
              << static_cast<int>(256 * color.z)
              << std::endl;
}

int main()
{
    RayTracer::Camera cam(Math::Point3D(0, 0, 0), Math::Rectangle3D(Math::Point3D(0, 0, 0), Math::Vector3D(0, 0, 1), Math::Vector3D(1, 0, 0)));
    RayTracer::Sphere sphere(Math::Point3D(0, 0, -1), 0.5);

    const int image_width = 256;
    const int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Math::Vector3D color(0, 0, 0);
            RayTracer::Ray r = cam.ray(i, j);
            if (sphere.hits(r))
                color = Math::Vector3D(1, 0, 0);
            else
                color = Math::Vector3D(0, 0, 1);
            write_color(color);
        }
    }
}
