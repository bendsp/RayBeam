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

// RayTracer::RGB Core::checkColisions(RayTracer::Ray ray)
// {
//     RayTracer::RGB color{0, 0, 0};
//     float maxdistance = std::numeric_limits<float>::max(); // Changed from int to float, and initialized with the maximum float value
//     float distance = 0; // Changed from int to float
//     for (int i = 0; i < _primitives.size(); i++) {
//         if (_primitives[i]->hits(ray)) {
//             std::cout << "Hit primitive " << i << " with distance " << distance << std::endl;
//             distance = _primitives[i]->getIntersectionDistance(ray);
//             if (distance < maxdistance) { // Removed the condition where maxdistance == 0
//                 maxdistance = distance;
//                 color = _primitives[i]->getColor();
//             }
//         }
//     }
//     return color;
// }

// void Core::displayScene(void) {
//     int width = this->_camera._width;
//     int height = this->_camera._height;
//     std::ofstream outFile("output.ppm");
//     outFile << "P3\n" << width << " " << height << "\n255\n";

//     for (int j = height - 1; j >= 0; --j) {
//         for (int i = 0; i < width; ++i) {
//             double u = double(i) / double(width);
//             double v = double(j) / double(height);
//             RayTracer::Ray ray = _camera.ray(u, v);
//             RayTracer::RGB col = checkColisions(ray);

//             int ir = int(col.r);
//             int ig = int(col.g);
//             int ib = int(col.b);

//             outFile << ir << " " << ig << " " << ib << "\n";
//         }
//     }

//     outFile.close();
//     std::cout << "Rendering complete. Output saved to 'output.ppm'." << std::endl;
// }

RayTracer::RGB Core::checkColisions(RayTracer::Ray ray)
{
    RayTracer::RGB color{0, 0, 0};
    float maxdistance = std::numeric_limits<float>::max(); // Changed from int to float, and initialized with the maximum float value
    float distance = 0; // Changed from int to float
    for (int i = 0; i < _primitives.size(); i++) {
        //printf("Ray origin: %f %f %f\n", ray._origin.x, ray._origin.y, ray._origin.z);
        //printf("Ray direction: %f %f %f\n", ray._direction.x, ray._direction.y, ray._direction.z);
        ray._direction.z = 100;
        if (_primitives[i]->hits(ray)) {
            distance = _primitives[i]->getIntersectionDistance(ray);
            if (distance < maxdistance) { // Removed the condition where maxdistance == 0
                maxdistance = distance;
                color = _primitives[i]->getColor();
            }
            std::cout << "Hit primitive " << i << " with distance " << distance << std::endl;
        }
    }
    return color;
}

void Core::displayScene(void) {
    float planeWidth = this->_camera._width * tan(this->_camera._fov * 0.5f * M_PI / 180.0f) * 2;
    float planeHeight = planeWidth * this->_camera._height / this->_camera._width;
    Math::Point3D bottomLeftLocal = Math::Point3D(-planeWidth / 2, -planeHeight / 2, 0);
    std::ofstream outFile("output.ppm");
    outFile << "P3\n" << this->_camera._width << " " << this->_camera._height << "\n255\n";

    for (int x = 0; x < this->_camera._width; ++x) {
        for (int y = 0; y < this->_camera._height; ++y) {
            float u = float(x) / float(this->_camera._width);
            float v = float(y) / float(this->_camera._height);
            Math::Point3D bL = this->_camera._origin + this->_camera._screen._origin + bottomLeftLocal;
            Math::Vector3D bottomLeft = Math::Vector3D(bL.x, bL.y, bL.z);
            Math::Vector3D right = this->_camera._screen._bottom_side * planeWidth;
            Math::Vector3D up = this->_camera._screen._left_side * planeHeight;
            Math::Vector3D point = bottomLeft + right * u + up * v;
            Math::Vector3D direction = point - this->_camera._origin;
            RayTracer::Ray ray = RayTracer::Ray(this->_camera._origin, direction);
            RayTracer::RGB col = checkColisions(ray);

            // TODO : Check direction z qui varie alors quil ne devrait pas
            int ir = int(col.r);
            int ig = int(col.g);
            int ib = int(col.b);

            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    return;
}
