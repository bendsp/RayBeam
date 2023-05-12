/*
** EPITECH PROJECT, 2022
** B-OOP-400-BER-4-1-raytracer-paul.thiebault
** File description:
** menu.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

const int MAX_NUMBER_OF_ITEMS = 2;

class Menu {
public:
    Menu(float width, float height, std::vector<std::string> fileNames)
    {
        if (!font.loadFromFile("font.ttf"))
        {
            // handle error
        }

        // Create menu items
        for (size_t i = 0; i < fileNames.size(); i++)
        {
            menu.push_back(sf::Text());
            menu[i].setFont(font);
            menu[i].setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
            menu[i].setString(fileNames[i]);
            menu[i].setPosition(sf::Vector2f(width / 2, height / (fileNames.size() + 1) * (i + 1)));
        }

        selectedItemIndex = 0;
    }

    void draw(sf::RenderWindow &window)
    {
        for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
        {
            window.draw(menu[i]);
        }
    }

    void MoveUp()
    {
        if (selectedItemIndex - 1 >= 0)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void MoveDown()
    {
        if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
        {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    int GetPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menu;
};
