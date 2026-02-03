#pragma once
#include <vector>
#include "h.h"
// Define the layout for each element
struct ElementLayout
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:          return  4;
        case GL_UNSIGNED_INT:   return  4;
        case GL_UNSIGNED_BYTE:  return  1;
        default:
            return 0;
        }
    }
};

// Define the class for managing the layout
class VertexBufferLayout
{
private:
    std::vector<ElementLayout> m_Element;
    unsigned int m_Stride = 0;

public:
    // Declare the template function (without specialization)
    template <typename T>
    void push(unsigned int count);

    // Getter functions for layout and stride
    inline const std::vector<ElementLayout>& GetElementLayout() const { return m_Element; }
    inline unsigned int GetStride() const { return m_Stride; }
};
