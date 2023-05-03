/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** display_scene.cpp
*/

#include "core.hpp"
#include <iostream>

void Core::display_scene(void) {
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
