#include"main.h"
#include"Window.hpp"
#include"Renderer.h"
#include"Mesh.h"

const unsigned int INSTANCE_COUNT = 1040;

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

    std::vector<glm::mat4> instanceMatrices(INSTANCE_COUNT);
    for (unsigned int i = 0; i < INSTANCE_COUNT; i++)
    {
        glm::mat4 model(1.0f);
        float x = (i % 32) * 1.2f - 18.0f;
        float y = (i / 32) * 1.2f - 18.0f;
        instanceMatrices[i] = glm::translate(model, glm::vec3(x, y, 0.0f));
    }

    VertexBufferLayout instanceLayout;
    instanceLayout.push<float>(4); // column 0
    instanceLayout.push<float>(4); // column 1
    instanceLayout.push<float>(4); // column 2
    instanceLayout.push<float>(4); // column 3

    rectangle.InitInstancing(instanceMatrices.data(),
        sizeof(glm::mat4) * INSTANCE_COUNT, instanceLayout, 2, 1);

    TextRenderer text("roman.ttf", 45.0f, 800, 600);

    Texture tex("texture/Blue.png");

    Renderer render;
    render.Init();

    bool showintro = true;

    glm::mat4 projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, -1.0f, 1.0f);
    // glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    while (!window.ShouldClose()) {

        render.SetClearColor(0.2f,0.3f,0.3f,1.0f);
        render.Clear();

        if(showintro)
        {
            if (window.IsKeyPressed(GLFW_KEY_SPACE))
                showintro = false;

            text.renderText("PRESS SPACE TO START", 200, 300, 1.0f, 1.0f, 1.0f);
        }
     else
    {
        shader.use();

        int projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        tex.Bind(0);
        rectangle.DrawInstanced(INSTANCE_COUNT);
    }
        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}