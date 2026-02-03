#include"VertexBufferLayout.h"


template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
    m_Element.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * sizeof(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
    m_Element.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * sizeof(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
    m_Element.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * sizeof(GL_UNSIGNED_BYTE);
}

// General template with static assertion for unsupported types
template <typename T>
void VertexBufferLayout::push(unsigned int count)
{
    static_assert(false, "Unsupported type!"); // Will trigger error for unsupported types
}

