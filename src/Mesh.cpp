#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices,
           const std::vector<unsigned int>& indices)
{
    indexCount = indices.size();

    vao.Bind();

    vbo.Init(vertices.size() * sizeof(float), vertices.data());

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),indices.data(), GL_STATIC_DRAW);

    
    layout.push<float>(3);
    layout.push<float>(2);
    
    vao.AddBuffer(vbo, layout);

    Unbind();    
}
void Mesh::InitInstancing(const void* instanceData, unsigned int dataSize,
    const VertexBufferLayout& instanceLayout, unsigned int baseAttribLocation, unsigned int divisor)
{
    instanceVBO.Init(dataSize, instanceData, GL_DYNAMIC_DRAW);
    vao.AddInstancedBuffer(instanceVBO, instanceLayout, baseAttribLocation, divisor);
}

void Mesh::UpdateInstanceData(const void* data, unsigned int size)
{
    instanceVBO.SetData(size, data);
}

void Mesh::DrawInstanced(unsigned int instanceCount) const
{
    vao.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0, instanceCount);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &ebo);
}

void Mesh::Bind() const
{
    vao.Bind();
}

void Mesh::Unbind() const
{
    vao.Unbind();
}

void Mesh::Draw() const
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
