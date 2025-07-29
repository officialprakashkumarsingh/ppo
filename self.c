#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

// Constants for the game
#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE_LENGTH (WIDTH * HEIGHT)

// Directional constants
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// Snake structure
typedef struct {
    int x;
    int y;
} Position;

// Game variables
Position snake[MAX_SNAKE_LENGTH];
int snakeLength = 1;
int direction = RIGHT;
Position food;
int score = 0;
int gameOver = 0;
int speed = 100; // milliseconds delay

// Function prototypes
void setupGame();
void drawGame();
void updateSnake();
void generateFood();
int checkCollision();
void gotoxy(int x, int y);
void hideCursor();

int main() {
    setupGame();
    hideCursor();
    
    while (!gameOver) {
        drawGame();
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
                case 'w':
                case 'W':
                    if (direction != DOWN) direction = UP;
                    break;
                case 's':
                case 'S':
                    if (direction != UP) direction = DOWN;
                    break;
                case 'a':
                case 'A':
                    if (direction != RIGHT) direction = LEFT;
                    break;
                case 'd':
                case 'D':
                    if (direction != LEFT) direction = RIGHT;
                    break;
                case 27: // ESC key
                    gameOver = 1;
                    break;
            }
        }
        updateSnake();
        Sleep(speed);
    }
    
    // Game over screen
    system("cls");
    printf("\n\n\t\tGame Over!\n");
    printf("\t\tFinal Score: %d\n", score);
    printf("\t\tPress any key to exit...\n");
    _getch();
    
    return 0;
}

void setupGame() {
    srand(time(NULL));
    // Initialize snake at the center
    snake[0].x = WIDTH / 2;
    snake[0].y = HEIGHT / 2;
    generateFood();
}

void drawGame() {
    system("cls");
    int i, j;
    
    // Draw top border
    printf("\t");
    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    
    // Draw game area
    for (i = 0; i < HEIGHT; i++) {
        printf("\t#");
        for (j = 0; j < WIDTH; j++) {
            int isSnake = 0;
            for (int k = 0; k < snakeLength; k++) {
                if (snake[k].x == j && snake[k].y == i) {
                    printf("O");
                    isSnake = 1;
                    break;
                }
            }
            if (!isSnake) {
                if (food.x == j && food.y == i)
                    printf("*");
                else
                    printf(" ");
            }
        }
        printf("#\n");
    }
    
    // Draw bottom border
    printf("\t");
    for (i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    
    // Display score
    printf("\tScore: %d\n", score);
    printf("\tUse W,A,S,D to move, ESC to quit\n");
}

void updateSnake() {
    // Store previous head position
    Position prevHead = snake[0];
    Position prev;
    
    // Move head based on direction
    switch (direction) {
        case UP:
            snake[0].y--;
            break;
        case DOWN:
            snake[0].y++;
            break;
        case LEFT:
            snake[0].x--;
            break;
        case RIGHT:
            snake[0].x++;
            break;
    }
    
    // Move body
    for (int i = 1; i < snakeLength; i++) {
        prev = snake[i];
        snake[i] = prevHead;
        prevHead = prev;
    }
    
    // Check for food collision
    if (snake[0].x == food.x && snake[0].y == food.y) {
        snakeLength++;
        score += 10;
        if (speed > 50) speed -= 2; // Increase speed slightly
        generateFood();
    }
    
    // Check for collisions with walls or self
    if (checkCollision()) {
        gameOver = 1;
    }
}

void generateFood() {
    int validPosition = 0;
    while (!validPosition) {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
        validPosition = 1;
        // Ensure food doesn't spawn on snake
        for (int i = 0; i < snakeLength; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                validPosition = 0;
                break;
            }
        }
    }
}

int checkCollision() {
    // Check wall collision
    if (snake[0].x < 0 || snake[0].x >= WIDTH || 
        snake[0].y < 0 || snake[0].y >= HEIGHT) {
        return 1;
    }
    
    // Check self collision (skip head)
    for (int i = 1; i < snakeLength; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            return 1;
        }
    }
    return 0;
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}