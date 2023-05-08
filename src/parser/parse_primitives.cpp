/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** parse_primitives.cpp
*/

#include "core.hpp"

void parseSpheres(const libconfig::Setting &primitives, Core *core)
{
    try {
        const libconfig::Setting &spheres = primitives["spheres"];

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
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parsePlanes(const libconfig::Setting &primitives, Core *core)
{
    try {
        const libconfig::Setting &planes = primitives["planes"];

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
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parsePrimitives(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &primitives = root["primitives"];

    parseSpheres(primitives, core);
    parsePlanes(primitives, core);
}
