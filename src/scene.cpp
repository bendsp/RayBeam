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

RayTracer::RGB Core::checkColisions(RayTracer::Ray ray)
{
    RayTracer::RGB color{0, 0, 0};
    for (int i = 0; i < _primitives.size(); i++) {
        if (_primitives[i]->hits(ray)) {
            color = _primitives[i]->getColor();
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

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            RayTracer::Ray ray = camera.ray(u, v);
            RayTracer::RGB col = checkColisions(ray);
            

            int ir = int(col.r);
            int ig = int(col.g);
            int ib = int(col.b);

            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }

    outFile.close();
    std::cout << "Rendering complete. Output saved to 'output.ppm'." << std::endl;
    std::cout << "Camera : " << std::endl;
    // std::cout << "Position : " << _camera._position << std::endl;
    // std::cout << "Direction : " << _camera._direction << std::endl;
    std::cout << "\n -- Camera --" << std::endl;
    std::cout << "Origin : {" << _camera._origin.x << ", " << _camera._origin.y << ", " << _camera._origin.z << "}" << std::endl;
    std::cout << "Screen Origin : {" << _camera._screen._origin.x << ", " << _camera._screen._origin.y << ", " << _camera._screen._origin.z << "}" << std::endl;
    std::cout << "Screen Bottom Side : {" << _camera._screen._bottom_side.x << ", " << _camera._screen._bottom_side.y << ", " << _camera._screen._bottom_side.z << "}" << std::endl;
    std::cout << "Screen Left Side : {" << _camera._screen._left_side.x << ", " << _camera._screen._left_side.y << ", " << _camera._screen._left_side.z << "}" << std::endl;
    std::cout << "Field of view : " << _camera._fov << std::endl;
    std::cout << "Width : " << _camera._width << std::endl;
    std::cout << "Height : " << _camera._height << std::endl;

    int nb_prim = _primitives.size();
    std::cout << "\n -- Number of primitives : " << nb_prim << std::endl;
    for (int i = 0; i < nb_prim; i++) {
        std::cout << "Primitive " << i << " : " << std::endl;
        _primitives[i]->displayPrimitive();
    }
}
