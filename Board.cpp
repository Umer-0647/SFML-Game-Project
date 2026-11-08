#include "Board.h"
#include <cstdlib>

Board::Board()
    : width(10), height(10),
    gameMode(DEBUG), gameState(MAIN_MENU),              //This is the constructor 
    revealedCount(0)                                    //which makes the default
{                                                       //state of the game 
    placeMinesRandomly();
}

Board::Board(int w, int h, GameMode mode)               //Contructor is parameterized
    : width(w), height(h),                              //by user  
    gameMode(mode), gameState(RUNNING),
    revealedCount(0)
{
    
    if (width < 1 || width > 100)                            
    {
        width = 10;                                     //This checks the parameters
    }                                                   //are valid or not

    if (height < 1 || height > 100)
    {
        height = 10;
    }

    placeMinesRandomly();
}

int Board::getWidth() const
{                                                        //This takes the 
    return width;                                        //board width
}

int Board::getHeight() const                             //This takes the 
{                                                        //board height
    return height;
}

int Board::countMines(int row, int col) const                       //This counts that 
{                                                                   //how many mines 
    if (row < 0 || row >= height || col < 0 || col >= width)        //are around cell
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

bool Board::hasFlag(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)    //Check that a 
    {                                                           //cell has a Flag
        return false;
    }

    return board[row][col].hasFlag;
}

void Board::toggleFlag(int row, int col)
{
    if (gameState != RUNNING)
    {                                                         // Place or remove a flag
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
    if (gameState != RUNNING)                           // Check the game state and 
    {                                                   // cell boundaries
        return;
    }

    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return;
    }

    if (board[row][col].isRevealed || board[row][col].hasFlag)
    {                                                  // Do not open an already 
        return;                                        //opened or flagged cell
    }


    board[row][col].isRevealed = true;                   // Open the selected cell

    if (board[row][col].hasMine)
    {                                               // This  Checks if the selected 
        gameState = LOST;                           //cell contains a mine
        return;
    }

    revealedCount++;                    // Increase the number of revealed safe cells   

    int mineCount = countMines(row, col);          // Count nearby mines

    if (mineCount == 0)                                   //This Opens all 
                                                          //neighbouring cells if 
    {                                                    //there are no nearby mines
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                revealField(row + i, col + j);
            }
        }
    }

    bool allFieldsRevealed = true;                      //This checks all safe cells
                                                       //have been revealed or not
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

bool Board::isRevealed(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {                                            // Check whether a cell is 
        return false;                            //already revealed
    }

    return board[row][col].isRevealed;
}

GameMode Board::getGameMode() const
{                                                         // Get current game mode
    return gameMode;
}

void Board::setGameMode(GameMode mode)
{                                                         // Change game mode
    gameMode = mode;
}

GameState Board::getGameState() const
{                                                         // Get current game state

    return gameState;
}

void Board::setGameState(GameState state)
{                                                    // Change game state
    gameState = state;
}

void Board::reset()
{
    gameState = RUNNING;                        //This Resets the board
    placeMinesRandomly();
}

                 // Place mines randomly
void Board::placeMinesRandomly()
{
    revealedCount = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)           // Clears the complete board
        {
            board[i][j].hasMine = false;
            board[i][j].hasFlag = false;
            board[i][j].isRevealed = false;
        }
    }

    int minesToPlace = 0;
    int totalCells = width * height;

    switch (gameMode)                              // Calculate total number of mines
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

    if (minesToPlace >= totalCells)                 // Keeps at least one safe cell
    {
        minesToPlace = totalCells - 1;
    }

    while (minesToPlace > 0)
    {
        int row = std::rand() % height;              //Ths  Places mines at 
        int col = std::rand() % width;               //random positions

        if (!board[row][col].hasMine)
        {
            board[row][col].hasMine = true;
            minesToPlace--;
        }
    }
}

char Board::getFieldInfo(int row, int col) const
{
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return ' ';                                // Get information about a cell
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
