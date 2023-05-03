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

const int WIDTH = 800;
const int HEIGHT = 200;

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

// * Bootstrap main
// int main() {
//     std::ofstream outFile("output.ppm");
//     outFile << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";

//     float aspect_ratio = static_cast<float>(WIDTH) / static_cast<float>(HEIGHT);
//     float screen_height = 2.0;
//     float screen_width = screen_height * aspect_ratio;

//     Math::Point3D cameraOrigin(0, 0, 0);
//     Math::Rectangle3D screen(Math::Point3D(-screen_width/2, -screen_height/2, -1), Math::Vector3D(screen_width, 0, 0), Math::Vector3D(0, screen_height, 0));
//     RayTracer::Camera camera(cameraOrigin, screen);
//     RayTracer::Sphere sphere(Math::Point3D(0, 0, -3), 1);

//     for (int j = HEIGHT - 1; j >= 0; --j) {
//         for (int i = 0; i < WIDTH; ++i) {
//             double u = double(i) / double(WIDTH);
//             double v = double(j) / double(HEIGHT);
//             RayTracer::Ray ray = camera.ray(u, v);
//             Math::Vector3D col = color(ray, sphere);

//             int ir = int(255.99 * col.getX());
//             int ig = int(255.99 * col.getY());
//             int ib = int(255.99 * col.getZ());

//             outFile << ir << " " << ig << " " << ib << "\n";
//         }
//     }

//     outFile.close();
//     std::cout << "Rendering complete. Output saved to 'output.ppm'." << std::endl;

//     return 0;
// }

int main(int ac, char **av)
{
    Core core;
    parse_file(av[1], &core);
    return (0);
}