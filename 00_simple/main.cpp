#include "glfw-cxx/Window.hpp"
#include "glfw-cxx/Time.hpp"
#include "glfw-cxx/Error.hpp"
#include "glfw-cxx/Context.hpp"

#include <cstdlib>
#include <iostream>
#include <unistd.h>

const unsigned int width = 800;
const unsigned int height = 800;

// ====================================================================================================================
static void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error" << error << ":" << description << "\n";
}
// ====================================================================================================================


int main()
{
    glfw::Error::SetErrorCallback(glfw_error_callback);

    glfw::Window::Hint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfw::Window::Hint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfw::Window::Hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only

    glfw::Window window(width, height, "00 Simple Example");
    if (window == nullptr)
        return 1;

    window.MakeContextCurrent();

    glfw::Context::SwapInterval(1);

    while (!window.ShouldClose())
    {

        // Poll and handle events (inputs, window resize, etc.)
        window.PollEvents();
        if (window.GetAttrib(GLFW_ICONIFIED) != 0)
        {
            usleep(10*1000);
            continue;
        }

        glfw::Event event;
        while (window.GetEvents(event))
        {
            std::cout << "Got event from queue\tEvent type is: " << static_cast<int>(event.type) << "\n";
            switch (event.type)
            {
            case glfw::Event::Type::Key:
                if (event.key.action == glfw::KeyAction::Press)
                    if (event.key.key == glfw::Key::Escape)
                        window.SetShouldClose(true);
                break;
            default:
                break;
            }
        }

        // Swap the back buffer with the front buffer
        window.SwapBuffers();
    }

    return 0;
}
