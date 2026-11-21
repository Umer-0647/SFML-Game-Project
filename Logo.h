#ifndef LOGO_H    //Preprocessor Dircetives . It stands for if not defined. It checks weather the Logo.h file is defined or not in another file.
#define LOGO_H    //Preprocessor Dircetives. It runs when the Logo.h file is not defined.

#include <SFML/Graphics.hpp> 

class Logo        // Here we are defining the our Logo class. It consists the functions related to our logo.
{
private:         // It is an Access Specifier used to access class members only within the class.
	sf::RenderWindow& window;
	sf::Font font;    // The font is kept here so it is loaded only once (in the constructor), not every frame.
	bool fontLoaded;  // Remembers whether the font loaded successfully.
public:          // It is an Access Specifier used to access class members outside the class.
	Logo(sf::RenderWindow& window); // It is tells about the constructor defined in logo.cpp.
	void display();                 // It is used to call the function defined in logo.cpp.       
};
#endif          // Preprocessor directive which is used to complete the indef LOGO_H.
