/*
********************************************************
Computación Gráfica
GRUPO:
- Yhon yerson sanchez yucra
*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstring>
#include <string.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader_s.h"

#define PI 3.14159265358979323846 /* pi */
using namespace std;
using namespace glm;

unsigned int texture[6];
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "uniform vec4 ourColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = ourColor;\n"
                                   "}\n\0";

float colorr[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.0f, 0.0f, 2.0f, 0.5f, 1.0f};
float colorg[] = {1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.1f, 0.1f, 0.5f, 0.5f, 0.5f};
float colorb[] = {0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f};

void mostrar()
{
    cout << "Computación Gráfica" << endl;
    cout << "GRUPO:" << endl;
    cout << "- Yhon yerson sanchez yucra" << endl;
    cout << "Presione E para animar estrella" << endl;
    cout << "Presione O para animar rombo" << endl;
    cout << "presione R para animar rectangulo" << endl;
    cout << "presione T para animar triangulo" << endl;
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock() < time_end)
    {
    }
}
float &Acceso(float *vector, int indice)
{
    return vector[indice];
}

void rotar(float &x, float &y, float cx, float cy, float ang)
{
    float dx = x - cx;
    float dy = y - cy;
    float r = sqrt(dx * dx + dy * dy);
    float a = atan2(dy, dx);

    float da_rad = ang / 180 * M_PI;
    a -= da_rad;
    x = cx + r * cos(a);
    y = cy + r * sin(a);
}

void rotar_todo(float arr[], int n, int angle)
{
    for (int i = 0; i < n / 3; ++i)
    {
        rotar(Acceso(arr, i * 3 + 0), Acceso(arr, i * 3 + 1), 0, 0, angle);
    }
}

class Mat
{
public:
    GLfloat elements[16];
    GLfloat operator()(int x, int y)
    {
        return elements[x * 4 + y];
    }
    void operator=(GLfloat *e)
    {
        for (int i = 0; i < 16; i++)
        {
            elements[i] = e[i];
        }
    }
    void operator=(Mat m)
    {
        for (int i = 0; i < 16; i++)
        {
            elements[i] = m.elements[i];
        }
    }
    Mat(GLfloat *e)
    {
        for (int i = 0; i < 16; i++)
        {
            elements[i] = e[i];
        }
    }
    Mat(Mat &m)
    {
        for (int i = 0; i < 16; i++)
        {
            elements[i] = m.elements[i];
        }
    }
    Mat()
    {
        GLfloat identity[16] = {
            1.0f,0.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
            0.0f,0.0f,0.0f,1.0f,
        };
        for (int i = 0; i < 16; i++)
        {
            elements[i] = identity[i];
        }
    }
    void print()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%.3f ", elements[i * 4 + j]);
            }
            cout << endl;
        }
        cout << endl;
    }
};

//*************************************************
//      	figuras
//*************************************************

GLfloat points_base[] = {
    0.0f, 0.15f, 0.0f,
    -0.08f, 0.0f, 0.0f,
};

GLfloat triangulo[] = {
    0.0f, 0.15f, 0.0f, 0.0f,0.0f,0.0f,  0.0f,0.15f,
    -0.08f, 0.0f, 0.0f,0.0f,0.0f,0.0f,  -0.08f,0.0f,
    0.08f, 0.0f, 0.0f, 0.0f,0.0f,0.0f,  0.08f,0.0f
    };

GLfloat triangulo_base[] = {
    0.0f, 0.15f, 0.0f,
    -0.08f, 0.0f, 0.0f,
    0.08f, 0.0f, 0.0f};

//************************************************
// 		Matrix Identidad
// ***********************************************
GLfloat identiti[] = {
    1.0f,0.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_identity(identiti);

//************************************************
//   		Traslacion +X
//************************************************
GLfloat tx = 0.05f, ty = 0.0f, tz = 0.0f;
GLfloat position_x[] = {
    1.0f,0.0f,0.0f,tx,
    0.0f,1.0f,0.0f,ty,
    0.0f,0.0f,1.0f,tz,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_position_x(position_x);

//************************************************
//   		Traslacion +Y
// ***********************************************
GLfloat tpx = 0.0f, tpy = 0.05f, tpz = 0.0f;
GLfloat position_y[] = {
    1.0f,0.0f,0.0f,tpx,
    0.0f,1.0f,0.0f,tpy,
    0.0f,0.0f,1.0f,tpz,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_position_y(position_y);

//************************************************
//   		Traslacion -X
//************************************************
GLfloat tmx = -0.05f, tmy = 0.0f, tmz = 0.0f;
GLfloat position_mx[] = {
    1.0f,0.0f,0.0f,tmx,
    0.0f,1.0f,0.0f,tmy,
    0.0f,0.0f,1.0f,tmz,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_position_mx(position_mx);
//**************************************************
//		Traslacion -Y
//**************************************************
GLfloat tpmx = 0.0f, tpmy = -0.05f, tpmz = 0.0f;
GLfloat position_my[] = {
    1.0f,0.0f,0.0f,tpmx,
    0.0f,1.0f,0.0f,tpmy,
    0.0f,0.0f,1.0f,tpmz,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_position_my(position_my);

//************************************************
//     		 	Scala
//************************************************
GLfloat sx = 0.7f, sy = 0.7f, sz = 0.0f;
GLfloat scales[] = {
    sx,0.0f,0.0f,0.0f,
    0.0f,sy,0.0f,0.0f,
    0.0f,0.0f,sz,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_scale(scales);

float angle_x = 45.0, angle_y = 33.0, angle_z = 57.0;
float cosine_x = cos(angle_x * PI / 180.0);
float sine_x = sin(angle_x * PI / 180.0);
float cosine_y = cos(angle_y * PI / 180.0);
float sine_y = sin(angle_y * PI / 180.0);
float cosine_z = cos(angle_z * PI / 180.0);
float sine_z = sin(angle_z * PI / 180.0);

//************************************************
// 			Rotacion Z
// ***********************************************
GLfloat rotate_z[] = {
    cosine_z,-sine_z,0.0f,0.0f,
    sine_z,cosine_z,0.0f,0.0f,
    0.0f,0.0f,1.0f,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_rz(rotate_z);

// ***********************************************
//   			Rotacion Y
//************************************************
GLfloat rotate_y[] = {
    cosine_y,0.0f,sine_y,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    -sine_y,0.0f,cosine_y,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_ry(rotate_y);

// ***********************************************
// 			Rotacion X
// ***********************************************
GLfloat rotate_x[] = {
    1.0f,0.0f,0.0f,0.0f,
    0.0f,cosine_x,-sine_x,0.0f,
    0.0f,sine_x,cosine_x,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_rx(rotate_x);
//**************************************************
// 			Inversa Rotacion Y
// *************************************************
GLfloat inverse_rotate_y[] = {
    cosine_y,0.0f,-sine_y,0.0f,
    0.0f,1.0f,0.0f,0.0f,
    sine_y,0.0f,cosine_y,0.0f,
    0.0f,0.0f,0.0f,1.0f,
};
Mat mat_inverse_ry(inverse_rotate_y);

//**************************************************
//			Secuencia
//**************************************************
Mat sequence_scale[20] = {
    mat_scale, mat_scale, mat_scale};

GLfloat *multiply(GLfloat vec[], Mat mat)
{
    GLfloat *result = new GLfloat[4];
    for (int i = 0; i < 4; i++)
    {
        result[i] = 0.0f;
        for (int j = 0; j < 4; j++)
        {
            result[i] += mat(i, j) * vec[j];
        }
    }
    return result;
}

int so = 0;
void mover_scala(int soo)
{
    GLfloat *result = new GLfloat[3];
    for (int i = 0; i < 3; i++)
    {
        GLfloat point[] = {triangulo[i * 3], triangulo[i * 3 + 1], triangulo[i * 3 + 2], 1.0f};
        result = multiply(point, sequence_scale[soo]);
        //sequence[co].print();
        triangulo[i * 3] = result[0];
        triangulo[i * 3 + 1] = result[1];
        triangulo[i * 3 + 2] = result[2];
    }

    if (soo == 3)
    {
        so = 0;
        for (int i = 0; i < 3; i++)
        {
            triangulo[i * 3] = triangulo_base[i * 3];
            triangulo[i * 3 + 1] = triangulo_base[i * 3 + 1];
            triangulo[i * 3 + 2] = triangulo_base[i * 3 + 2];
        }
    }
    sleepcp(50);
}

bool triangle_scale = false;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "my version opengl", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    // glad: load all opengl function pouinter
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // ****************** outshader ************************** 
    string vs = "/home/yrsn/WorkSpace/ComputacionGrafica/Template/src/hw/3.3.shader.vs";
    string fs = "/home/yrsn/WorkSpace/ComputacionGrafica/Template/src/hw/3.3.shader.fs";
    Shader ourShader(vs.c_str(), fs.c_str());



    //*****************VertexShader******************
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //**************check vertex shader*********
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR VERTER:_SHADER_COMPILATION" << std::endl;
    }
    //**************CREATE AND COMPILE Fragment shadre***********
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //**************FRAGMENTSHADER**********************
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infolog << std::endl;
    }
    //***********LINK SHADER*************************
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //***********check for linking errors************
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infolog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //***************END CONCIFG AND LINKED ***************
    unsigned int VBO[11], VAO[11], EBO, TRI, FG3, FG4, FG5, FG6, FG7, FG8, FG9, FG10;
    glGenVertexArrays(11, VAO);
    glGenBuffers(11, VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &TRI);
    glGenBuffers(1, &FG3);
    glGenBuffers(1, &FG4);
    glGenBuffers(1, &FG5);  //marco
    glGenBuffers(1, &FG6);  //niño
    glGenBuffers(1, &FG7);  //cabelloniño
    glGenBuffers(1, &FG8);  //manomadre
    glGenBuffers(1, &FG9);  //manomadre
    glGenBuffers(1, &FG10); //manomadre
vector<string> nombresTexturas = {
    "container.jpg",
    "C.png",
    "S.png",
    "P.png",
    "C.png",
    "G.png"
    };

// ********** Load and create texture ***********************
for(int i=0; i<6; i++){
    glGenTextures(1, &texture[i]);
    glBindTexture(GL_TEXTURE_2D, texture[i]); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    string path = "/home/yrsn/WorkSpace/ComputacionGrafica/Template/src/hw/";
    path+=nombresTexturas[i];
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}

    ourShader.use();


    //**********Triangulos*********************
    mostrar();
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        //**********primera figura en VAO[0]******
        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points_base), points_base, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangulo), triangulo, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        //*************position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //*************color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        //*************texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        if (triangle_scale)
            mover_scala(so++);

        // 		rotar_todo(estrella,27,5);
        //int r = rand() % 9 + 0;
        //int g = rand() % 9 + 0;
        //int b = rand() % 9 + 0;
        //sleepcp(100);

        glBindTexture(GL_TEXTURE_2D, texture[0]);
        ourShader.use();
        //glUniform4f(vertexColorLocation, colorr[r], colorg[g], colorb[b], 0.0f);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        triangle_scale = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        int cont=0;
        GLfloat *result = new GLfloat[3];
        for (int i = 0; i < 3; i++)
        {
            GLfloat point[] = {triangulo[i * 8], triangulo[i * 8 + 1], triangulo[i * 8 + 2], 1.0f};
            result = multiply(point, mat_position_x);
            //sequence[co].print();
            triangulo[i * 8] = result[0];
            triangulo[i * 8 + 1] = result[1];
            triangulo[i * 8 + 2] = result[2];
        }

        if (cont == 3)
        {
            so = 0;
            for (int i = 0; i < 3; i++)
            {
                triangulo[i * 8] = triangulo_base[i * 3];
                triangulo[i * 8 + 1] = triangulo_base[i * 3 + 1];
                triangulo[i * 8 + 2] = triangulo_base[i * 3 + 2];
            }
        }
    }
}
