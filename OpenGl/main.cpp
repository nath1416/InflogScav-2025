#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <iostream>

#include "src/input.h"
#include "src/data.h"

float vertices[] = {
    // Positions          // Normals           // Texture Coords (not used here)
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // Back face
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // Front face
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Left face
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // Right face
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // Bottom face
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f, // Top face
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};


std::string loadShaderSource(const char* filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

unsigned int compileShader(GLenum type, const char* path) {
    std::string src = loadShaderSource(path);
    const char* source = src.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, NULL, info);
        std::cerr << "Error compiling shader (" << path << "): " << info << std::endl;
    }
    return shader;
}

int main()
{
    Input input;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Cube", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }


    glfwSetWindowUserPointer(window, &input);

    glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int sc, int action, int mods) {
        Input* in = (Input*)glfwGetWindowUserPointer(win);
        in->keyCallback(key, action);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
        Input* in = (Input*)glfwGetWindowUserPointer(win);
        in->mouseMoveCallback(x, y);
    });

    glfwSetScrollCallback(window, [](GLFWwindow* win, double xoff, double yoff) {
        Input* in = (Input*)glfwGetWindowUserPointer(win);
        in->scrollCallback(yoff);
    });

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/phong.vs.glsl");
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/phong.fs.glsl");


    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glEnable(GL_DEPTH_TEST);
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);

    const int nbLights= 5;

    // glm::vec3 lightPos = glm::vec3(1.2f, 0.0f, 2.0f);
    
    bool run = true;
    float angle = 45;
    bool color = false;
    bool pulse = false;
    float pulseTime = 0;
    while (!glfwWindowShouldClose(window) && run)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        glfwPollEvents();
        
    
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glUseProgram(shaderProgram);
    
    float speed = 2.5f;
    if (input.getKeyHold(Input::W)) cameraPos.z += speed * deltaTime;
    if (input.getKeyHold(Input::S)) cameraPos.z -= speed * deltaTime;
    if (input.getKeyHold(Input::A)) cameraPos.x += speed * deltaTime;
    if (input.getKeyHold(Input::D)) cameraPos.x -= speed * deltaTime;
    if (input.getKeyHold(Input::SPACE)) cameraPos.y -= speed * deltaTime;
    if (input.getKeyHold(Input::SHIFT)) cameraPos.y += speed * deltaTime;
    if (input.getKeyPress(Input::T)) pulse  = !pulse;
    if (input.getKeyHold(Input::R)){
        angle += speed*deltaTime;
    }

    if (input.getKeyHold(Input::Q)) run = false;
    if (input.getKeyHold(Input::ESC)) run = false;
    if (input.getKeyPress(Input::E)) color = !color;

    // int x,y;
    // input.getMousePos(x, y);
    //     lightPos.y = -y/100;
    //     lightPos.x = -x/100 + 2;
    //     std::cout << lightPos.x << std::endl;
    
        
        glm::mat4 model = glm::mat4(1.0f);
        
        glm::vec3 objectPos = glm::vec3(0.0f);
        model = glm::translate(model, objectPos);

        model = glm::translate(model, objectPos);
        model = glm::rotate(
            model,
            angle,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 view = glm::translate(
            glm::mat4(1.0f),
            cameraPos
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );


        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);



        unsigned int lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
        unsigned int viewPosLoc = glGetUniformLocation(shaderProgram, "viewPos");
        unsigned int firstColorLoc = glGetUniformLocation(shaderProgram, "firstColor");
        unsigned int secondColorLoc = glGetUniformLocation(shaderProgram, "secondColor");
        unsigned int timeLoc = glGetUniformLocation(shaderProgram, "time");

        float time =  glfwGetTime() / 5;

        glm::vec3 firstColor(0.8);
        glm::vec3 secondColor(0.2);
        if(color){
            float ra = 0.5f + 0.5f * sin(time * 0.6f); 
            float ga = 0.5f + 0.5f * sin(time * 0.8f + 2.0f); 
            float ba = 0.5f + 0.5f * sin(time * 1.0f + 4.0f);

            float rb = 0.5f + 0.5f * sin((time+50) * 0.6f ); 
            float gb = 0.5f + 0.5f * sin((time+50) * 0.8f + 2.0f); 
            float bb = 0.5f + 0.5f * sin((time+50)* 1.0f + 4.0f);

            firstColor.x = ra;
            firstColor.y = ga;
            firstColor.z = ba;

            secondColor.x = ra;
            secondColor.y = ga;
            secondColor.z = ba;
        }
        glUniform3f(firstColorLoc, firstColor.x, firstColor.y, firstColor.z);
        glUniform3f(secondColorLoc, secondColor.x, secondColor.y, secondColor.z);
        if(pulse){
            pulseTime += deltaTime;
            glUniform1f(timeLoc, pulseTime);
        }


        glm::vec3 lightPos = glm::vec3(2.0f * sin(time), 1.5f, 2.0f * cos(time));

        glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z); 

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glBindVertexArray(VAO);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    std::cout << "Goodbye !" << std::endl;
    glfwTerminate();
    return 0;
}

