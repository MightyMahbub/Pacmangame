#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include <windows.h> // For Sleep() and system("cls")

class Game {
public:
    Game() : score(0), running(true), pacmanX(6), pacmanY(6) {
        initMap();
    }

    void init() {
        std::cout << "Game started! Use W/A/S/D or arrow keys to move. Press 'Q' to quit.\n";
    }

    bool isRunning() const {
        return running;
    }

    void render() {
        system("cls");  // Clear screen

        // Render the map
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (i == pacmanY && j == pacmanX) {
                    std::cout << 'O';  // Pac-Man's visible character
                } else {
                    std::cout << map[i][j];  // Render the map
                }
            }
            std::cout << std::endl;
        }

        std::cout << "Score: " << score << std::endl;
    }

    void handleInput() {
        if (_kbhit()) {
            char input = _getch();  // Get user input
            if (input == 'q') {
                running = false;  // Quit the game
            }
            move(input);
        }
    }

    void update() {
        // Add any updates to game logic here
        // For example, we could increase the score every few seconds, etc.
        Sleep(100);  // Small delay for smooth game rendering
    }

    int getScore() const {
        return score;
    }

private:
    static const int width = 20;   // Increased map width
    static const int height = 10;  // Increased map height
    char map[height][width];       // Game map

    int pacmanX, pacmanY;  // Pac-Man's position on the map
    int score;             // Current score
    bool running;          // Game running flag

    void initMap() {
        // Filling the map with walls and empty spaces
        const char* tempMap[height] = {
            "####################",
            "#..........#.......#",
            "#.#######..#......#.",
            "#.#.....#..#......#.",
            "#.#.###.#..#######.#",
            "#...#P#....#.....#.#",
            "#.#######..#.#####.#",
            "#..........#.......#",
            "####################",
            "####################"
        };

        // Initialize the map array
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                map[i][j] = tempMap[i][j];
            }
        }
    }

    void move(char direction) {
        // Move Pac-Man based on the user input
        int newX = pacmanX;
        int newY = pacmanY;

        if (direction == 'w' || direction == 72) {  // Up (W or Arrow Up)
            newY--;
        }
        if (direction == 's' || direction == 80) {  // Down (S or Arrow Down)
            newY++;
        }
        if (direction == 'a' || direction == 75) {  // Left (A or Arrow Left)
            newX--;
        }
        if (direction == 'd' || direction == 77) {  // Right (D or Arrow Right)
            newX++;
        }

        // Check if the new position is valid (not a wall)
        if (map[newY][newX] != '#') {
            pacmanX = newX;  // Move Pac-Man to the new position
            pacmanY = newY;
            score++;  // Increase score for each valid move
        }
    }
};
