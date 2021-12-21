#include <iostream>
#include "Krill/Subsystems/Window/GLFWWindowHandler.h"
#include "Krill/Subsystems/System.h"

class Environment : public Krill::System::System
{
public:
    Environment() : glfwHandler(*this, [](std::string in)
                                { std::cout << in << std::endl; })
    {
        InitWindow();
    }

    void InitWindow()
    {
        glfwHandler.options.WindowWidth = 640;
        glfwHandler.options.WindowHeight = 480;
        glfwHandler.options.FullscreenHeight = 1080;
        glfwHandler.options.FullscreenWidth = 1920;
        glfwHandler.options.Fullscreen = false;

        glfwHandler.InitializeGLFW();
        glfwHandler.InitializeWindow();
    }

    void Loop()
    {
        System::Loop();
        std::cout << ".";
        if (glfwGetKey(glfwHandler.GetWindow(), GLFW_KEY_F) == GLFW_PRESS)
        {
            std::cout << "[F]";
        }
    }

    void Start()
    {
        while (!glfwWindowShouldClose(glfwHandler.GetWindow()))
        {
            Loop();
        }
    }

    Krill::System::Window::GLFWWindowHandler glfwHandler;
};

int main()
{
    Environment env;
    env.Start();
}