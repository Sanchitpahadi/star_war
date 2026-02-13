#include"main.h"

glm::vec3 trianglePosition(0.0f, -0.6f, 0.0f);
glm::vec3 bulletPosition(0.0f, 0.0f, 0.0f);
bool bulletActive = false;
float bulletSpeed = 0.02f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void movement(GLFWwindow* window);
void updateBullet();

int main() {
    // Initialize and configure GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    


    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Shader shader("shader.vs", "shader.fs");
    std::cout << "Shader created successfully" << std::endl;
    
    float vertices[] = {
        // Positions          // TexCoords
        -0.12f,  0.12f, 0.0f,  0.0f, 1.0f,  // top-left
         0.12f,  0.12f, 0.0f,  1.0f, 1.0f,  // top-right
         0.12f, -0.12f, 0.0f,  1.0f, 0.0f,  // bottom-right
        -0.12f, -0.12f, 0.0f,  0.0f, 0.0f   // bottom-left
    };

    unsigned int indices[] = { 
        0, 1, 3,
        1, 2, 3 
    };

    TextRenderer text("roman.ttf", 45.0f, 800, 600);


    // Create EBO first
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    std::cout << "EBO created" << std::endl;

    // Create vertex buffers and arrays
    VertexBuffer vbSquare(sizeof(vertices), vertices);
    std::cout << "VertexBuffer vbSquare created" << std::endl;
    
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    std::cout << "Layout configured" << std::endl;
    
    VertexArray va;
    va.AddBuffer(vbSquare, layout);
    std::cout << "VertexArray va created" << std::endl;
    
    VertexBuffer bulletVB(sizeof(vertices), vertices);
    std::cout << "VertexBuffer bulletVB created" << std::endl;
    
    VertexArray bulletVA;
    VertexBufferLayout bulletLayout;
    bulletLayout.push<float>(3);
    bulletLayout.push<float>(2);
    bulletVA.AddBuffer(bulletVB, bulletLayout);
    std::cout << "VertexArray bulletVA created" << std::endl;

    // Load textures
    Texture tex("texture/Blue.png");
    std::cout << "Texture tex loaded" << std::endl;
    
    Texture bull("texture/bullet.png");
    std::cout << "Texture bull loaded" << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    bool showintro = true;

    printf("the first one is done");
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        movement(window);
        updateBullet();
        glfwPollEvents();

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(showintro)
        {
            

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                        showintro = false;
            }

            text.renderText("PRESS SPACE TO START", 200, 300, 1.0f, 1.0f, 1.0f);

        }
        else
        {

            shader.use();
            // Draw player
            glm::mat4 model = glm::translate(glm::mat4(1.0f), trianglePosition);
            int modelLoc = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            
            tex.Bind(0);
            va.Bind();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // Draw bullet if active
            if (bulletActive) {
                glm::mat4 bulletModel = glm::translate(glm::mat4(1.0f), bulletPosition);
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bulletModel));

                bull.Bind(0);
                bulletVA.Bind();
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void movement(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        trianglePosition.x -= 0.007f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        trianglePosition.x += 0.007f;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        trianglePosition.y += 0.007f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        trianglePosition.y -= 0.007f;
    }
    
    // Wrap around screen edges
    if (trianglePosition.x < -0.9f) trianglePosition.x = 0.9f;
    if (trianglePosition.x > 0.9f) trianglePosition.x = -0.9f;
    if (trianglePosition.y < -0.9f) trianglePosition.y = 0.9f;
    if (trianglePosition.y > 0.9f) trianglePosition.y = -0.9f;

    // Fire bullet (single press detection)
    static bool spaceWasPressed = false;
    bool spaceIsPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    
    if (spaceIsPressed && !spaceWasPressed && !bulletActive) {
        bulletActive = true;
        bulletPosition = trianglePosition;
    }
    spaceWasPressed = spaceIsPressed;
}

void updateBullet() {
    if (bulletActive) {
        bulletPosition.y += bulletSpeed;
        
        if (bulletPosition.y > 1.0f) {
            bulletActive = false;
        }
    }
}