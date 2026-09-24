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

    void InitInstancing(const void* instanceData, unsigned int dataSize, const VertexBufferLayout& instanceLayout, unsigned int baseAttribLocation, unsigned int divisor = 1);
    void UpdateInstanceData(const void* data, unsigned int size);
    void DrawInstanced(unsigned int instanceCount) const;

private:

    unsigned int ebo;
    VertexArray vao;
    VertexBuffer instanceVBO;
    VertexBuffer vbo;
    VertexBufferLayout layout;

    unsigned int indexCount;
};
