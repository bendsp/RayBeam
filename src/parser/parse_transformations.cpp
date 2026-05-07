#include "core.hpp"

void parseTranslations(const libconfig::Setting &transformations, Core *core)
{
    if (!transformations.exists("translations"))
        return;
    const libconfig::Setting &translations = transformations["translations"];

    for (int i = 0; i < translations.getLength(); ++i) {
        const libconfig::Setting& translation = translations[i];
        int index = static_cast<int>(translation["index"]);
        int x = static_cast<int>(translation["x"]);
        int y = static_cast<int>(translation["y"]);
        int z = static_cast<int>(translation["z"]);

        if (index < 0 || static_cast<size_t>(index) >= core->_primitives.size())
            throw Core::CoreException("Invalid index for translation");

        Math::Vector3D translationVector(x, y, z);
        core->_primitives[index]->translate(translationVector);
    }
}

void parseRotations(const libconfig::Setting &transformations, Core *core)
{
    if (!transformations.exists("rotations"))
        return;
    const libconfig::Setting &rotations = transformations["rotations"];

    for (int i = 0; i < rotations.getLength(); i++) {
        const libconfig::Setting &rotation = rotations[i];
        int index = static_cast<int>(rotation["index"]);
        int angle = static_cast<int>(rotation["angle"]);
        int x = static_cast<int>(rotation["x"]);
        int y = static_cast<int>(rotation["y"]);
        int z = static_cast<int>(rotation["z"]);

        if (index < 0 || static_cast<size_t>(index) >= core->_primitives.size())
            throw Core::CoreException("Invalid index for rotation");

        (void)angle;
        (void)x;
        (void)y;
        (void)z;
        // TODO: implement rotate
    }
}

void parseTransformations(const libconfig::Setting &root, Core *core)
{
    if (!root.exists("transformations"))
        return;
    const libconfig::Setting &transformations = root["transformations"];

    parseTranslations(transformations, core);
    parseRotations(transformations, core);
}
