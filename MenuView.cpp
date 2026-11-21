
#include "MenuView.h"
#include <string>

// this Constructor connects this MenuView with the Menu and game window.
// We also load the font here so we don't have to load it again and again.
MenuView::MenuView(Menu& menu, sf::RenderWindow& window)
    : menu(menu), window(window)
{
    font.loadFromFile("./assets/font.ttf");
}


// This function displays the board width and height on the screen.
// The player can select either value and change it using arrow keys.
void MenuView::displayBoardSizeInput()
{
    // These four text objects will show the labels and their current values.
    sf::Text widthText;
    sf::Text heightText;
    sf::Text widthValue;
    sf::Text heightValue;

    // Set the same font for all four text objects.
    widthText.setFont(font);
    heightText.setFont(font);
    widthValue.setFont(font);
    heightValue.setFont(font);

    // Show the names of the two board dimensions.
    widthText.setString("Width:");
    heightText.setString("Height:");

    // Get the current width and height from the Menu class.
    // to_string converts the integer values into strings so SFML can display them.
    widthValue.setString(std::to_string(menu.getBoardWidth()));
    heightValue.setString(std::to_string(menu.getBoardHeight()));

    // Set the size of all the text.
    widthText.setCharacterSize(24);
    heightText.setCharacterSize(24);
    widthValue.setCharacterSize(24);
    heightValue.setCharacterSize(24);

    // Make the labels white so they are clearly visible.
    widthText.setFillColor(sf::Color::White);
    heightText.setFillColor(sf::Color::White);

    // Position the Width and Height labels on the left side.
    widthText.setPosition(window.getSize().x / 2 - 100,
        window.getSize().y / 2 - 100);

    heightText.setPosition(window.getSize().x / 2 - 100,
        window.getSize().y / 2 - 50);

    // Position their values on the right side of the labels.
    widthValue.setPosition(window.getSize().x / 2 + 100,
        window.getSize().y / 2 - 100);

    heightValue.setPosition(window.getSize().x / 2 + 100,
        window.getSize().y / 2 - 50);

    // Find the current mouse position inside our game window.
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    // Check whether the player has clicked on the width or height value.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // If the player clicks on the width value, select WIDTH.
        if (widthValue.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            menu.setSelectedBoardSizeType(SelectedBoardSizeType::WIDTH);
        }

        // Otherwise, check if the player clicked on the height value.
        else if (heightValue.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            menu.setSelectedBoardSizeType(SelectedBoardSizeType::HEIGHT);
        }
    }

    // Now check which dimension the player has selected.
    // The selected value will become red.

    if (menu.getSelectedBoardSizeType() == SelectedBoardSizeType::WIDTH)
    {
        // Red colour shows that width is currently selected.
        widthValue.setFillColor(sf::Color::Red);

        // Up arrow increases the width.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            // We don't allow the width to go above 52.
            if (menu.getBoardWidth() < 52)
            {
                menu.setBoardWidth(menu.getBoardWidth() + 1);

                // A small delay prevents the value from increasing too quickly.
                sf::sleep(sf::milliseconds(200));
            }
        }

        // Down arrow decreases the width.
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            // We don't allow the width to go below 10.
            if (menu.getBoardWidth() > 10)
            {
                menu.setBoardWidth(menu.getBoardWidth() - 1);
                sf::sleep(sf::milliseconds(200));
            }
        }
    }

    // Do the same thing for height if HEIGHT is selected.
    else if (menu.getSelectedBoardSizeType() == SelectedBoardSizeType::HEIGHT)
    {
        // Red colour shows that height is currently selected.
        heightValue.setFillColor(sf::Color::Red);

        // Increase height using the Up arrow.
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (menu.getBoardHeight() < 52)
            {
                menu.setBoardHeight(menu.getBoardHeight() + 1);
                sf::sleep(sf::milliseconds(200));
            }
        }

        // Decrease height using the Down arrow.
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (menu.getBoardHeight() > 10)
            {
                menu.setBoardHeight(menu.getBoardHeight() - 1);
                sf::sleep(sf::milliseconds(200));
            }
        }
    }

    // Finally, draw all four text objects on the game window.
    window.draw(widthText);
    window.draw(heightText);
    window.draw(widthValue);
    window.draw(heightValue);
}


// This function creates and displays the PLAY button.
// When the player clicks it, we inform the Menu class.
void MenuView::displayPlayButton()
{
    // Create a rectangular button with a width of 300 and height of 50.
    sf::RectangleShape button(sf::Vector2f(300, 50));

    // Place the button in the centre, below the menu options.
    button.setPosition(
        window.getSize().x / 2 - 150,
        window.getSize().y / 2 + 150
    );

    // Keep the inside transparent and show a white border.
    button.setFillColor(sf::Color::Transparent);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);

    // Create the text that will appear inside the button.
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("PLAY");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    // Get the size of the PLAY text.
    // We use this information to place it exactly in the centre.
    sf::FloatRect textBounds = buttonText.getLocalBounds();

    buttonText.setOrigin(
        textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2
    );

    // Place the text in the middle of the rectangular button.
    buttonText.setPosition(
        button.getPosition().x + 150,
        button.getPosition().y + 25
    );

    // Get the mouse position to check whether it is over the button.
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    // Check if the mouse is inside the button.
    if (button.getGlobalBounds().contains(mouse.x, mouse.y))
    {
        // Highlight the button when the mouse moves over it.
        button.setFillColor(sf::Color::Red);

        // If the player clicks the button, set its pressed value to true.
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            menu.setPressedPlayButton(true);
        }
    }

    // Draw the button first and then draw its text.
    window.draw(button);
    window.draw(buttonText);
}


// This is the main display function.
// It draws the complete menu whenever the game displays the main menu.
void MenuView::display()
{
    // Clear the previous frame before drawing the new one.
    window.clear();

    // Get the current mouse position.
    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    // Loop through all the options stored in the Menu class.
    for (int i = 0; i < menu.getOptions().size(); i++)
    {
        // Create a separate text object for each menu option.
        sf::Text text;

        text.setFont(font);

        // Get the name of the current option from the Menu class.
        text.setString(menu.getOptions()[i]);

        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        // Find the size of the text so we can place it in the centre.
        sf::FloatRect textBounds = text.getLocalBounds();

        text.setOrigin(
            textBounds.left + textBounds.width / 2,
            textBounds.top + textBounds.height / 2
        );

        // Place each option below the previous one.
        // Multiplying i by 50 creates equal space between the options.
        text.setPosition(
            window.getSize().x / 2,
            window.getSize().y / 2 + i * 50
        );

        // Check if the mouse is currently over this menu option.
        if (text.getGlobalBounds().contains(mouse.x, mouse.y))
        {
            // Highlight the option in red.
            text.setFillColor(sf::Color::Red);

            // Save the selected option when the player clicks it.
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                menu.setSelectedOption(i);
            }
        }

        // Keep the previously selected option highlighted in red.
        if (menu.getSelectedOption() == i)
        {
            text.setFillColor(sf::Color::Red);
        }

        // Draw the current menu option on the screen.
        window.draw(text);
    }

    // Display the board size controls and PLAY button.
    displayBoardSizeInput();
    displayPlayButton();
}
