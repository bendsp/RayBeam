#include "core.hpp"

void parsePointLights(const libconfig::Setting &lights, Core *core)
{
    double ambient = static_cast<double>(lights["ambient"]);
    if (ambient > 1)
        ambient = 1;
    if (ambient < 0)
        ambient = 0;
    double diffuse = static_cast<double>(lights["diffuse"]);

    core->setAmbient(ambient);
    core->setDiffuse(diffuse);
    if (!lights.exists("point"))
        return;
    const libconfig::Setting &pointLights = lights["point"];

    for (int i = 0; i < pointLights.getLength(); ++i) {
        const libconfig::Setting& pointLight = pointLights[i];
        int x = static_cast<int>(pointLight["x"]);
        int y = static_cast<int>(pointLight["y"]);
        int z = static_cast<int>(pointLight["z"]);
        Math::Point3D position = Math::Point3D(x, y, z);
        core->addLight(std::make_unique<RayTracer::PointLight>(position, ambient, diffuse));
    }
}

void parseDirectionalLights(const libconfig::Setting &lights, Core *core)
{
    double ambient = static_cast<double>(lights["ambient"]);
    double diffuse = static_cast<double>(lights["diffuse"]);

    if (!lights.exists("directional"))
        return;
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
        core->addLight(std::make_unique<RayTracer::DirectionalLight>(position, vecDirection, ambient, diffuse));
    }
}

void parseLights(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &lights = root["lights"];

    parsePointLights(lights, core);
    parseDirectionalLights(lights, core);
}
