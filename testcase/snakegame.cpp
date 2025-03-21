#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 17;
int x, y, foodX, foodY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
    srand(time(0)); // Ensure different food positions each run
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    foodX = rand() % width;
    foodY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls"); // Clears console on Windows
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left border

            if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == foodY && j == foodX)
                cout << "F"; // Food
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }

            if (j == width - 1) cout << "#"; // Right border
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % width;
        foodY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Controls speed
    }

    cout << "Game Over! Press any key to exit...";
    _getch(); // Prevents console from closing immediately
    return 0;
}
    
    // The code is well-commented, but here’s a brief overview of the main functions: 
    
    // Setup()  initializes the game state, including the snake’s initial position, food position, and score. 
    // Draw()  renders the game board, including the snake, food, and borders. 
    // Input()  handles user input to change the snake’s direction. 
    // Logic()  updates the game state based on the current direction, checks for collisions, and handles food consumption. 
    
    // To compile and run the game, you can use a C++ compiler like  g++  or  clang++ . For example, you can compile the code using the following command: 
    // g++ snakegame.cpp -o snakegame 
    // Then, run the compiled executable: 
    // ./snakegame 
    // You can control the snake using the arrow keys (up, down, left, right) and exit the game by pressing the ‘x’ key. 
    // This simple Snake game is a good starting point for learning game development concepts in C++. You can further enhance the game by adding features like increasing difficulty levels, adding obstacles, or implementing a two-player mode. 
    // 5.  How to Create a Simple Snake Game in Python 
    // Here’s a simple implementation of the Snake game in Python using the  Pygame library. Pygame is a set of Python modules designed for writing video games.
