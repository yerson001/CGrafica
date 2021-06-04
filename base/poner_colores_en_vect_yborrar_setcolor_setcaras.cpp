#include <glad/glad.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"
#include "Rubik.hpp"
#include "camera.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// string mainPath = "/home/yrsn/WorkSpace/ComputacionGrafica/Template/src/hw1/";
string mainPath = "/home/yrsn/WorkSpace/ComputacionGrafica/Proyecto Rubik/src/Proyecto_Cubo/";
glm::mat4 model1 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
unsigned int VBO[27], VAO[27];
unsigned int textures[6];
bool presionado = false;
//D Yellow       U White         B Blue         F Green          L Orange        R RED
vector<vector<float>> colores = { {1.0, 1.0, 0.0}, {1.0,1.0,1.0},{0.0, 0.0, 1.0},{0.0, 1.0, 0.0},{1.0, 0.647, 0.0}, {1.0, 0.0, 0.0} };

// camera
Camera camera(glm::vec3(1.0f, 1.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
// time between current frame and last frame
float deltaTime = 0.0f;	
float lastFrame = 0.0f;

//intervalo entre cubos
float intervalo = 1.1;      


//ROTACIONES
int anguloDividido = 100;
float angulo = 90.0f;

void rotateVec(mat4& model, vec3 val) {  //count 2000 veces como m�ximo
    //rotaci�n en eje origen del mundo
    mat4 nuevo(1.0f);
    nuevo = glm::rotate(nuevo, glm::radians(angulo / anguloDividido), val);
    model = nuevo * model;
}

//hace que gire en el eje "x, y, z" del mundo
void rotateVecSame(mat4& model, vec3 val) {
    mat4 nuevo(1.0f);
    nuevo = glm::rotate(nuevo, glm::radians(angulo / anguloDividido), val);
    model = nuevo * model;          //hace que gire en el eje "x, y, z" del mundo
}



void menu() {
    cout << "Presiona  :" << endl;
    cout << "W:       para acercarte" << endl;
    cout << "S:       para alejarte" << endl;
    cout << "A:       para mover la c�mara a la izquierda" << endl;
    cout << "D:       para mover la c�mara a la derecha" << endl;
    cout << endl;
}

vector<float> vertices0 = {
        -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,     1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,     0.0f, 0.0f,                     //  DOWN
         0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,     1.0f, 0.0,

        -0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 0.0f,                          //UP FACE
         0.5f,  0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,



         0.5f, -0.5f, -0.5f,      0.0,0.0, 0.0,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,      0.0,0.0, 0.0,    0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,      0.0,0.0, 0.0,    0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,      0.0,0.0, 0.0,    0.0f, 1.0f,       
         0.5f,  0.5f, -0.5f,      0.0,0.0, 0.0,    1.0f, 1.0f,        
         0.5f, -0.5f, -0.5f,      0.0,0.0, 0.0,    1.0f, 0.0,

        -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,        
         0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,        
         0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,        
         0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f
};



class cubie
{
public:
    unsigned int idVAO;
    //nuestra figura
    glm::mat4 model;
    //coordenada
    glm::vec3 puntoInicial;
    vector<float> vertices;


    cubie() = default;
    cubie(vec3 point, int id);

    //configura el VAO, VBO
    void configVertex();       
     //dibuja el cubi                         
    void drawing(Shader* myShader);    
    void setColors();   
     int setFace(char side);              
    void roteD(Shader* myShader);
    void roteI(Shader* myShader);

private:

};

// creamos un cubo
cubie::cubie(vec3 point, int id) {
    idVAO = id;
    //getting initial point
    puntoInicial = point;
    //setting model
    model = mat4(1.0f);
    model = glm::translate(model, puntoInicial);
    vertices = vertices0;

}

void cubie::drawing(Shader* myShader) {
    //Setting nwew matrix 1 VAO0
    myShader->setMat4("model", model);
    // render box
    glBindVertexArray(VAO[idVAO]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    configVertex();
}

void cubie::roteD(Shader* myShader) {
    myShader->setMat4("model", model);
    // render box
    rotateVecSame(model, glm::vec3(0.0f, 0.0f, 1.0f));
    glBindVertexArray(VAO[idVAO]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    configVertex();
}


void cubie::roteI(Shader* myShader) {
    myShader->setMat4("model", model);
    // render box
    rotateVecSame(model, glm::vec3(-1.0f,0.0f, -1.0f));
    glBindVertexArray(VAO[idVAO]);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    configVertex();
}



void cubie::configVertex() {
    glBindVertexArray(VAO[idVAO]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[idVAO]);
    glBufferData(GL_ARRAY_BUFFER, vertices0.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color  attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}



class RubikCube
{
public:
    cubie* cubos[27];
    Shader* myShader;
    RubikCube(Shader& nuevo);
    RubikCube();
    void setInitialPoints();
    void drawing();
    void roteD();
    void roteI();
private:

};
RubikCube* cuboPrincipal;

RubikCube::RubikCube() {
}
void RubikCube::roteD() {
    for (int i = 0; i < 9; i++) {
        //Sleep(50);
        cubos[i]->roteD(myShader);
    }
}
void RubikCube::roteI() {
    for (int i = 0; i < 27; i++) {
        //Sleep(50);
        cubos[i]->roteI(myShader);
    }
}

RubikCube::RubikCube(Shader& nuevo) {
    myShader = &nuevo;
    setInitialPoints();
}

void RubikCube::setInitialPoints() {
    //punto inicial de donde se dibuja
    vec3 init = vec3(-1.1, -1.1, -1.1);
    vector<vec3> puntos;
    vec3 capa = init;

    //generando 3 matrices de 3 x 3 para el cubo
    for (int k = 0; k < 3; k++) {
        vec3 fila = capa;
        for (int j = 0; j < 3; j++) {
            puntos.push_back(fila);
            vec3 columna = fila;
            //creando dos cubos avanzando en eje x
            for (int i = 0; i < 2; i++) {
                //avanza la columna
                columna = columna + vec3(intervalo, 0.0, 0.0);
                puntos.push_back(columna);
            }
            fila = fila + vec3(0.0, intervalo, 0.0);
        }
        capa = capa + vec3(0.0, 0.0, intervalo);
    }

    //Creando 27 cubos peque�os
    for (int i = 0; i < puntos.size(); i++) {
        cubos[i] = new cubie(puntos[i], i);
    }
}





void RubikCube::drawing() {
    for (int i = 0; i < 27; i++){
        cubos[i]->drawing(myShader);
    }
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef APPLE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    string vs = mainPath + "3.3.shader.vs", fs = mainPath + "3.3.shader.fs";
    Shader ourShader(vs.c_str(), fs.c_str());


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------



    //unsigned int VBO[3], VAO[3];
    glGenVertexArrays(27, VAO);
    glGenBuffers(27, VBO);




    vector<string> nombresTexturas = {
        "faceo.png",
        "face1.png",
        "container.jpg",
        "P.png",
        "C.png",
        "G.png"

    };

     for (int i = 0; i < 6; i++) {
         // texture 1
     // ---------
         glGenTextures(1, &textures[i]);
         glBindTexture(GL_TEXTURE_2D, textures[i]);
         // set the texture wrapping parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
         // set texture filtering parameters
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         // load image, create texture and generate mipmaps
         int width, height, nrChannels;
         stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
         string path = mainPath + nombresTexturas[i];
         unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
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




    /*
    string sequence = "B U B U B B", moves;
    moves = Rubik::solve(sequence);
    cout << "MOVES :   " << moves << endl;*/

    //cout << "FORMATEADO:  " << Rubik::format(moves);

    RubikCube CUBOOS(ourShader);

    cuboPrincipal = &CUBOOS;


    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    // render loop
    // -----------

    menu();

    int val = 0;
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // input
        // -----
        processInput(window);
        glfwSetKeyCallback(window, key_callback);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation|
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);
        CUBOOS.drawing();

       
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            CUBOOS.roteD();

        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
            CUBOOS.roteI();
        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(27, VAO);
    glDeleteBuffers(27, VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

