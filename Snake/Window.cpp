#include "window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdexcept>
#include <string>

using namespace window;

Window::Window(int width, int height, const char* title, const char* iconPath)
    : m_Width(width), m_Height(height), m_Title(title) {
    initGLFW();
    m_Monitor = glfwGetPrimaryMonitor();
    createWindow();
    setIcon(iconPath);
    glfwSetKeyCallback(m_Window, static_KeyCallback);
}

Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void window::Window::transform_output_area_coords(float coordx, float coordy, int& xwindow, int& ywindow)
{
    xwindow = (coordx + 1.0) * (m_Width / 2) + Viewport.x;
    ywindow = ((m_Height / 2) * (-1) * coordy + (m_Height / 2)) + Viewport.y;
}

void window::Window::window_resize()
{
    if (m_Height != m_Width) {
        throw std::runtime_error("Height window != Width window");
    }

    glfwGetWindowSize(m_Window, &m_resize_Width, &m_resize_Height);
    if (m_Height != m_resize_Height || m_Width != m_resize_Width)
    {
        if (m_resize_Width > m_resize_Height) {
            m_Height = m_resize_Height;
            m_Width = m_resize_Height;
            Viewport.x = (m_resize_Width - m_resize_Height) / 2;
            Viewport.y = 0;
        }
        else if (m_resize_Height > m_resize_Width) {
            m_Height = m_resize_Width;
            m_Width = m_resize_Width;
            Viewport.x = 0;
            Viewport.y = (m_resize_Height - m_resize_Width) / 2;
        }
        glViewport(Viewport.x, Viewport.y, m_Width, m_Height);
    }
    
}

GLFWwindow* Window::getWindow() {
    return m_Window;
}

void Window::initGLFW() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }
}

void Window::createWindow() {
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);
    if (!m_Window) {
        throw std::runtime_error("Could not create GLFW window!");
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, this);
}

void window::Window::setIcon(const char* path) {
    m_Icon[0].pixels = stbi_load(path, &m_Icon[0].width, &m_Icon[0].height, 0, 4);
    if (m_Icon[0].pixels) {
        glfwSetWindowIcon(m_Window, 1, m_Icon);
    }
}


void Window::setFullscreen() {
    if (!m_Fullscreen) {
        const GLFWvidmode* vidMode = glfwGetVideoMode(m_Monitor);
        glfwGetWindowPos(m_Window, &m_Pos.x, &m_Pos.y);
        glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
        m_Fullscreen = !m_Fullscreen;   
    }
    else { 
        glfwSetWindowMonitor(m_Window, nullptr, m_Pos.x, m_Pos.y, m_Width, m_Height, 0);
        m_Fullscreen = !m_Fullscreen;
    }
}


void Window::static_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Window* actualWindow = (Window*)glfwGetWindowUserPointer(window);
    actualWindow->keyCallback(key, scancode, action, mods);
}

void Window::keyCallback(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_Window, true);
    }        
    if (key == GLFW_KEY_F11 && action == GLFW_RELEASE) {
        setFullscreen();
    }   
}
