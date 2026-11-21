#include "Logo.h"			// It contains the functions. 
#include<iostream>			// library used for standarad input/output functions
#include <SFML/Graphics.hpp> // It is the smfl library which consists sfml classes.
using namespace sf;
using namespace std;
Logo::Logo(RenderWindow& GameWindow) :window(GameWindow)             // It is a class in which the constructor and variables are declared
{                                                                    // Body is empty as we have already intialized in the parameter list.
}
void Logo::display() {                          // It is the a function which has the details about the logo. Display is a function of the logo class.
	Font font;                                  // Font is a class (datatype) in which we are make a object (variable) called font.
	if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf"))        // Here we are calling the a function through are obejct(variable).
	{
		cout << "Font loading failed!" << endl;
		return;
	}

	cout << "Font loaded successfully!" << endl;
	Text l;                       // It is a class in which a object is declared . "l" is a variable used for logo.
	l.setFont(font);              // We are setting the obejct font with the obejct in the Text class.
	l.setString("MINESWEEPER");	  // It is a function which is defined in Text class of SFML.It is used to set the name for the game.
	l.setCharacterSize(96);       // It is a function used to set the string size .
	l.setFillColor(Color::Red);   // It is a function used to give colour to my text.
	l.setStyle(Text::Bold);       // It is a function used to give style to my text.
	l.setOrigin(l.getLocalBounds().width / 2, l.getLocalBounds().height / 2);    // It is a function used to set the origin.It has two more functions in its argument.
	l.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 200);         // It ia a function used to set the positon othe text on the screen. Similarly it uses two functions in the argument.
	window.draw(l);               //This is used to give instruction to draw the text object in the renderwindow.

}



