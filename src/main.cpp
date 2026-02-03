#include"main.h"


glm::vec3 trianglePosition(0.0f, -0.6f, 0.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void movement(GLFWwindow* window);



int main() {
    // Initialize and configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    GLFWwindow*window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::string vspath = readShaderFromFile("shader.vs");
    const char* vss = vspath.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vss, NULL);
    glCompileShader(vertexShader);

    std::string fspath = readShaderFromFile("shader.fs");
    const char* fss = fspath.c_str();
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fss, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    float vertices[] = {
        // Positions          // TexCoords
        -0.12f ,  0.12f, 0.0f,  0.0f, 1.0f,  // top-left
         0.12f,  0.12f, 0.0f,  1.0f, 1.0f,  // top-right
         0.12f, -0.12f, 0.0f,  1.0f, 0.0f,  // bottom-right
        -0.12f, -0.12f, 0.0f,  0.0f, 0.0f   // bottom-left
    };

    unsigned int indices[] = { 
        0, 1, 3,
        1, 2, 3 
    };

    unsigned int ebo;
 
    VertexBuffer vbSquare(sizeof(vertices), vertices);
    VertexBufferLayout layout;
    layout.push<float>(3);
    layout.push<float>(2);
    VertexArray va;
    
    va.AddBuffer(vbSquare, layout);
    VertexBufferLayout bulletLayout;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

     Texture tex("container.png");



    

    // Main game loop
    while (!glfwWindowShouldClose(window))
    {
        movement(window);
        glUseProgram(shaderProgram);
        glClear(GL_COLOR_BUFFER_BIT);
        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glm::mat4 model = glm::mat4(1.0f); // Identity matrix (no translation)
         model = glm::translate(glm::mat4(1.0f), trianglePosition);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        tex.Bind(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        va.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
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
    if (trianglePosition.x < -0.9f) trianglePosition.x = 0.9f;
    if (trianglePosition.x > 0.9f) trianglePosition.x = -0.9f;
    if (trianglePosition.y < -0.9f) trianglePosition.y = 0.9f;
    if (trianglePosition.y > 0.9f) trianglePosition.y = -0.9f;
}
