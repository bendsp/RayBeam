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

    return (0);
}