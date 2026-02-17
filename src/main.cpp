#include"main.h"
#include"Window.hpp"
#include"Renderer.h"
#include"Mesh.h"

glm::vec3 trianglePosition(0.0f, -0.6f, 0.0f);

int main() {
    Window window(800, 600, "Engine");
    
    Shader shader("shader.vs", "shader.fs");

    std::vector<float> rectVertices = 
        {
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f
        };

    std::vector<unsigned int> rectIndices = 
        {
            0, 1, 2,
            2, 3, 0
        };

    Mesh rectangle(rectVertices, rectIndices);

    TextRenderer text("roman.ttf", 45.0f, 800, 600);

    Texture tex("texture/Blue.png");
    Texture bull("texture/bullet.png");

    Renderer render;

    render.Init();

    bool showintro = true;

    
    while (!window.ShouldClose()) {
       
        render.SetClearColor(0.2f,0.3f,0.3f,1.0f);
        render.Clear();

        if(showintro)
        {
            
             if (window.IsKeyPressed(GLFW_KEY_SPACE))
                {
                    showintro = false;
            
                }

            text.renderText("PRESS SPACE TO START", 200, 300, 1.0f, 1.0f, 1.0f);

        }
        else
        {
            shader.use();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), trianglePosition);
            int modelLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            tex.Bind(0);
            rectangle.Draw();
        }
        window.SwapBuffers();
        window.PollEvents();  
      }

    return 0;
}
