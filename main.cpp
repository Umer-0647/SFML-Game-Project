#include <SFML/Graphics.hpp>  // Sfml header files are included to access related functions.
#include "Logo.h"             // logo header file which declare logo class.
using namespace sf;
int main()
{
RenderWindow gameWindow( // here Render Window is Class of SMFL in  which an object gameWindow is being created.
        VideoMode(1000, 700),// here Video Mode is another class of SFMlwith is 1000 width and 700 is height.
        "Minesweeper" // Title Minesweeper.
    );
    gameWindow.setFramerateLimit(60); // Here we use a function for the object so that we set frame limit.
    Logo myLogo(gameWindow); // It creates a logo object and call its constructor passing the existing windowgame by reference.
    while (gameWindow.isOpen())
    {
     Event event; // this is a clas in which an object is created to check for user inputs.
        while (gameWindow.pollEvent(event))  // It is used to process the pending game events.
        {
            if (event.type == Event::Closed)
            {
                gameWindow.close();
            }
        }
        gameWindow.clear(Color::Black); // It is used to remove previous drawing and prpares for new frame.
        myLogo.display();// Here we are calling the obejct of logo class and calling the function of logo class.
        gameWindow.display(); // It is used to draw the complete render frame.
    }

    return 0;
}