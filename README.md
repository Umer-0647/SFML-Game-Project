# SFML-Game-Project
2D game developed in C++ using SFML for our first-semester programming project.

## Requirements
- Visual Studio 2022 or newer with **Desktop development with C++**
- SFML **2.6.2** (Visual C++ 64-bit build) extracted to `C:\SFML\SFML-2.6.2`

**Option 1: Visual Studio.** Open `MinesweeperGame.slnx`, set the toolbar to **x64**, and press **Ctrl+F5**. The SFML DLLs are copied automatically after each build.

## How to play
- Pick a difficulty (HARD / MEDIUM / EASY), set the board width and height (click a number, then use the Up/Down arrow keys), and press **PLAY**.
- **Left click** reveals a cell. **Right click** places or removes a flag.
- When you win or lose, press **Enter** to go back to the menu or **Esc** to quit.

## Project structure
| File | Purpose |
|---|---|
| `main.cpp` | Starts the game |
| `Game.h / Game.cpp` | Main game loop, switches between menu and board |
| `Board.h / Board.cpp` | Minesweeper logic (mines, flags, revealing, win/lose) |
| `Board.View.cpp / BoardView.h` | Draws the board and handles mouse clicks |
| `Menu.h / Menu.cpp` | Menu data (difficulty, board size) |
| `MenuView.h / MenuView.cpp` | Draws the menu and handles input |
| `Logo.h / Logo.cpp` | Draws the MINESWEEPER title |
| `assets/` | `font.ttf` (DejaVu Sans, free licence in `FONT-LICENSE.txt`) and `tiles.png` (12 tiles of 32x32: numbers 0-8, mine, covered, flag). Put `minesweeper_explosion.wav` here too for the explosion sound |
