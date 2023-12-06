#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

const int MAX_NUMBER_OF_ITEMS = 2;


class Menu {
public:
    Menu(float width, float height, std::vector<std::string> & fileNames, sf::RenderWindow &window) {
        if (!font.loadFromFile("font.ttf")) {
            // handle error
        }

        // Create menu items for each file name
        for (size_t i = 0; i < fileNames.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(fileNames[i]);
            text.setCharacterSize(30);
            text.setFillColor(sf::Color::White);
            text.setPosition(sf::Vector2f((width - 200) / 2, (200 + fileNames.size() + 50 * i)));
            menu.push_back(text);
        }

        // Add "Exit" option
        sf::Text exitText;
        exitText.setFont(font);
        exitText.setString("Exit");
        exitText.setCharacterSize(30);
        exitText.setFillColor(sf::Color::White);
        exitText.setPosition(sf::Vector2f(width / 2, height / (fileNames.size() + 2) * (fileNames.size() + 1)));
        menu.push_back(exitText);

        selectedItemIndex = 0;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow &window) {
        for (auto &text : menu) {
            window.draw(text);
        }
    }

    void MoveUp() {
        if (selectedItemIndex - 1 >= 0) {
            menu[selectedItemIndex].setFillColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setFillColor(sf::Color::Red);
        }
    }

    void MoveDown() {
        if (selectedItemIndex + 1 < menu.size()) {
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
