#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <Glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class TextRenderer {
public:
    TextRenderer(const std::string& fontPath, float initialSize, int windowWidth, int windowHeight);
    ~TextRenderer();
    
    void renderText(const std::string& text, float x, float y, float r, float g, float b);
    void setSize(float newSize);
    float getSize() const;
    void updateProjection(int windowWidth, int windowHeight);

private:
    void initShaders();
    void initBuffers();
    void createFontAtlas(float fontSize);
    void createOrthoMatrix(float* matrix, float left, float right, float bottom, float top);
    GLuint compileShader(const char* source, GLenum shaderType);
    
    GLuint texture;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    
    unsigned char* fontBuffer;
    void* charData;
    
    float currentSize;
    int windowWidth;
    int windowHeight;
    
    static constexpr int ATLAS_WIDTH = 512;
    static constexpr int ATLAS_HEIGHT = 512;
};

#endif