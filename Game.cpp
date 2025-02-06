#include <iostream>
#include <conio.h>  // For _kbhit() and _getch()
#include <windows.h> // For Sleep() and system("cls")
#include <vector>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

class Game {
public:
    Game() : score(0), running(true), pacmanX(1), pacmanY(1), lives(3) {
        srand(time(0));  // Seed for random number generation
        initMap();
        initGhosts();
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
                } else if (isGhost(i, j)) {
                    std::cout << 'G';  // Ghost's visible character
                } else {
                    std::cout << map[i][j];  // Render the map
                }
            }
            std::cout << std::endl;
        }

        std::cout << "Score: " << score << " Lives: " << lives << std::endl;
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
        moveGhosts();
        checkCollisions();
        Sleep(100);  // Small delay for smooth game rendering
    }

    int getScore() const {
        return score;
    }

private:
    static const int width = 21;   // Increased map width
    static const int height = 11;  // Increased map height
    char map[height][width];       // Game map

    int pacmanX, pacmanY;  // Pac-Man's position on the map
    int score;             // Current score
    int lives;             // Number of lives
    bool running;          // Game running flag

    struct Ghost {
        int x, y;
    };

    std::vector<Ghost> ghosts;

    void initMap() {
        // Filling the map with walls and empty spaces
        const char* tempMap[height] = {
            "#####################",
            "#........#..........#",
            "#.###.###.#.#########",
            "#.#...#...#.........#",
            "#.#.###.###.###.###.#",
            "#...#...#...#...#...#",
            "###.###.###.###.###.#",
            "#........#...#...#...#",
            "#.###.###.###.###.###",
            "#...................#",
            "#####################"
        };

        // Initialize the map array
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                map[i][j] = tempMap[i][j];
            }
        }
    }

    void initGhosts() {
        ghosts.push_back({9, 9});
        ghosts.push_back({9, 1});
        ghosts.push_back({1, 9});
    }

    bool isGhost(int y, int x) {
        for (const auto& ghost : ghosts) {
            if (ghost.x == x && ghost.y == y) {
                return true;
            }
        }
        return false;
    }

    void move(char direction) {
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
            pacmanX = newX;
            pacmanY = newY;
            if (map[newY][newX] == '.') {
                score += 10;  // Increase score for eating dots
                map[newY][newX] = ' ';  // Remove the dot
            }
        }
    }

    void moveGhosts() {
        for (auto& ghost : ghosts) {
            int direction = rand() % 4;  // Random direction
            int newX = ghost.x;
            int newY = ghost.y;

            switch (direction) {
                case 0: newY--; break;  // Up
                case 1: newY++; break;  // Down
                case 2: newX--; break;  // Left
                case 3: newX++; break;  // Right
            }

            if (map[newY][newX] != '#') {
                ghost.x = newX;
                ghost.y = newY;
            }
        }
    }

    void checkCollisions() {
        for (const auto& ghost : ghosts) {
            if (ghost.x == pacmanX && ghost.y == pacmanY) {
                lives--;
                if (lives <= 0) {
                    running = false;
                } else {
                    pacmanX = 1;
                    pacmanY = 1;
                }
            }
        }
    }
};