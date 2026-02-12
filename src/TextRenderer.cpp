#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#include "TextRenderer.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

// Vertex shader source
static const char* vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec2 texCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 projection;\n"
    "void main() {\n"
    "    gl_Position = projection * vec4(position, 0.0, 1.0);\n"
    "    TexCoord = texCoord;\n"
    "}\n";

// Fragment shader source
static const char* fragmentShaderSource = 
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D text;\n"
    "uniform vec3 textColor;\n"
    "void main() {\n"
    "    float alpha = texture(text, TexCoord).r;\n"
    "    FragColor = vec4(textColor, alpha);\n"
    "}\n";

TextRenderer::TextRenderer(const std::string& fontPath, float initialSize, int windowWidth, int windowHeight)
    : texture(0), shaderProgram(0), VAO(0), VBO(0), fontBuffer(nullptr), 
      currentSize(0.0f), windowWidth(windowWidth), windowHeight(windowHeight) {
    
    // Allocate character data
    charData = malloc(sizeof(stbtt_bakedchar) * 96);
    
    // Load font file
    std::ifstream file(fontPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open font file: " << fontPath << std::endl;
        throw std::runtime_error("Failed to open font file");
    }
    
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    
    fontBuffer = new unsigned char[size];
    if (!file.read(reinterpret_cast<char*>(fontBuffer), size)) {
        delete[] fontBuffer;
        throw std::runtime_error("Failed to read font file");
    }
    
    file.close();
    
    // Initialize OpenGL resources
    initShaders();
    initBuffers();
    
    // Set up projection matrix
    float projMatrix[16];
    createOrthoMatrix(projMatrix, 0.0f, static_cast<float>(windowWidth), 
                     static_cast<float>(windowHeight), 0.0f);
    
    glUseProgram(shaderProgram);
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMatrix);
    
    // Create initial font atlas
    createFontAtlas(initialSize);
    
    std::cout << "TextRenderer created successfully!" << std::endl;
    std::cout << "  Font: " << fontPath << std::endl;
    std::cout << "  Size: " << initialSize << " px" << std::endl;
}

TextRenderer::~TextRenderer() {
    if (texture) {
        glDeleteTextures(1, &texture);
    }
    
    if (VAO) {
        glDeleteVertexArrays(1, &VAO);
    }
    
    if (VBO) {
        glDeleteBuffers(1, &VBO);
    }
    
    if (shaderProgram) {
        glDeleteProgram(shaderProgram);
    }
    
    if (fontBuffer) {
        delete[] fontBuffer;
    }
    
    if (charData) {
        free(charData);
    }
    
    std::cout << "TextRenderer destroyed" << std::endl;
}

void TextRenderer::renderText(const std::string& text, float x, float y, float r, float g, float b) {
    glUseProgram(shaderProgram);
    
    // Set text color
    GLint colorLoc = glGetUniformLocation(shaderProgram, "textColor");
    glUniform3f(colorLoc, r, g, b);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    
    float currentX = x;
    float currentY = y;
    
    stbtt_bakedchar* cdata = static_cast<stbtt_bakedchar*>(charData);
    
    for (char c : text) {
        if (c >= 32 && c < 128) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, ATLAS_WIDTH, ATLAS_HEIGHT, 
                              c - 32, &currentX, &currentY, &q, 1);
            
            float vertices[6][4] = {
                { q.x0, q.y0, q.s0, q.t0 },
                { q.x1, q.y0, q.s1, q.t0 },
                { q.x1, q.y1, q.s1, q.t1 },
                
                { q.x0, q.y0, q.s0, q.t0 },
                { q.x1, q.y1, q.s1, q.t1 },
                { q.x0, q.y1, q.s0, q.t1 }
            };
            
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::setSize(float newSize) {
    createFontAtlas(newSize);
    std::cout << "Font size changed to " << newSize << " px" << std::endl;
}

float TextRenderer::getSize() const {
    return currentSize;
}

void TextRenderer::updateProjection(int windowWidth, int windowHeight) {
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    
    float projMatrix[16];
    createOrthoMatrix(projMatrix, 0.0f, static_cast<float>(windowWidth), 
                     static_cast<float>(windowHeight), 0.0f);
    
    glUseProgram(shaderProgram);
    GLint projLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projMatrix);
}

void TextRenderer::initShaders() {
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader linking failed:\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void TextRenderer::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::createFontAtlas(float fontSize) {
    unsigned char* bitmap = new unsigned char[ATLAS_WIDTH * ATLAS_HEIGHT];
    
    stbtt_bakedchar* cdata = static_cast<stbtt_bakedchar*>(charData);
    stbtt_BakeFontBitmap(fontBuffer, 0, fontSize, bitmap, ATLAS_WIDTH, ATLAS_HEIGHT, 32, 96, cdata);
    
    if (texture == 0) {
        glGenTextures(1, &texture);
    }
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, ATLAS_WIDTH, ATLAS_HEIGHT, 
                 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    currentSize = fontSize;
    delete[] bitmap;
}

void TextRenderer::createOrthoMatrix(float* matrix, float left, float right, float bottom, float top) {
    for (int i = 0; i < 16; i++) matrix[i] = 0.0f;
    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -1.0f;
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[15] = 1.0f;
}

GLuint TextRenderer::compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
    }
    
    return shader;
}
