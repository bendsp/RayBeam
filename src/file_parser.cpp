/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include <libconfig.h++>
#include <iostream>

int parse_file(char *filepath)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filepath);
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return (84);
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (84);
    }
    return (0);
}

/*
    libconfig::Setting &root = cfg.getRoot();

    //* Camera
    try {
        const libconfig::Setting &camera = root["camera"];

        const libconfig::Setting &resolution = camera["resolution"];
        int width, height;
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
        std::cout << "width: " << width << std::endl;
        std::cout << "height: " << height << std::endl;

        const libconfig::Setting &position = camera["position"];
        int posX, posY, posZ;
        position.lookupValue("x", posX);
        position.lookupValue("y", posY);
        position.lookupValue("z", posZ);
        std::cout << "x: " << posX << std::endl;
        std::cout << "y: " << posY << std::endl;
        std::cout << "z: " << posZ << std::endl;

        const libconfig::Setting &rotation = camera["rotation"];
        int rotX, rotY, rotZ;
        rotation.lookupValue("x", rotX);
        rotation.lookupValue("y", rotY);
        rotation.lookupValue("z", rotZ);
        std::cout << "x: " << rotX << std::endl;
        std::cout << "y: " << rotY << std::endl;
        std::cout << "z: " << rotZ << std::endl;

        double fovDegree;
        camera.lookupValue("fieldOfView", fovDegree);
        std::cout << "fov: " << fovDegree << std::endl;

    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "No 'camera' setting in configuration file." << std::endl;
    }

    //* Primitives
    try {
        const libconfig::Setting &primitives = root["primitives"];

        const libconfig::Setting &spheres = primitives["spheres"];

    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "No 'primitives' setting in configuration file." << std::endl;
    }
*/