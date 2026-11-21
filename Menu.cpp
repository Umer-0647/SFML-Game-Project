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