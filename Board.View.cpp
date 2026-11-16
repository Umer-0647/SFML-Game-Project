#include<iostream>
#include"Board.h"
#include<SFML/Graphics.hpp>
#include"BoardView.h"
using namespace sf;
using namespace std;
BoardView::BoardView(Board& board, RenderWindow& window) :board(board), window(window){}
void BoardView::displayWon()
{
	Font font;
	if (!font.loadFromFile("./assests/font.ttf")) {
		cout<< "Font could not be loaded ";
		return;
	}
	Text t;
	t.setFont(font);
	t.setCharacterSize(36);
	t.setString("You Won!");
	t.setFillColor(Color::Green);
	t.setStyle(Text::Bold);
	t.setOrigin(t.getLocalBounds().width / 2, t.getLocalBounds().height / 2);
	t.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(t);

	if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Escape)) {
		if (board.getGameState() == RUNNING) {
			board.setGameState(MAIN_MENU);
		}
		else if (board.getGameState() == MAIN_MENU) {
			window.close();
		}
	}
	Text PressEnterText;
	PressEnterText.setFont(font);
	PressEnterText.setString("PressEn")

}

