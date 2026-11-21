#include "Menu.h"
using namespace std;
Menu::Menu() {
	selectedOption = -1;
	selectedBoardSizeType = SelectedBoardSizeType :: WIDTH;
	options.push_back("HARD");
	options.push_back("MEDIUM");
	options.push_back("EASY");
	boardWidth = 10;
	boardHeight = 10;
}
Menu::Menu(string options[], int size) {
	selectedOption = -1;
	selectedBoardSizeType = SelectedBoardSizeType::WIDTH;
	for (int i = 0;i < size;i++) {
		this->options.push_back(options[i]);
	}
	boardWidth = 10;
	boardHeight = 10;
}
vector<string>Menu::getOptions()const {
	return options;
}
int Menu::getBoardWidth() const {
	return boardWidth;
}
void Menu::setBoardWidth(int width) {
	this->boardWidth = width;
}
int Menu::getBoardHeight() const {
	return boardHeight;
}
void Menu::setBoardHeight(int height) {
	this->boardHeight = height;
}
SelectedBoardSizeType Menu::getSelectedBoardSizeType() const//this function is returning whether width or height is the selected size
{
	return selectedBoardSizeType;// it is giving back the saved choice
}
void Menu::setSelectedBoardSizeType(SelectedBoardSizeType newType) // this function is saving whether width or height is the selected size
{
	selectedBoardSizeType = newType;//it is saving the new choice in the variable
}
int Menu::getSelectedOption() const//the function is returning the chosen difficulty as a number(0=Hard,1=Normal,2=Easy,-1=Not chosen yet)
{
	return selectedOption;//its giving back the saved number 
}
void Menu::setSelectedOption(int newOption)//thiss function is saving the chosen difficulty but only when that place exists in the list of options
{
	if (newOption >= -1 && newOption < (int)options.size())//it is checking the validity of the number 
	{
		selectedOption = newOption;//the number is within the range so it is being saved
	}
}
bool Menu::getPressedPlayButton()//this function is returning whether the play button was pressed or not
{
	return pressedPlayButton;//it is giving back the answer as true(button was pressed) or false(button was not pressed)
}
void Menu::setPressedPlayButton(bool pressed)//this function is saving whether the play button was pressed
{
	pressedPlayButton = pressed;//it is saving the new true or false value
}
