#include "VertexBuffer.h"
#include "Glad/glad.h"
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer() {}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_Renderer);
}

void VertexBuffer::Init(unsigned int size, const void* data, unsigned int usage)
{
    glGenBuffers(1, &m_Renderer);
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VertexBuffer::SetData(unsigned int size, const void* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
}

void VertexBuffer::unBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

