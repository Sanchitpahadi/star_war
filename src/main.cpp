
#include "main.h"
#include "Window.hpp"
#include "Renderer.h"
#include "Mesh.h"

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int main()
{
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

    Renderer render;
    render.Init();

    bool showintro = true;

  

    const float windowWidth  = 800.0f;
    const float windowHeight = 600.0f;

    const float aspectRatio = windowWidth / windowHeight;
    const float halfHeight = 10.0f;
    const float halfWidth = halfHeight * aspectRatio;

    glm::mat4 projection = glm::ortho(
        -halfWidth, halfWidth,
        -halfHeight, halfHeight,
         0.1f, 100.0f
    );

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );


    while (!window.ShouldClose())
    {
        render.SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        render.Clear();

        if (showintro)
        {
            if (window.IsKeyPressed(GLFW_KEY_SPACE))
            {
                showintro = false;
            }

            text.renderText(
                "PRESS SPACE TO START",
                200, 300,
                1.0f, 1.0f, 1.0f
            );
        }
        else
        {
            shader.use();

            const unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");

            const unsigned int  viewLoc = glGetUniformLocation(shader.ID, "view");

            const unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");

            glUniformMatrix4fv(projLoc, 1, GL_FALSE,glm::value_ptr(projection));

            glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr(view) );
 

            glm::mat4 model(1.0f);

            model = glm::translate( model, glm::vec3(0.0f, 0.0f, 0.0f) );

            model = glm::scale( model, glm::vec3(2.5f, 2.5f, 1.0f) );

            glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            tex.Bind(0);

            rectangle.Draw();
        }

        window.SwapBuffers();
        window.PollEvents();
    }

    return 0;
}
