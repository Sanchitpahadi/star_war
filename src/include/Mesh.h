#pragma once

#include <vector>
#include <Glad/glad.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices);

    ~Mesh();

    void Bind() const;
    void Unbind() const;

    void Draw() const;

private:

    unsigned int ebo;
    VertexArray vao;
    VertexBuffer vbo;
    VertexBufferLayout layout;

    unsigned int indexCount;
};
