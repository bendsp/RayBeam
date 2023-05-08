/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include "core.hpp"

double toRadians(double degrees)
{
    return degrees * (3.14159265358979323846 / 180.0);
}

void parseCamera(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &camera = root["camera"];
    const libconfig::Setting &resolution = camera["resolution"];
    const libconfig::Setting &position = camera["position"];
    const libconfig::Setting &rotation = camera["rotation"];

    double fov = static_cast<double>(camera["fieldOfView"]);
    core->_camera.setDirection(Math::Vector3D(static_cast<int>(rotation["x"]), static_cast<int>(rotation["y"]), static_cast<int>(rotation["z"])));
    core->_camera.setWidth(static_cast<int>(resolution["width"]));
    core->_camera.setHeight(static_cast<int>(resolution["height"]));
    core->_camera.setOrigin(Math::Point3D(static_cast<int>(position["x"]), static_cast<int>(position["y"]), static_cast<int>(position["z"])));
    core->_camera.setFov(fov);
    
    double distance = 0.5 * core->_camera.getWidth() / tan(0.5 * fov);
    core->_camera.setDistanceToScreen(distance);
    std::cout << "Distance to screen : " << distance << std::endl;
    double halfScreenHeight = tan(toRadians(core->_camera.getFov() / 2.0)) * core->_camera.getDistanceToScreen();
    float aspect_ratio = static_cast<float>(core->_camera.getWidth()) / static_cast<float>(core->_camera.getHeight());
    double screen_height = 2.0 * halfScreenHeight;
    double screen_width = screen_height * aspect_ratio;
    Math::Rectangle3D screen(Math::Point3D(-screen_width/2, -screen_height/2, -1), Math::Vector3D(screen_width, 0, 0), Math::Vector3D(0, screen_height, 0));
    core->_camera.setScreen(screen);
}

int parseFile(char *filepath, Core *core)
{
    libconfig::Config cfg;
    try {
        cfg.readFile(filepath);
        const libconfig::Setting &root = cfg.getRoot();

        parseCamera(root, core);
        parsePrimitives(root, core);
        parseLights(root, core);
        parseTransformations(root, core);

    } catch (const libconfig::FileIOException &fioex) {
        throw Core::CoreException("I/O error while reading file.");
    }
    catch (const libconfig::ParseException &pex) {
        throw Core::CoreException("Parse error at " + std::string(pex.getFile()) + ":" + std::to_string(pex.getLine()) + " - " + pex.getError());
    }
    catch (const libconfig::SettingTypeException &stex) {
        throw Core::CoreException("Setting type error at " + std::string(stex.getPath()) + " - " + stex.what());
    }
    return (0);
}
