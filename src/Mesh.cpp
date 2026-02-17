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
