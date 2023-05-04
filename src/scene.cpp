/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** display_scene.cpp
*/

#include "core.hpp"
#include <iostream>

void Core::display_scene(void) {
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
