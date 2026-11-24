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
    Texture tilesTexture;//the tiles.png strip, loaded once in the constructor
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    std::string wonMessage;
    std::string lostMessage;
    std::string returnMessage;
    void loadMessages();
    void displayWon();
    void displayLost();
    void displayBoard();
    public:
    BoardView(Board&board,RenderWindow&window);
    void display();
};
#endif
