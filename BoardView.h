#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include"Board.h"
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
class BoardView
{
    private:    
    Board &board;
    RenderWindow& window;
    Font font;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    void displayWon();
    void displayLost();
    void displayBoard();
    public:
    BoardView(Board&board,RenderWindow&window);
    void display();
};
#endif
