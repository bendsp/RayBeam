#include "core.hpp"

void parsePointLights(const libconfig::Setting &lights, Core *core)
{
    try {
        const libconfig::Setting &pointLights = lights["point"];

        double ambient = static_cast<double>(lights["ambient"]);
        if (ambient > 1)
            ambient = 1;
        if (ambient < 0)
            ambient = 0;
        double diffuse = static_cast<double>(lights["diffuse"]);

        for (int i = 0; i < pointLights.getLength(); ++i) {
            const libconfig::Setting& pointLight = pointLights[i];
            int x = static_cast<int>(pointLight["x"]);
            int y = static_cast<int>(pointLight["y"]);
            int z = static_cast<int>(pointLight["z"]);
            Math::Point3D position = Math::Point3D(x, y, z);
            core->setAmbient(ambient);
            core->addLight(new RayTracer::PointLight(position, ambient, diffuse));
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parseDirectionalLights(const libconfig::Setting &lights, Core *core)
{
    try {
        const libconfig::Setting &directionalLights = lights["directional"];

        double ambient = static_cast<double>(lights["ambient"]);
        double diffuse = static_cast<double>(lights["diffuse"]);

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
            core->addLight(new RayTracer::DirectionalLight(position, vecDirection, ambient, diffuse));
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parseLights(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &lights = root["lights"];

    parsePointLights(lights, core);
    parseDirectionalLights(lights, core);
}
