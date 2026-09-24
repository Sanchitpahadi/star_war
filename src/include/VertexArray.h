#pragma once
#include"VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <iostream>
class VertexBuffer;
class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout); // Updated to accept VertexBufferLayout
    void AddInstancedBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int baseAttribLocation, unsigned int divisor = 1);

    void Bind() const;
    void Unbind() const;
};
