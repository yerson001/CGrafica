#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "shaders_s.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//CALLBACK MANAGE
int op = 0;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1)
    {
      
        op = 1;
    }
    else if (key == GLFW_KEY_2)
    {

        op = 2;
    }
    else if (key == GLFW_KEY_3)
    {

        op = 3;
    }
    else if (key == GLFW_KEY_4)
    {

        op = 4;
    }
    else
    {
        op = 0;
    }
}

//SHADERS:


//#1

static const char* v1 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
layout (location = 0) in vec3 aPos;      \n\
uniform mat4 transform; \n\
                                         \n\
void main()                              \n\
{                                        \n\
    gl_Position = transform * vec4(aPos, 1.0);       \n\
}";

//#2

static const char* f1 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
out vec4 FragColor;                      \n\
                                         \n\
void main()                              \n\
{                                        \n\
    FragColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);      \n\
}";


static const char* v2 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
layout (location = 0) in vec3 aPos;      \n\
                                         \n\
void main()                              \n\
{                                        \n\
    gl_Position = vec4(aPos, 1.0);        \n\
}";

//#2

static const char* f2 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
out vec4 FragColor;                      \n\
                                         \n\
void main()                              \n\
{                                        \n\
    FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);      \n\
}";

//#3

static const char* v3 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
layout (location = 0) in vec3 aPos;      \n\
                                         \n\
void main()                              \n\
{                                        \n\
    gl_Position = vec4(aPos, 1.0);        \n\
}";

//#2

static const char* f3 = "           \n\
                                         \n\
#version 330                             \n\
                                         \n\
out vec4 FragColor;                      \n\
                                         \n\
void main()                              \n\
{                                        \n\
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);      \n\
}";


void printmatrix(float mat[9])
{
    int cont = 1;
    for (int i = 0; i < 9; i++, cont++)
    {
        cout << mat[i] << " ";
        if (cont == 3)
        {
           
            cout << '\n';
            cont = 0;
        }
    }
    cout << "---------------------------------" << '\n';
    cout << '\n';
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Control Practico", NULL, NULL);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
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


    Shader ourShader(v1, f1); // you can name your shader files however you like
    Shader ourShader2(v2, f2);
    Shader ourShader3(v3, f3);

    //(0.25, -0.5, 0.0)	(-0.25, 0.5, 0.0)	(-0.75, -0.5, 0.0)

    float vertices[] = {
       0.25f, -0.5f, 0.0f, // left  
        -0.25f, 0.5f, 0.0f, // right 
        -0.75f,  -0.5f, 0.0f,

         0.25f, -0.5f, 0.0f, // left  
        -0.25f, 0.5f, 0.0f, // right 
        -0.75f,  -0.5f, 0.0f,

         0.25f, -0.5f, 0.0f, // left  
        -0.25f, 0.5f, 0.0f, // right 
        -0.75f,  -0.5f, 0.0f
    };


    //unsigned int VBO, VAO, EBO;
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    cout << "RODRIGO ANDRE CAYRO CUADROS " << '\n';
    cout << "INSTRUCCIONES: " << '\n';
    cout << "PARA VER EL TRIANGULO ORIGINAL CUALQUIER NUMERO DISINTO DE 1 A 4" << '\n';
    cout << "TRANFORMACION POR ROTACION EN EL EJE X CON LA TECLA: 1" << '\n';
    cout << "TRANFORMACION POR ROTACION EN EL EJE X MAS MATRIZ DE ESCALA CON LA TECLA: 2" << '\n';
    cout << "TRANFORMACION POR ROTACION EN EL EJE X MAS MATRIZ DE ESCALA MAS LA MATRIZ DE TRASLACION CON LA TECLA: 3" << '\n';
    cout << "TRANFORMACION POR ROTACION EN EL EJE X MAS MATRIZ DE ESCALA MAS LA MATRIZ DE TRASLACION MAS LA MATRIZ INVERSA DE ROTACION EN EL EJE X CON LA TECLA: 4" << '\n';
    cout << "TRANSFORMACION SIGUE EL ORDEN DE DERECHA A IZQUIERDA:  M = (A * (B * (C * D)))" << '\n';
    cout << "PARA REALIZAR LAS OPERACIONES NOS BASAREMOS EN LAS SIGUIENTES MATRICES Y EN LA SIGUIENTES TRANSFORMACIONES, SI HABLAMOS EN EL ESPACIO 3D: " << '\n';
    cout << "RX -------->" << '\n';

    
    bool  once[4];
    once[0] = true;
    once[1] = true;
    once[2] = true;
    once[3] = true;
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //ROTACION EN EL EJE X
        glm::mat4 transform = glm::mat4(1.0f);

        //MATRIX ROTACION EN X
        glm::mat4 transformRx = glm::mat4(1.0f); 
        //MATRIX ESACALADO
        glm::mat4 transformS = glm::mat4(1.0f);
        //MATRIX TRASLADO
        glm::mat4 transformT = glm::mat4(1.0f);
        //MATRIX ROTACION EN X CON INVERSA
        glm::mat4 transformRx1 = glm::mat4(1.0f);


        transformS = glm::scale(transformS, glm::vec3(1.25, 1.25, 1));
        transformT = glm::translate(transformT, glm::vec3(0.5f, 0.0f, 0.0f));
        transformRx = glm::rotate(transformRx, glm::radians(65.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        transformRx1 = glm::inverse(transformRx);

        glBindVertexArray(VAO);

        if (op == 1)
        {
            //SI QUEREMOS VER LOS VALORES DE LA MATRIZ QUE NOS DA OPENGL PODEMOS DESCOMENTAR LA LINEA SIGUIENTE
           
            //cout << glm::to_string(transform) << '\n';
            //AQUI REALIZAMOS LA MUTIPLICACION DE MATRICES PARA OBETENER LAS TRANSFORMACIONES
            transform = transformRx;
            if (once[0])
            {
                cout << "MATRIZ CON LA TRANSFORMACION Rx" << '\n';
                cout << glm::to_string(transform) << '\n';
                cout << '\n';
                cout << '\n';
                once[0] = false;
            }


            //ourShader.use();
            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //glDrawArrays(GL_TRIANGLES, 0, 3);

                ourShader.use();
                glDrawArrays(GL_TRIANGLES, 0, 3);
            

        }
        else if (op == 2)
        {
            //AQUI REALIZAMOS LA MUTIPLICACION DE MATRICES PARA OBETENER LAS TRANSFORMACIONES
            transform = transformS * transformRx;

            if (once[1])
            {
                cout << "MATRIZ CON LA TRANSFORMACION S Rx" << '\n';
                cout << glm::to_string(transform) << '\n';
                cout << '\n';
                cout << '\n';
                once[1] = false;
            }


            

            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            //cout << transformLoc << '\n';
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

                ourShader.use();
                glDrawArrays(GL_TRIANGLES, 0, 3);


           
        }
        else if (op == 3)
        {
            //AQUI REALIZAMOS LA MUTIPLICACION DE MATRICES PARA OBETENER LAS TRANSFORMACIONES
            transform = transformT * transformS * transformRx;

            if (once[2])
            {
                cout << "MATRIZ CON LA TRANSFORMACION T S Rx" << '\n';
                cout << glm::to_string(transform) << '\n';
                cout << '\n';
                cout << '\n';
                once[2] = false;
            }

          

            //ourShader.use();
            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //glDrawArrays(GL_TRIANGLES, 0, 3);
                ourShader.use();
                glDrawArrays(GL_TRIANGLES, 0, 3);
            
        }
        else  if (op == 4)
        {
            //AQUI REALIZAMOS LA MUTIPLICACION DE MATRICES PARA OBETENER LAS TRANSFORMACIONES
            transform = transformRx1 * transformT * transformS * transformRx;

            if (once[3])
            {
                cout << "MATRIZ CON LA TRANSFORMACION Rx-1 T S Rx" << '\n';
                cout << glm::to_string(transform) << '\n';
                cout << '\n';
                cout << '\n';
                once[3] = false;
            }

          

            //ourShader.use();
            unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            //glDrawArrays(GL_TRIANGLES, 0, 3);

                ourShader.use();
                glDrawArrays(GL_TRIANGLES, 0, 3);
        

        }
        else
        {
            ourShader2.use();
            glDrawArrays(GL_TRIANGLES, 3, 6);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
