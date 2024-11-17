#include "Game.h"



void snake::Game::playbutton()
{
    float coords[] = { -0.4f, -0.2f,  -0.4f, 0.2f,  0.4f, 0.2f,  0.4f, -0.2f };

    glBegin(GL_QUADS);

    glColor3f(0, 1, 1);

    glVertex2fv(coords + 0);
    glVertex2fv(coords + 2);
    glVertex2fv(coords + 4);
    glVertex2fv(coords + 6);

    glEnd();

    if (press_button(coords[0], coords[4], coords[1], coords[5])) {
        game = true;
    }
}

bool snake::Game::press_button(float mincoordx, float maxcoordx, float mincoordy, float maxcoordy)
{
    struct {
        double x;
        double y;
    }Cursor_pos;
    glfwGetCursorPos(window_game->getWindow(), &Cursor_pos.x, &Cursor_pos.y);
    int vertex1x;
    int vertex1y;
    int vertex2x;
    int vertex2y;
    window_game->transform_output_area_coords(mincoordx, mincoordy, vertex1x, vertex1y);
    window_game->transform_output_area_coords(maxcoordx, maxcoordy, vertex2x, vertex2y);

    return glfwGetMouseButton(window_game->getWindow(), GLFW_MOUSE_BUTTON_LEFT) &&
        (Cursor_pos.x > vertex1x && Cursor_pos.x < vertex2x) &&
        (Cursor_pos.y < vertex1y && Cursor_pos.y > vertex2y);
}

void snake::Game::testsnake()
{
    


    for (size_t i = 0; i < sizeof(coords_snake) / sizeof(coords_snake[0]); i ++) {
        std::cout << coords_snake[i] << "  ";
    }
    std::cout << std::endl;


    if (glfwGetKey(window_game->getWindow(), GLFW_KEY_W) && coords_snake[3] < 1) {
        for (size_t i = 1; i < 8; i += 2) {
            coords_snake[i] += 0.02f;
        }
    }
    if (glfwGetKey(window_game->getWindow(), GLFW_KEY_S) && coords_snake[1] > -1) {
        for (size_t i = 1; i < 8; i += 2) {
            coords_snake[i] -= 0.02f;
        }
    }
    if (glfwGetKey(window_game->getWindow(), GLFW_KEY_A) && coords_snake[0] > -1) {
        for (size_t i = 0; i < 8; i += 2) {
            coords_snake[i] -= 0.02f;
        }
    }
    if (glfwGetKey(window_game->getWindow(), GLFW_KEY_D) && coords_snake[6] < 1) {
        for (size_t i = 0; i < 8; i += 2) {
            coords_snake[i] += 0.02f;
        }
    }

    glBegin(GL_QUADS);

    glColor3f(1, 0, 1);

    glVertex2fv(coords_snake + 0);
    glVertex2fv(coords_snake + 2);
    glVertex2fv(coords_snake + 4);
    glVertex2fv(coords_snake + 6);

    glEnd();
}



snake::Game::Game(window::Window* window_0)
{
    window_game = window_0;
}

void snake::Game::home_screen()
{
    playbutton();
}

void snake::Game::game_screen()
{
    testsnake();
}
