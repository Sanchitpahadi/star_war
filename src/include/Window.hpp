#pragma once
#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
    GLFWwindow* m_Window;
    int m_Width;
    int m_Height;
    std::string m_Title;

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    Window(int width, int height, const std::string& title);
    ~Window();

    void PollEvents();
    void SwapBuffers();

    bool ShouldClose() const;
    bool IsKeyPressed(int key) const;

    GLFWwindow* GetNativeWindow() const;
};
