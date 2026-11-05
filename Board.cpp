#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

// This is the Default constructor
Board::Board() : width(10), height(10),
gameState(MAIN_MENU), gameMode(DEBUG), revealedCount(0)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    placeMinesRandomly();
}

//  This  Parameterized constructor
Board::Board(int width, int height, GameMode mode)
    : width(width), height(height),
    gameState(RUNNING), gameMode(mode), revealedCount(0)
{
    // Keep board dimensions within array limits
    if (this->width < 1 || this->width > 100)
        this->width = 10;

    if (this->height < 1 || this->height > 100)
        this->height = 10;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    placeMinesRandomly();
}

// Get board width
int Board::getWidth() const
{
    return width;
}

// Get board height
int Board::getHeight() const
{
    return height;
}

// Count surrounding mines
int Board::countMines(int row, int col) const
{
    int mineCount = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < height &&
                newCol >= 0 && newCol < width)
            {
                if (board[newRow][newCol].hasMine)
                {
                    mineCount++;
                }
            }
        }
    }

    return mineCount;
}

// Check whether a cell has a flag
bool Board::hasFlag(int row, int col) const
{
    if (row < 0 || row >= height ||
        col < 0 || col >= width)
    {
        return false;
    }

    return board[row][col].hasFlag;
}

// Place or remove a flag
void Board::toggleFlag(int row, int col)
{
    if (row < 0 || row >= height ||
        col < 0 || col >= width)
    {
        return;
    }

    if (!board[row][col].isRevealed)
    {
        board[row][col].hasFlag = !board[row][col].hasFlag;
    }
}

// Reveal a cell
void Board::revealField(int row, int col)
{
    if (row < 0 || row >= height ||
        col < 0 || col >= width)
    {
        return;
    }

    if (board[row][col].isRevealed ||
        board[row][col].hasFlag)
    {
        return;
    }

    // Protect the first click from hitting a mine
    while (board[row][col].hasMine && revealedCount == 0)
    {
        reset();
    }

    board[row][col].isRevealed = true;

    // If the player hits a mine
    if (board[row][col].hasMine)
    {
        gameState = LOST;
        return;
    }

    revealedCount++;

    int mineCount = countMines(row, col);

    // Automatically open neighbouring cells if there are no mines
    if (mineCount == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                revealField(row + i, col + j);
            }
        }
    }

    // Check whether all safe cells have been revealed
    bool allFieldsRevealed = true;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (!board[i][j].hasMine &&
                !board[i][j].isRevealed)
            {
                allFieldsRevealed = false;
                break;
            }
        }

        if (!allFieldsRevealed)
        {
            break;
        }
    }

    if (allFieldsRevealed)
    {
        gameState = WON;
    }
}

// Check whether a cell is revealed
bool Board::isRevealed(int row, int col) const
{
    if (row < 0 || row >= height ||
        col < 0 || col >= width)
    {
        return false;
    }

    return board[row][col].isRevealed;
}

// Get game mode
GameMode Board::getGameMode() const
{
    return gameMode;
}

// Change game mode
void Board::setGameMode(GameMode mode)
{
    gameMode = mode;
}

// Get game state
GameState Board::getGameState() const
{
    return gameState;
}

// Change game state
void Board::setGameState(GameState state)
{
    gameState = state;
}

// Get information about a cell
char Board::getFieldInfo(int row, int col) const
{
    if (row < 0 || row >= height ||
        col < 0 || col >= width)
    {
        return ' ';
    }

    if (board[row][col].isRevealed)
    {
        if (board[row][col].hasMine)
        {
            return '*';
        }

        int mineCount = countMines(row, col);

        return mineCount == 0 ? '0' : '0' + mineCount;
    }

    if (board[row][col].hasFlag)
    {
        return 'F';
    }

    return ' ';
}

// Reset the board
void Board::reset()
{
    gameState = RUNNING;
    placeMinesRandomly();
}

// Place mines randomly
void Board::placeMinesRandomly()
{
    revealedCount = 0;

    // Clear the entire board
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
            board[i][j].isRevealed = false;
        }
    }

    int minesToPlace = 0;

    switch (gameMode)
    {
    case DEBUG:
        minesToPlace = 10;
        break;

    case EASY:
        minesToPlace = (width * height * 10 + 50) / 100;
        break;

    case NORMAL:
        minesToPlace = (width * height * 20 + 50) / 100;
        break;

    case HARD:
        minesToPlace = (width * height * 30 + 50) / 100;
        break;
    }

    // Do not place more mines than available cells
    if (minesToPlace > width * height)
    {
        minesToPlace = width * height;
    }

    // Place mines at random positions
    while (minesToPlace > 0)
    {
        int row = std::rand() % height;
        int col = std::rand() % width;

        if (!board[row][col].hasMine)
        {
            board[row][col].hasMine = true;
            minesToPlace--;
        }
    }
}






#include "Board.h"
#include <cstdlib>

// Default constructor
Board::Board()
    : width(10), height(10),
    gameMode(DEBUG), gameState(MAIN_MENU),
    revealedCount(0)
{
    placeMinesRandomly();
}

// Parameterized constructor
Board::Board(int w, int h, GameMode mode)
    : width(w), height(h),
    gameMode(mode), gameState(RUNNING),
    revealedCount(0)
{
    // Check board dimensions
    if (width < 1 || width > 100)
    {
        width = 10;
    }

    if (height < 1 || height > 100)
    {
        height = 10;
    }

    placeMinesRandomly();
}

// Get board width
int Board::getWidth() const
{
    return width;
}

// Get board height
int Board::getHeight() const
{
    return height;
}

// Count mines around a cell
int Board::countMines(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return 0;
    }

    int mineCount = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < height &&
                newCol >= 0 && newCol < width)
            {
                if (board[newRow][newCol].hasMine)
                {
                    mineCount++;
                }
            }
        }
    }

    return mineCount;
}

// Check whether a cell has a flag
bool Board::hasFlag(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return false;
    }

    return board[row][col].hasFlag;
}

// Place or remove a flag
void Board::toggleFlag(int row, int col)
{
    if (gameState != RUNNING)
    {
        return;
    }

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return;
    }

    if (!board[row][col].isRevealed)
    {
        board[row][col].hasFlag = !board[row][col].hasFlag;
    }
}

// Reveal a cell
void Board::revealField(int row, int col)
{
    // Check game state and cell boundaries
    if (gameState != RUNNING)
    {
        return;
    }

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return;
    }

    // Do not open an already revealed or flagged cell
    if (board[row][col].isRevealed || board[row][col].hasFlag)
    {
        return;
    }

    // Protect the first click from a mine
    if (board[row][col].hasMine && revealedCount == 0)
    {
        reset();
        revealField(row, col);
        return;
    }

    // Open the selected cell
    board[row][col].isRevealed = true;

    // Check if the selected cell contains a mine
    if (board[row][col].hasMine)
    {
        gameState = LOST;
        return;
    }

    // Increase the number of revealed safe cells
    revealedCount++;

    // Count nearby mines
    int mineCount = countMines(row, col);

    // Open neighbouring cells if there are no nearby mines
    if (mineCount == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                revealField(row + i, col + j);
            }
        }
    }

    // Check whether all safe cells have been revealed
    bool allFieldsRevealed = true;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (!board[i][j].hasMine && !board[i][j].isRevealed)
            {
                allFieldsRevealed = false;
                break;
            }
        }

        if (!allFieldsRevealed)
        {
            break;
        }
    }

    if (allFieldsRevealed)
    {
        gameState = WON;
    }
}

// Check whether a cell is revealed
bool Board::isRevealed(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return false;
    }

    return board[row][col].isRevealed;
}

// Get current game mode
GameMode Board::getGameMode() const
{
    return gameMode;
}

// Change game mode
void Board::setGameMode(GameMode mode)
{
    gameMode = mode;
}

// Get current game state
GameState Board::getGameState() const
{
    return gameState;
}

// Change game state
void Board::setGameState(GameState state)
{
    gameState = state;
}

// Reset the board
void Board::reset()
{
    gameState = RUNNING;
    placeMinesRandomly();
}

// Place mines randomly
void Board::placeMinesRandomly()
{
    revealedCount = 0;

    // Clear the complete board
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
            board[i][j].isRevealed = false;
        }
    }

    // Calculate total number of mines
    int minesToPlace = 0;
    int totalCells = width * height;

    switch (gameMode)
    {
    case DEBUG:
        minesToPlace = 10;
        break;

    case EASY:
        minesToPlace = (totalCells * 10 + 50) / 100;
        break;

    case NORMAL:
        minesToPlace = (totalCells * 20 + 50) / 100;
        break;

    case HARD:
        minesToPlace = (totalCells * 30 + 50) / 100;
        break;
    }

    // Keep at least one safe cell
    if (minesToPlace >= totalCells)
    {
        minesToPlace = totalCells - 1;
    }

    // Place mines at random positions
    while (minesToPlace > 0)
    {
        int row = std::rand() % height;
        int col = std::rand() % width;

        if (!board[row][col].hasMine)
        {
            board[row][col].hasMine = true;
            minesToPlace--;
        }
    }
}

// Get information about a cell
char Board::getFieldInfo(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return ' ';
    }

    if (!board[row][col].isRevealed)
    {
        if (board[row][col].hasFlag)
        {
            return 'F';
        }

        return ' ';
    }

    if (board[row][col].hasMine)
    {
        return '*';
    }

    int mineCount = countMines(row, col);

    return '0' + mineCount;
}
