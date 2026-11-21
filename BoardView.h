#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include"Board.h"
#include<"SFML/Graphics.hpp">
#include<iostream>
using namespace sf;
class boardView
{
    private:
    Board &board;
    RenderWindow& window;
    void displayWon();
    void displayLost();
    void displayBoard();
    public:
    BoardView(Board&board,RenderWindow&window);
    void display();
};
#endif
