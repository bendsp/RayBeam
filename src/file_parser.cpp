/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** file_parser.cpp
*/

#include <libconfig.h++>
#include <iostream>
#include <unordered_map>
#include "core.hpp"
#include "primitives.hpp"

void parseCamera(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &camera = root["camera"];
    const libconfig::Setting &resolution = camera["resolution"];
    const libconfig::Setting &position = camera["position"];
    const libconfig::Setting &rotation = camera["rotation"];

    core->_camera.setWidth(static_cast<int>(resolution["width"]));
    core->_camera.setHeight(static_cast<int>(resolution["height"]));
    core->_camera.setOrigin(Math::Point3D(static_cast<int>(position["x"]), static_cast<int>(position["y"]), static_cast<int>(position["z"])));
    core->_camera.setFov(static_cast<double>(camera["fieldOfView"]));
}

void parsePrimitives(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &primitives = root["primitives"];
    const libconfig::Setting &spheres = primitives["spheres"];
    const libconfig::Setting &planes = primitives["planes"];

    for (int i = 0; i < spheres.getLength(); ++i) {
        const libconfig::Setting& sphere = spheres[i];
        Math::Point3D center = Math::Point3D(static_cast<int>(sphere["x"]), static_cast<int>(sphere["y"]), static_cast<int>(sphere["z"]));
        double radius = static_cast<int>(sphere["r"]);
        libconfig::Setting& color = sphere["color"];
        int r = static_cast<int>(color["r"]);
        int g = static_cast<int>(color["g"]);
        int b = static_cast<int>(color["b"]);
        core->addPrimitive(new RayTracer::Sphere(center, radius, {r, g, b}));
    }

    static std::unordered_map<std::string, RayTracer::Axis> axisMap = {
        {"X", RayTracer::X},
        {"Y", RayTracer::Y},
        {"Z", RayTracer::Z},
        {"x", RayTracer::X},
        {"y", RayTracer::Y},
        {"z", RayTracer::Z}
    };

    for (int i = 0; i < planes.getLength(); ++i) {
        const libconfig::Setting& plane = planes[i];
        std::string axisType = static_cast<std::string>(plane["axis"]);
        RayTracer::Axis axis = axisMap[axisType];
        if (axis == 0)
            throw Core::CoreException("Invalid axis type");
        int position = static_cast<int>(plane["position"]);
        libconfig::Setting& color = plane["color"];
        int r = static_cast<int>(color["r"]);
        int g = static_cast<int>(color["g"]);
        int b = static_cast<int>(color["b"]);
        core->addPrimitive(new RayTracer::Plane(position, axis, {r, g, b}));
    }
}

void parseLights(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &lights = root["lights"];
    const libconfig::Setting &point_lights = lights["point"];
    const libconfig::Setting &directional_lights = lights["directional"];

    double ambient = static_cast<double>(lights["ambient"]);
    double diffuse = static_cast<double>(lights["diffuse"]);

    for (int i = 0; i < point_lights.getLength(); ++i) {
        const libconfig::Setting& point_light = point_lights[i];
        int x = static_cast<int>(point_light["x"]);
        int y = static_cast<int>(point_light["y"]);
        int z = static_cast<int>(point_light["z"]);
        Math::Point3D position = Math::Point3D(x, y, z);
        core->addLight(new RayTracer::PointLight(position, ambient, diffuse));
    }

    for (int i = 0; i < directional_lights.getLength(); ++i) {
        const libconfig::Setting& directional_light = directional_lights[i];
        int x = static_cast<int>(directional_light["x"]);
        int y = static_cast<int>(directional_light["y"]);
        int z = static_cast<int>(directional_light["z"]);
        libconfig::Setting &direction = directional_light["direction"];
        int dx = static_cast<int>(direction["x"]);
        int dy = static_cast<int>(direction["y"]);
        int dz = static_cast<int>(direction["z"]);
        Math::Point3D position = Math::Point3D(x, y, z);
        Math::Vector3D vecDirection = Math::Vector3D(dx, dy, dz);
        core->addLight(new RayTracer::DirectionalLight(position, vecDirection, ambient, diffuse));
    }
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
