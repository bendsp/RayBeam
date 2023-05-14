/*
** EPITECH PROJECT, 2022
** bootstrapRaytracer
** File description:
** main.cpp
*/

#include <iostream>
#include <fstream>
#include "raytracer.hpp"
#include "primitives.hpp"
#include "core.hpp"
#include "menu.hpp"
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <filesystem>

void Core::printCoreInfo(void)
{
    std::cout << "Origin : {" << _camera._origin.x << ", " << _camera._origin.y << ", " << _camera._origin.z << "}" << std::endl;
    std::cout << "Distance to Screen: " << _camera.getDistanceToScreen() << std::endl;
    std::cout << "Direction: " << _camera._forward.x << ", " << _camera._forward.y << ", " << _camera._forward.z << std::endl; 
    std::cout << "Field of view : " << _camera._fov << std::endl;
    std::cout << "Width : " << _camera._width << std::endl;
    std::cout << "Height : " << _camera._height << std::endl;
    std::cout << "Center of screen: " << _camera._screenCenter.x << ", " << _camera._screenCenter.y << ", " << _camera._screenCenter.z << std::endl;
    std::cout << "Ambient light: " << _ambient << std::endl;
    int nb_prim = _primitives.size();
    std::cout << "\n -- Number of primitives : " << _primitives.size() << std::endl;
    for (int i = 0; i < nb_prim; i++) {
        std::cout << "Primitive " << i << " : " << std::endl;
        _primitives[i]->displayPrimitive();
    }

    int nb_lights = _lights.size();
    std::cout << "\n -- Number of lights : " << nb_lights << std::endl;
    for (int i = 0; i < nb_lights; i++) {
        std::cout << "Light " << i << " : " << std::endl;
        _lights[i]->displayLight();
    }
}

// int main(int ac, char **av)
// {
//     Core core;
//     try {
//         parseFile(av[1], &core);
//         core.displayScene();
//     } catch (Core::CoreException &e) {
//         std::cerr << e.what() << std::endl;
//         return (84);
//     }
//     core.printCoreInfo();

//     return (0);
// }

void displayLogo(sf::RenderWindow &window){
    sf::Texture texture;
    sf::Sprite sprite;
    if (!texture.loadFromFile("rtx.png")) {
        std::cout << "Error loading logo" << std::endl;
        // handle error
    }
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(230, 30));
    sprite.setScale(sf::Vector2f(0.1, 0.1));
    window.draw(sprite);
}

int main(int ac, char **av)
{
    Core core;

    std::vector<std::string> fileNames;
    std::vector<std::string> filePaths;
    for (const auto & entry : std::filesystem::directory_iterator("scenes")) {
        if (entry.path().extension() == ".cfg") {
            fileNames.push_back(entry.path().filename().string());
            filePaths.push_back("scenes/" + entry.path().filename().string());
        }
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Raytracer Output");

    Menu menu(window.getSize().x, window.getSize().y, fileNames, window);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;
                case sf::Keyboard::Return:
                    {
                        if (menu.GetPressedItem() == fileNames.size()) {
                            window.close();
                            break;
                        }

                        Core core;
                        try {
                            char* filePath = strdup(filePaths[menu.GetPressedItem()].c_str());
                            parseFile(filePath, &core);
                            free(filePath);
                            core.displayScene();
                        } catch (Core::CoreException &e) {
                            std::cerr << e.what() << std::endl;
                            return (84);
                        }
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();

                break;
            }
        }

        window.clear();

        displayLogo(window);

        menu.draw(window);

        window.display();
    }

    // ? Uncomment to display core info
    // core.printCoreInfo();

    return (0);
}
