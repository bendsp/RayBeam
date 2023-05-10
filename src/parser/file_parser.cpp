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
    double fov = (static_cast<double>(camera["fieldOfView"]) * (M_PI / 180));
    Math::Vector3D direction = Math::Vector3D(static_cast<double>(rotation["x"]), static_cast<double>(rotation["y"]), static_cast<double>(rotation["z"]));
    core->_camera.setDirection(direction.normalized());
    core->_camera.setWidth(static_cast<int>(resolution["width"]));
    core->_camera.setHeight(static_cast<int>(resolution["height"]));
    core->_camera.setOrigin(Math::Point3D(static_cast<int>(position["x"]), static_cast<int>(position["y"]), static_cast<int>(position["z"])));
    core->_camera.setFov(fov);

    // calculate screen properties
    float aspect_ratio = static_cast<float>(core->_camera.getWidth()) / static_cast<float>(core->_camera.getHeight());
    float vertical_distance = 0.5f * core->_camera.getHeight() / tan(0.5f * fov);
    float horizontal_fov = 2.0f * atan(tan(0.5f * fov) * aspect_ratio);
    float horizontal_distance = 0.5f * core->_camera.getWidth() / tan(0.5f * horizontal_fov);
    float distance = 0.5f * (horizontal_distance + vertical_distance);
    Math::Vector3D rightVector = math.crossProduct(core->_camera.getDirection(), Math::Vector3D(0, 1, 0)).normalized();
    Math::Vector3D upVector = math.crossProduct(rightVector, core->_camera.getDirection()).normalized();

    core->_camera.setDistanceToScreen(distance);
    core->_camera.setRight(rightVector);
    core->_camera.setUp(upVector);
    // calculate screen center
    Math::Vector3D cameraOriginVec(core->_camera.getOrigin());
    Math::Vector3D screenCenterVec = cameraOriginVec + (core->_camera.getDirection() * core->_camera.getDistanceToScreen());
    Math::Point3D screenCenter = screenCenterVec.toPoint();
    core->_camera.setScreenCenter(screenCenter);
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
