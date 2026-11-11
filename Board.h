#ifndef BOARD_H
#define BOARD_H

enum GameMode
{
    DEBUG,
    EASY,
    NORMAL,
    HARD
};

enum GameState
{
    MAIN_MENU,
    RUNNING,
    WON,
    LOST
};

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class Board
{
private:

    int width;
    int height;

    Field board[100][100];

    GameMode gameMode;
    GameState gameState;

    int revealedCount;

    void placeMinesRandomly();

public:

    // Constructors
    Board();
    Board(int w, int h, GameMode mode);

    // Board size
    int getWidth() const;
    int getHeight() const;

    // Cell operations
    int countMines(int row, int col) const;
    bool hasFlag(int row, int col) const;
    void toggleFlag(int row, int col);
    void revealField(int row, int col);
    bool isRevealed(int row, int col) const;
    char getFieldInfo(int row, int col) const;

    // Game mode
    GameMode getGameMode() const;
    void setGameMode(GameMode mode);

    // Game state
    GameState getGameState() const;
    void setGameState(GameState state);

    // Reset game
    void reset();
};

#endif



