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

void Core::printCoreInfo(void)
{
    std::cout << "Origin : {" << _camera._origin.x << ", " << _camera._origin.y << ", " << _camera._origin.z << "}" << std::endl;
    std::cout << "Distance to Screen: " << _camera.getDistanceToScreen() << std::endl;
    std::cout << "Direction: " << _camera._forward.x << ", " << _camera._forward.y << ", " << _camera._forward.z << std::endl; 
    std::cout << "Field of view : " << _camera._fov << std::endl;
    std::cout << "Width : " << _camera._width << std::endl;
    std::cout << "Height : " << _camera._height << std::endl;
    std::cout << "Center of screen: " << _camera._screenCenter.x << ", " << _camera._screenCenter.y << ", " << _camera._screenCenter.z << std::endl;
    std::cout << "Ambient light: " << _ambient << std::endl;
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

int main(int ac, char **av)
{
    Core core;
    try {
        parseFile(av[1], &core);
        core.displayScene();
    } catch (Core::CoreException &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }
    core.printCoreInfo();

    return (0);
}