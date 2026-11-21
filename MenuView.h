
#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <SFML/Graphics.hpp>
#include "Menu.h"

class MenuView
{
private:
    Menu& menu;
    sf::RenderWindow& window;
    sf::Font font;

    void displayBoardSizeInput();
    void displayPlayButton();

public:
    MenuView(Menu& menu, sf::RenderWindow& window);
    void display();
};

#endif
