#include <iostream>
#include <windows.h>

#include "Window.h"

int main()
{
    try
    {
        window::Window window_0(512, 512, "Snake", "bless-48x48.png");

        float coords[] = { 0.0f, 0.0f,  0.0f, 0.4f,  0.4f, 0.4f,  0.4f, 0.0f };

        while (!glfwWindowShouldClose(window_0.getWindow()))
        {
            window_0.window_resize();
            glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();

            if (glfwGetKey(window_0.getWindow(), GLFW_KEY_W) && coords[3] < 1) {
                for (size_t i = 1; i < sizeof(coords) / sizeof(coords[0]); i += 2) {
                    coords[i] += 0.015f;
                }
            }
            if (glfwGetKey(window_0.getWindow(), GLFW_KEY_S) && coords[1] > -1) {
                for (size_t i = 1; i < sizeof(coords) / sizeof(coords[0]); i += 2) {
                    coords[i] -= 0.015f;
                }
            }
            if (glfwGetKey(window_0.getWindow(), GLFW_KEY_A) && coords[0] > -1) {
                for (size_t i = 0; i < sizeof(coords) / sizeof(coords[0]); i += 2) {
                    coords[i] -= 0.015f;
                }
            }
            if (glfwGetKey(window_0.getWindow(), GLFW_KEY_D) && coords[6] < 1) {
                for (size_t i = 0; i < sizeof(coords) / sizeof(coords[0]); i += 2) {
                    coords[i] += 0.015f;
                }
            }

            glBegin(GL_QUADS);

            glColor3f(1, 0, 1);

            glVertex2fv(coords + 0);
            glVertex2fv(coords + 2);
            glVertex2fv(coords + 4);
            glVertex2fv(coords + 6);

            glEnd();


            struct {
                double x;
                double y;
            }Cursor_pos;
            glfwGetCursorPos(window_0.getWindow(), &Cursor_pos.x, &Cursor_pos.y);

            int vertex1x;
            int vertex1y;
            int vertex2x;
            int vertex2y;
            window_0.transform_output_area_coords(coords[0], coords[1], vertex1x, vertex1y);
            window_0.transform_output_area_coords(coords[4], coords[5], vertex2x, vertex2y);

            if (glfwGetMouseButton(window_0.getWindow(), GLFW_MOUSE_BUTTON_LEFT) &&
                (Cursor_pos.x > vertex1x && Cursor_pos.x < vertex2x)  &&
                (Cursor_pos.y < vertex1y && Cursor_pos.y > vertex2y) ) {                
                std::cout << "you pressed the button\n";
            }


            glPopMatrix();

            glfwSwapBuffers(window_0.getWindow());
            glfwPollEvents();
            Sleep(10);
        }
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "Exception glfw: " << e.what() << std::endl;
    }

    std::cout << "Ok\n";
    std::cin.get();
    return 0;
}

































/*
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;

int x;
int y;

int fruitX;
int fruitY; 

int score;

int tailX[100];
int tailY[100];

int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
time_t startTime;
const int timeLimitSeconds = 60; // Set the time limit to 60 seconds

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    startTime = time(NULL); // Get current time
}

void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
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
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }

    time_t currentTime = time(NULL);
    if (difftime(currentTime, startTime) >= timeLimitSeconds)
        gameOver = true;
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(50); //sleep(10) for Linux/Mac
    }
    cout << "Game over! Time's up!" << endl;
    std::cin.get();
    return 0;
}//*/