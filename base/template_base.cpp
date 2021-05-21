//********************************************
//            MY template
//    Sanchez yucra yhon yerson
//**********************************************

#include <glad/glad.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>

using namespace std;
using namespace glm;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
	    "layout (location = 0) in vec3 aPos;\n"
	    "void main()\n"
	    "{\n"
	    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	    "out vec4 FragColor;\n"
	    "uniform vec4 ourColor;\n"
	    "void main()\n"
	    "{\n"
	    "   FragColor = ourColor;\n"
	    "}\n\0";

float array[] = {
    0.0f, 0.5f, 0.0f,  //A
    -0.2f, 0.0f, 0.0f, //B
    0.2f, 0.0f, 0.0f,  //C
    -0.2f, 0.4f, 0.0f, //D
    0.2f, 0.4f, 0.0f,  //E
    0.0f, 0.16f, 0.0f  //F

};

unsigned int Indicearray[] = {
    0, 1, 5,
    0, 5, 2,
    3, 4, 5
};


float vertices[] = {
    -0.25f, -0.25f, 0.0f,   
    0.25f, -0.25f, 0.0f, 
    0.0f,  0.25f, 0.0f    
}; 



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //*****************BUFFERS********************************
    unsigned int VBO[11], VAO[11], EBO, TRI, FG3, FG4, FG5, FG6, FG7, FG8, FG9, FG10;
    glGenVertexArrays(11, VAO);
    glGenBuffers(11, VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &TRI);
    glGenBuffers(1, &FG3);
    glGenBuffers(1, &FG4);
    glGenBuffers(1, &FG5);
    glGenBuffers(1, &FG6);	
    glGenBuffers(1, &FG7);	
    glGenBuffers(1, &FG8);	
    glGenBuffers(1, &FG9);	
    glGenBuffers(1, &FG10);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
//**********************Link VAO[0] with index***************	
        glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);
	//********indcies para la figura en VAO[0]******
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicearray), Indicearray, GL_STATIC_DRAW);
	//*********pointer para la figura VAO[0]************
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

//**********************Link VAO[1] no Indix ***********
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

//**********************Setting Color**************************
        glUseProgram(shaderProgram);
	glPointSize(10);
	glLineWidth(5.0f);
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

// ***********************Draw VAO[0] with index
	glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAO[0]);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

//**********************Draw VAO[1]******************************
        glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 0.0f);
	glBindVertexArray(VAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
