#include<iostream>
#include"Board.h"
#include<SFML/Graphics.hpp>
#include"BoardView.h"
using namespace sf;			
using namespace std;
BoardView::BoardView(Board& board, RenderWindow& window)
	: board(board), window(window)
{
	font.loadFromFile("./assets/font.ttf");

	// Load bomb explosion sound
	if (!explosionBuffer.loadFromFile(".assets/minesweeper_explosion.wav"))
		
	{
		cout << "Sound file could not be loaded!" << endl;
	}
	else
	{
		cout << "Sound loaded successfully!" << endl;
	}

	explosionSound.setBuffer(explosionBuffer);
}
void BoardView::displayWon()
{
	
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
		if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            board.setGameState(MAIN_MENU);
        }
		else if (board.getGameState() == MAIN_MENU) {
			window.close();
		}
	}
	Text PressEnterText;
	PressEnterText.setFont(font);
	PressEnterText.setString("Press Enter to return to the main menu");
	PressEnterText.setCharacterSize(14);
	PressEnterText.setFillColor(Color::Red);
	PressEnterText.setStyle(Text::Bold);
	PressEnterText.setOrigin(PressEnterText.getLocalBounds().width/2,PressEnterText.getLocalBounds().height/2);
	PressEnterText.setPosition(window.getSize().x/2,window.getSize().y/2+25);
	window.draw(PressEnterText);
}
void BoardView::displayLost(){

	Text l;
	l.setFont(font);
	l.setCharacterSize(36);
	l.setString("You Lost!");
	l.setFillColor(Color::Green);
	l.setStyle(Text::Bold);
	l.setOrigin(l.getLocalBounds().width / 2, l.getLocalBounds().height / 2);
	l.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	window.draw(l);

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
	PressEnterText.setString("Press Enter to return to the main menu");
	PressEnterText.setCharacterSize(14);
	PressEnterText.setFillColor(Color::Red);
	PressEnterText.setStyle(Text::Bold);
	PressEnterText.setOrigin(PressEnterText.getLocalBounds().width/2,PressEnterText.getLocalBounds().height/2);
	PressEnterText.setPosition(window.getSize().x/2,window.getSize().y/2+25);
	window.draw(PressEnterText);

}
void BoardView::displayBoard()//it draws every cell on the grid and then reads the mouse clicks
{
	int cellsize = 32;//size of one square on the board in pixels

	sf::Texture tex;//an image will be loaded in memory
	tex.loadFromFile("./assets/tiles.png");//it will load the strip of 12 pictures from the assets folder
	sf::Sprite sprite(tex);//the object that is dawn on the window 

	for (int row = 0; row < board.getHeight(); row++)//this nested loop will visit every cell of the grid
	{
		for (int col = 0; col < board.getWidth(); col++)
		{
			char f = board.getFieldInfo(row, col);//it asks the board to show which character for this cell and store it in f
			if (board.getGameState() == GameState::LOST)
{
	explosionSound.play();
}
			int imageindex;//it will give the position of the picture inside the file tiles.png
			if (f == '*')//if it is s mine
			{
				imageindex = 9;//store the picture number of mine in imageindex
			}
			else if (f == ' ')//if it is a covered cell
			{
				imageindex = 10;//store the picture number of covered tile in imageindex
			}
			else if (f == 'F')//if it is a flagged cell
			{
				imageindex = 11;//store the picture number of flagged cell in imageindex
			}
			else//it is a digit character from '0' to'8'
			{
				imageindex = f - '0';//subtract the ASCII value 48 from the character to turn it into a number from the range 0 to 8
			}
			sprite.setTextureRect(sf::IntRect(imageindex * cellsize, 0, cellsize, cellsize));//it shows only the required pictured 32x32 piece of strip based on imageindex
			sprite.setPosition(col * cellsize, row * cellsize);//it places that picture on the window, traversing across the coloumn first and then down the row
			window.draw(sprite);//it paints the sprite on the window
		}
	}


	sf::Vector2i pos = sf::Mouse::getPosition(window);//it stores the mouses's position in pixels  from the windows top-left corner. The value is stored in pair that is why vector2i is used.
	int col = pos.x / cellsize;//to get the coloumn under the mouse we divide the pixels by 32 to get the coloumn number
	int row = pos.y / cellsize;//to get the row under the mouse we divide the pixels by 32 to get the row number

	if (board.getGameState() == GameState::RUNNING) {//this check only reacts to clicks when the game is running
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//if left button of mouse is clicked
		{
			board.revealField(row, col);//tells the board to reveal this cell
			sf::sleep(sf::milliseconds(200));////a pause of 0.2 seconds so one click is not counted in many frames
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))//if right button of mouse is clicked
		{
			board.toggleFlag(row, col);//tells the board to place or remove a flag on this cell
			sf::sleep(sf::milliseconds(200));//prevents the flag from being flipped several times
		}
	}
}
void BoardView::display()// it draws the board and then displays the win or lose message if the game has ended
{
	displayBoard();//first it draws the board so it is visible behind any message


	if (board.getGameState() == GameState::WON)//if the player won
	{
		displayWon();//draw the won message on the board
	}
	else if (board.getGameState() == GameState::LOST)//if the player lost
	{
		displayLost();//draw the lost message on the board
	}
}
