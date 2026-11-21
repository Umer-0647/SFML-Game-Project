#include "Game.h"           //including header files and external libraries
#include "../include/Menu.h"
#include "MenuView.h"
#include "Board.h"
#include "BoardView.h"
#include <SFML/Graphics.hpp>
#include "Logo.h"

void Game::initialize()
{
    int cellsize = 32;//size of one square on the board in pixels
    Menu menu;
    Board board;//placeholder board, real board is created when the play button is pressed
    board.setGameState(GameState::MAIN_MENU);//starting on menu screen
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);//creating window used for the whole game
    window.setKeyRepeatEnabled(false);//if a key is held down, it counts as one press only
    window.setFramerateLimit(60);//the game draws 60 frames every second
    Board Board(10,10,DEBUG);// This is the actual object of board class.
    MenuView menuView(menu, window);//draws the menu
    BoardView boardView(board, gameWindow);//draws the board.
    Logo myLogo(gameWindow);//draws the logo
    Menu menu; //It creates a menu object and call its constructor.
    while (window.isOpen())
    {
        sf::Event event;//check what the user did
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)//if the player pressed the close button
                window.close();//close the window
        }

        window.clear();//clear the previous frame

        if (board.getGameState() == GameState::MAIN_MENU)
        {
            //make the window and the view match the menu size
            window.setSize(sf::Vector2u(800, 600));
            sf::View view(sf::FloatRect(0, 0, 800, 600));
            window.setView(view);

            menuView.display();
            myLogo.display();

            int option = menu.getSelectedOption();//player selects one of the menu options

            if (menu.getPressedPlayButton() && option >= 0 && option <= 2)//if play button has been selected alongside one of the menu options then
            {
                GameMode mode = GameMode::EASY;//assigning initial value
                switch (option)
                {
                case 0:
                    mode = GameMode::HARD;
                    break;
                case 1:
                    mode = GameMode::NORMAL;
                    break;
                case 2:
                    mode = GameMode::EASY;
                    break;
                }

                board = Board(menu.getBoardWidth(), menu.getBoardHeight(), mode);//build the real board and sets the state to running
                menu.setSelectedOption(-1);//sets menu option back to default
                menu.setPressedPlayButton(false);//sets play button back to default
                sf::sleep(sf::milliseconds(500));//short pause so the cursor doesnt hit the board after clicking play button
            }
            else
            {
                menu.setPressedPlayButton(false);//if the play button was not pressed, or no valid option was selected, set it back to default
            }
        }

        if (board.getGameState() == GameState::RUNNING || board.getGameState() == GameState::WON || board.getGameState() == GameState::LOST)//when the player is still on the board
        {

            window.setSize(sf::Vector2u(board.getWidth() * cellsize, board.getHeight() * cellsize));//resize the window to fit the board
            sf::View view(sf::FloatRect(0, 0, board.getWidth() * cellsize, board.getHeight() * cellsize));//resize the view to fit the board
            window.setView(view);//apply the view to the window
            boardView.display();
        }

        window.display();//displaying the final picture on the screen
    }
}