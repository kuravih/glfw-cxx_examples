#include "glfw-cxx/Window.hpp"
#include "glfw-cxx/Time.hpp"
#include "glfw-cxx/Error.hpp"

#include <cstdlib>
#include <iostream>

static void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error" << error << ":" << description << "\n";
}

int main(int argc, char **argv)
{

    glfw::Error::SetErrorCallback(glfw_error_callback);

    glfw::Window mainWindow, subWindow;
    glfw::Event mainWindowEvent, subWindowEvent;

    mainWindow.Create(1920, 1200, "Window");

    subWindow.Create(800, 800, "Sub-Window", mainWindow);

    while ((!mainWindow.ShouldClose()) && (!subWindow.ShouldClose()))
    {
        {
            mainWindow.MakeContextCurrent();
            mainWindow.PollEvents();
            while (mainWindow.GetEvents(mainWindowEvent))
            {
                std::cout << "Got mainWindowEvent from queue\tEvent type is: " << static_cast<int>(mainWindowEvent.type) << "\n";
                switch (mainWindowEvent.type)
                {
                case glfw::Event::Type::Key:
                    if (mainWindowEvent.key.action == glfw::KeyAction::Press)
                        if (mainWindowEvent.key.key == glfw::Key::Escape)
                            mainWindow.SetShouldClose(GL_TRUE);
                }
            }
            mainWindow.SwapBuffers();
        }

        {
            subWindow.MakeContextCurrent();
            subWindow.PollEvents();
            glfw::Event subWindowEvent;
            while (subWindow.GetEvents(subWindowEvent))
            {
                std::cout << "Got subWindowEvent from queue\tEvent type is: " << static_cast<int>(subWindowEvent.type) << "\n";
                switch (subWindowEvent.type)
                {
                case glfw::Event::Type::Key:
                    if (subWindowEvent.key.action == glfw::KeyAction::Press)
                        if (subWindowEvent.key.key == glfw::Key::Escape)
                            subWindow.SetShouldClose(GL_TRUE);
                }
            }
            subWindow.SwapBuffers();
        }
    }

    return 0;
}
// ====================================================================================================================