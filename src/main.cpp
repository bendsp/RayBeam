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
    parse_file(av[1], &core);
    core.display_scene();
    return (0);
}