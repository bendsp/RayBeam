/*
** EPITECH PROJECT, 2022
** raytracer
** File description:
** parse_transformations.cpp
*/

#include "core.hpp"

void parseTranslation(const libconfig::Setting &transformations, Core *core)
{
    try {
        const libconfig::Setting &translations = transformations["translations"];

        for (int i = 0; i < translations.getLength(); ++i) {
            const libconfig::Setting& translation = translations[i];
            int index = static_cast<int>(translation["index"]);
            int x = static_cast<int>(translation["x"]);
            int y = static_cast<int>(translation["y"]);
            int z = static_cast<int>(translation["z"]);
            std::cout << "Translation: " << index << " > " << x << " " << y << " " << z << std::endl;
            //Math::Vector3D vec = Math::Vector3D(x, y, z);
            //core->addTransformation(new RayTracer::Translation(vec));
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
    }
}

void parseRotation(const libconfig::Setting &transformations, Core *core)
{

}

// TODO: parse and apply transformations
void parseTransformations(const libconfig::Setting &root, Core *core)
{
    const libconfig::Setting &transformations = root["transformations"];
    // const libconfig::Setting &rotations = transformations["rotations"];

    parseTranslation(transformations, core);
}
