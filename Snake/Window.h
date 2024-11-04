#pragma once

#include <GLFW/glfw3.h>

namespace window
{

class Window {
    GLFWwindow* m_Window;
    GLFWmonitor* m_Monitor;

    const char* m_Title;
    GLFWimage m_Icon[1];
    struct {
        int x;
        int y;
    }m_Pos;
   
    struct {
        int x;
        int y;
    }Viewport;

    bool m_Fullscreen = false;

    int m_Width;
    int m_Height;
    int m_resize_Width;
    int m_resize_Height;

public:
    Window(int width, int height, const char* title, const char* iconPath);
    ~Window();

    void transform_output_area_coords(float coordy, float coordx,int &xwindow, int &ywindow);

    void window_resize();

    GLFWwindow* getWindow();

private:
    
    void initGLFW();
    void createWindow();

    void setIcon(const char* path);

    void setFullscreen();


    static void static_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void keyCallback(int key, int scancode, int action, int mods);
};

} //namespace window

