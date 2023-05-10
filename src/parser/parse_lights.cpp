/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** parse_lights.cpp
*/

#include "core.hpp"

void parsePointLights(const libconfig::Setting &lights, Core *core)
{
    try {
        const libconfig::Setting &pointLights = lights["point"];

        for (int i = 0; i < pointLights.getLength(); ++i) {
            const libconfig::Setting& pointLight = pointLights[i];
            int x = static_cast<int>(pointLight["x"]);
            int y = static_cast<int>(pointLight["y"]);
            int z = static_cast<int>(pointLight["z"]);
            Math::Point3D position = Math::Point3D(x, y, z);
            core->addLight(new RayTracer::PointLight(position, core->getAmbient(), core->getDiffuse()));
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parseDirectionalLights(const libconfig::Setting &lights, Core *core)
{
    try {
        const libconfig::Setting &directionalLights = lights["directional"];

        for (int i = 0; i < directionalLights.getLength(); ++i) {
            const libconfig::Setting& directionalLight = directionalLights[i];
            int x = static_cast<int>(directionalLight["x"]);
            int y = static_cast<int>(directionalLight["y"]);
            int z = static_cast<int>(directionalLight["z"]);
            libconfig::Setting &direction = directionalLight["direction"];
            int dx = static_cast<int>(direction["x"]);
            int dy = static_cast<int>(direction["y"]);
            int dz = static_cast<int>(direction["z"]);
            Math::Point3D position = Math::Point3D(x, y, z);
            Math::Vector3D vecDirection = Math::Vector3D(dx, dy, dz);
            core->addLight(new RayTracer::DirectionalLight(position, vecDirection, core->getAmbient(), core->getDiffuse()));
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parseLights(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &lights = root["lights"];

    try {
        const libconfig::Setting &ambient = lights["ambient"];
        core->setAmbient(static_cast<double>(ambient));
    } catch (const libconfig::SettingNotFoundException &nfex) {
        core->setAmbient(1.0);
    }

    try {
        const libconfig::Setting &diffuse = lights["diffuse"];
        core->setDiffuse(static_cast<double>(diffuse));
    } catch (const libconfig::SettingNotFoundException &nfex) {
        core->setDiffuse(1.0);
    }

    parsePointLights(lights, core);
    parseDirectionalLights(lights, core);
}
