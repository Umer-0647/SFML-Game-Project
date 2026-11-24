
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>

enum class SelectedBoardSizeType
{
    HEIGHT,
    WIDTH
};

class Menu
{
private:

    std::vector<std::string> options;
    int selectedOption;
    int boardWidth, boardHeight;
    SelectedBoardSizeType selectedBoardSizeType;
    bool pressedPlayButton = false;
public:
    Menu();
    std::vector<std::string> getOptions() const;
    int getSelectedOption() const;
    void setSelectedOption(int option);
    int getBoardWidth() const;
    void setBoardWidth(int width);
    int getBoardHeight() const;
    void setBoardHeight(int height);
    SelectedBoardSizeType getSelectedBoardSizeType() const;
    void setSelectedBoardSizeType(SelectedBoardSizeType type);
    bool getPressedPlayButton();
    void setPressedPlayButton(bool pressedPlayButton);
};

#endif
