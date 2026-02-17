#pragma once
#include <Glad/glad.h>

class Renderer
{
public:

    Renderer();
    
    void Init();
    void SetClearColor(float r, float g, float b, float a);
    void Clear() const;

    void SetViewport(int width, int height) const;

    void DrawArrays(unsigned int vao, int count) const;
    void DrawIndexed(unsigned int indexCount) const;
};
