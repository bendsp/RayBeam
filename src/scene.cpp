/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** displayScene.cpp
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
    float maxdistance = std::numeric_limits<float>::max(); // Changed from int to float, and initialized with the maximum float value
    float distance = 0; // Changed from int to float
    for (int i = 0; i < _primitives.size(); i++) {
        if (_primitives[i]->hits(ray)) {
            std::cout << "Hit primitive " << i << " with distance " << distance << std::endl;
            distance = _primitives[i]->getIntersectionDistance(ray);
            if (distance < maxdistance) { // Removed the condition where maxdistance == 0
                maxdistance = distance;
                color = _primitives[i]->getColor();
            }
        }
    }
    return color;
}

void Core::displayScene(void) {
    int width = this->_camera._width;
    int height = this->_camera._height;
    std::ofstream outFile("output.ppm");
    outFile << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / double(width);
            double v = double(j) / double(height);
            RayTracer::Ray ray = _camera.ray(u, v);
            RayTracer::RGB col = checkColisions(ray);

            int ir = int(col.r);
            int ig = int(col.g);
            int ib = int(col.b);

            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }

    outFile.close();
    std::cout << "Rendering complete. Output saved to 'output.ppm'." << std::endl;
    // std::cout << "Camera : " << std::endl;
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
    std::cout << "\n -- Number of primitives : " << _primitives.size() << std::endl;
    for (int i = 0; i < nb_prim; i++) {
        std::cout << "Primitive " << i << " : " << std::endl;
        _primitives[i]->displayPrimitive();
    }

    int nb_lights = _lights.size();
    std::cout << "\n -- Number of lights : " << nb_lights << std::endl;
    for (int i = 0; i < nb_lights; i++) {
        std::cout << "Light " << i << " : " << std::endl;
        _lights[i]->displayLight();
    }
}
