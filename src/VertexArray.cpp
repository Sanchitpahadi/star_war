#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
    Bind();
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    vb.Bind();
    const auto& elements = layout.GetElementLayout();
    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        std::cout << "Element type: " << element.type
            << " count: " << element.count
            << " normalized: " << (int)element.normalized << std::endl;
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)(uintptr_t)offset);
        offset += element.count * ElementLayout::getSizeOfType(element.type);

    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
