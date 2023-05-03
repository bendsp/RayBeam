/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** display_scene.cpp
*/

#include "core.hpp"

void Core::display_scene(void) {
    int nb_prim = _primitives.size();
    for (int i = 0; i < nb_prim; i++) {
        std::cout << "Primitive " << i << " : " << std::endl;
        std::cout << "Center : " << _primitives[i]->_center << std::endl;
        std::cout << "Radius : " << _primitives[i]->_radius << std::endl;
    }
}
