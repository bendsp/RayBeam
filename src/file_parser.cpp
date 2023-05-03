/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include <libconfig.h++>
#include <iostream>
#include "core.hpp"

int parse_file(char *filepath, Core *core)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filepath);
        const libconfig::Setting &root = cfg.getRoot();
        const libconfig::Setting &camera = root["camera"];
        const libconfig::Setting &resolution = camera["resolution"];
        const libconfig::Setting &position = camera["position"];
        const libconfig::Setting &rotation = camera["rotation"];
        const libconfig::Setting &primitives = root["primitives"];
        const libconfig::Setting &spheres = primitives["spheres"];
        const libconfig::Setting &planes = primitives["planes"];
        const libconfig::Setting &lights = root["lights"];
        const libconfig::Setting &point_lights = lights["point"];
        const libconfig::Setting &directional_lights = lights["directional"];

        std::cout << "Resolution width: " << static_cast<int>(resolution["width"]) << std::endl;
        std::cout << "Resolution height: " << static_cast<int>(resolution["height"]) << std::endl;
        std::cout << "Camera position: " << static_cast<int>(position["x"]) << ", " << static_cast<int>(position["y"]) << ", " << static_cast<int>(position["z"]) << std::endl;
        std::cout << "Camera rotation: " << static_cast<int>(rotation["x"]) << ", " << static_cast<int>(rotation["y"]) << ", " << static_cast<int>(rotation["z"]) << std::endl;
        std::cout << "Ambient light: " << static_cast<double>(lights["ambient"]) << std::endl;
        std::cout << "Diffuse light: " << static_cast<double>(lights["diffuse"]) << std::endl;
        core->_camera.setWidth(static_cast<int>(resolution["width"]));
        core->_camera.setHeight(static_cast<int>(resolution["height"]));
        core->_camera.setOrigin(Math::Point3D(static_cast<int>(position["x"]), static_cast<int>(position["y"]), static_cast<int>(position["z"])));

        for (int i = 0; i < spheres.getLength(); ++i) {
            const libconfig::Setting& sphere = spheres[i];
            std::cout << "Sphere " << i + 1 << " center: (" << static_cast<int>(sphere["x"]) << ", " << static_cast<int>(sphere["y"]) << ", " << static_cast<int>(sphere["z"]) << ")" << std::endl
                      << "Sphere " << i + 1 << " radius: " << static_cast<int>(sphere["r"]) << std::endl;
        }

        for (int i = 0; i < planes.getLength(); ++i) {
            const libconfig::Setting& plane = planes[i];
            std::cout << "Plane " << i + 1 << " axis: " << static_cast<std::string>(plane["axis"]) << std::endl
              << "Plane " << i + 1 << " position: " << static_cast<int>(plane["position"]) << std::endl;
        }


        for (int i = 0; i < point_lights.getLength(); ++i) {
            const libconfig::Setting& point_light = point_lights[i];
            std::cout << "Point light " << i + 1 << " position: (" << static_cast<int>(point_light["x"]) << ", " << static_cast<int>(point_light["y"]) << ", " << static_cast<int>(point_light["z"]) << ")" << std::endl;
        }

        for (int i = 0; i < directional_lights.getLength(); ++i) {
            const libconfig::Setting& directional_light = directional_lights[i];
            std::cout << "Directional light " << i + 1 << " direction: (" << static_cast<int>(directional_light["x"]) << ", " << static_cast<int>(directional_light["y"]) << ", " << static_cast<int>(directional_light["z"]) << ")" << std::endl;
        }

    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return (84);
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return (84);
    }
    catch (const libconfig::SettingTypeException &stex) {
        std::cerr << "SettingTypeException: " << stex.getPath() << " - " << stex.what() << std::endl;
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