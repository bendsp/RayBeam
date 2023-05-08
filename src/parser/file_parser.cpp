/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include "core.hpp"

void parseCamera(const libconfig::Setting &root, Core *core)
{
    Math math;
    const libconfig::Setting &camera = root["camera"];
    const libconfig::Setting &resolution = camera["resolution"];
    const libconfig::Setting &position = camera["position"];
    const libconfig::Setting &rotation = camera["rotation"];

    // set camera properties
    double fov = static_cast<double>(camera["fieldOfView"]);
    Math::Vector3D direction = Math::Vector3D(static_cast<double>(rotation["x"]), static_cast<double>(rotation["y"]), static_cast<double>(rotation["z"]));
    core->_camera.setDirection(direction.normalized());
    core->_camera.setWidth(static_cast<int>(resolution["width"]));
    core->_camera.setHeight(static_cast<int>(resolution["height"]));
    core->_camera.setOrigin(Math::Point3D(static_cast<int>(position["x"]), static_cast<int>(position["y"]), static_cast<int>(position["z"])));
    core->_camera.setFov(fov);
    
    // calculate screen properties
    double distance = 0.5 * core->_camera.getWidth() / tan(0.5 * fov);
    core->_camera.setDistanceToScreen(distance);
    Math::Vector3D rightVector = math.crossProduct(core->_camera.getDirection(), Math::Vector3D(0, 1, 0));
    Math::Vector3D upVector = math.crossProduct(rightVector, core->_camera.getDirection());
    
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
    catch (const libconfig::SettingNotFoundException &nfex) {
    }
    return (0);
}
