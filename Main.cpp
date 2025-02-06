#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include "Game.cpp"

int main() {
    Game game;
    game.init();

    while (game.isRunning()) {
        game.render();  // Render the current game state
        game.handleInput();  // Get input from user
        game.update();  // Update the game state (move Pac-Man and ghosts)
    }

    std::cout << "Game Over! Final Score: " << game.getScore() << std::endl;
    system("pause");  // Pause to see the final score
    return 0;
}