#pragma once
#include "VertexBufferLayout.h"
class VertexBuffer
{
private:
    unsigned int m_Renderer;
public:
    VertexBuffer();
    ~VertexBuffer();

    void Init(unsigned int size, const void* data, unsigned int usage = GL_STATIC_DRAW);
    void SetData(unsigned int size, const void* data); // glBufferSubData, for per-frame instance updates
    void Bind() const;
    void unBind() const;
};