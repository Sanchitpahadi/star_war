#include"VertexBuffer.h"
#include"Glad/glad.h"
#include<GLFW/glfw3.h>

VertexBuffer::VertexBuffer()
{

}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Renderer);
}

void VertexBuffer::Init(float size,const void* data)
{
	glGenBuffers(1, &m_Renderer);
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void VertexBuffer::Bind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer);

}
void VertexBuffer::unBind()const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}