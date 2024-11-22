
/* Убрать freetype_x64-windows/ из .gitignore */

#include <iostream>
#include <windows.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Window.h"
#include "Game.h"

int main()
{
    FT_Library  library;
    if (FT_Init_FreeType(&library)) {

    }
    try
    {
        window::Window window_0(512, 512, "Snake", "bless-48x48.png");
        snake::Game gamesnake(&window_0);

        while (!glfwWindowShouldClose(window_0.getWindow()))
        {
            window_0.window_resize();
            glClearColor(0.0f, 0.8f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            if (!gamesnake.game) {
                gamesnake.home_screen();
            }
            else if (gamesnake.game) {
                gamesnake.game_screen();
            }
                        
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
