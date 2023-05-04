/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** display_scene.cpp
*/

#include "core.hpp"
#include "raytracer.hpp"
#include "primitives.hpp"
#include "math.hpp"
#include <fstream>
#include <iostream>

Math::Vector3D Core::checkColisions(RayTracer::Ray ray)
{
    Math::Vector3D color(0, 0, 0);
    for (int i = 0; i < _primitives.size(); i++) {
        if (_primitives[i]->hits(ray)) {
            color = Math::Vector3D(1, 0, 0);
        }
    }
    return color;
}

void Core::display_scene(void) {
    int width = this->_camera._width;
    int height = this->_camera._height;
    std::ofstream outFile("output.ppm");
    outFile << "P3\n" << width << " " << height << "\n255\n";

    float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    float screen_height = 2.0;
    float screen_width = screen_height * aspect_ratio;

    Math::Point3D cameraOrigin(0, 0, 0);
    Math::Rectangle3D screen(Math::Point3D(-screen_width/2, -screen_height/2, -1), Math::Vector3D(screen_width, 0, 0), Math::Vector3D(0, screen_height, 0));
    RayTracer::Camera camera(cameraOrigin, screen);
    RayTracer::Sphere sphere(Math::Point3D(0, 0, -3), 1);

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            RayTracer::Ray ray = camera.ray(u, v);
            Math::Vector3D col = checkColisions(ray);
            

            int ir = int(255.99 * col.getX());
            int ig = int(255.99 * col.getY());
            int ib = int(255.99 * col.getZ());

            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }

    outFile.close();
    std::cout << "Rendering complete. Output saved to 'output.ppm'." << std::endl;
    std::cout << "Camera : " << std::endl;
    // std::cout << "Position : " << _camera._position << std::endl;
    // std::cout << "Direction : " << _camera._direction << std::endl;
    std::cout << "Field of view : " << _camera._fov << std::endl;
    std::cout << "Width : " << _camera._width << std::endl;
    std::cout << "Height : " << _camera._height << std::endl;

    int nb_prim = _primitives.size();
    std::cout << "Number of primitives : " << nb_prim << std::endl;
    for (int i = 0; i < nb_prim; i++) {
        std::cout << "Primitive " << i << " : " << std::endl;
        // std::cout << "Center : " << _primitives[i]->_center << std::endl;
        // std::cout << "Radius : " << _primitives[i]->_radius << std::endl;
    }
}
