#include "glfw-cxx/Window.hpp"
#include "glfw-cxx/Time.hpp"
#include "glfw-cxx/Error.hpp"

#include <cstdlib>
#include <iostream>
#include <algorithm>

static void glfw_error_callback(int error, const char *description)
{
    std::cerr << "GLFW Error" << error << ":" << description << "\n";
}

int main()
{

    glfw::Error::SetErrorCallback(glfw_error_callback);

    glfw::Window window;

    std::list<glfw::Monitor> monitors = glfw::Monitor::GetMonitors();

    std::list<glfw::Monitor>::iterator it = std::find_if(monitors.begin(), monitors.end(), [](const glfw::Monitor &_monitor)
                                                         { return _monitor.GetVideoMode().GetWidth() == 540 && _monitor.GetVideoMode().GetHeight() == 2560; });

    if (it != monitors.end())
    {
        glfw::Monitor &monitor = *it;
        std::cout << "SLM monitor found : {width : " << monitor.GetVideoMode().GetWidth() << ", height : " << monitor.GetVideoMode().GetHeight() << "}" << "\n";
        window.Create(monitor.GetVideoMode().GetWidth(), monitor.GetVideoMode().GetHeight(), "SLM", monitor);
        window.SetAttrib(GLFW_DECORATED, false);
    }

    glfw::Event windowEvent;

    while ((!window.ShouldClose()))
    {
        window.MakeContextCurrent();
        window.PollEvents();
        while (window.GetEvents(windowEvent))
        {
            std::cout << "Got event from queue\tEvent type is: " << static_cast<int>(windowEvent.type) << "\n";
            switch (windowEvent.type)
            {
            case glfw::Event::Type::Key:
                if (windowEvent.key.action == glfw::KeyAction::Press)
                    if (windowEvent.key.key == glfw::Key::Escape)
                        window.SetShouldClose(true);
                break;
            default:
                break;
            }
        }
        window.SwapBuffers();
    }

    return 0;
}
// ====================================================================================================================