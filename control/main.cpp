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
#include <vector>
#define PI 3.14159265358979323846 /* pi */
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow *window);

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

int co = 0;
float tx = 0.35, ty = 0.65, tz = 1.25;

float traslacion[] = {
	1.0f,0.0f,0.0f,tx,
	0.0f,1.0f,0.0f,ty,
	0.0f,0.0f,1.0f,tz,
	0.0f,0.0f,0.0f,1.0f,
};


float angle_x = 65.0, angle_y = 55.0, angle_z = 93.0;

float cosine_y = cos(angle_y * PI / 180.0);
float sine_y = sin(angle_y * PI / 180.0);
float cosine_z = cos(angle_z * PI / 180.0);
float sine_z = sin(angle_z * PI / 180.0);

float rotate_y[] = {
	cosine_y,0.0f,sine_y,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	-sine_y,0.0f,cosine_y,0.0f,
	0.0f,0.0f,0.0f,1.0f,
};


float rotate_z[] = {
	cosine_z,-sine_z,0.0f,0.0f,
	sine_z,cosine_z,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f,
};


float sx = 1.25, sy = 1, sz = 1.25;

float scale[] = {
	sx,0.0f,0.0f,0.0f,
	0.0f,sy,0.0f,0.0f,
	0.0f,0.0f,sz,0.0f,
	0.0f,0.0f,0.0f,1.0f,
};


float points_base[]={
	0.75f,-0.5f,0.0f, 
	0.25f,0.5f,0.0f,
	0.0f,-0.5f,0.0f
};

float points1[] = {
	0.75f,-0.5f,0.0f,0.0f, 
	0.25f,0.5f,0.0f,0.0f,
	0.0f,-0.5f,0.0f,0.0,
	0.0f,0.0f,0.0f,1.0
	};


float tallo[] = {
	-0.527457f, -0.510823f, 0.767955f, -0.0625f, 
	0.489934f, -0.205165f, 0.255985f, 0.4125f, 
	-0.499315f, 0.026168f, 0.0f, -0.325f, 
	0.0f, 0.0f, 0.0f, 1.0
};
int nn = sizeof(tallo) / sizeof(tallo[0]);
float flor[] = {};
float array[] = {
	0.75f,-0.5f,0.0f, 
	0.25f,0.5f,0.0f,
	0.0f,-0.5f,0.0f
};

int n = sizeof(array) / sizeof(array[0]);
unsigned int Indicearray[] = {
	0, 1, 2,};
float LineasCuadro[] = {};
float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left
	0.5f, -0.5f, 0.0f,	// right
	0.0f, 0.5f, 0.0f,	// top

	0.8f, 0.4f, 0.0f,
	0.6f, 0.0f, 0.0f,
	0.9f, 0.0f, 0.0f};

void print(float arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i % 4 == 0)
			cout << endl;
		cout << arr[i] << " ";
	}
}




float C1[10][10];
float C2[10][10];
float C3[10][10];
float C4[10][10];


void multiplicar1(float A[],float B[]){
  float AA[10][10], BB[10][10];
    int io=0;
    for (int i=0; i <4; i++){
      for(int j=0; j<4; j++){
        AA[i][j] = A[io++];
      }
    }


    int pio=0;
    for (int i=0; i <4; i++){
      for(int j=0; j<4; j++){
        BB[i][j] = B[pio++];
      }
    }

      cout<<"ARRAY A"<<endl;
      for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          cout<<AA[i][j]<<" ";
        }
        cout<<endl;
      }
    cout<<endl;
    cout<<"ARRAY B"<<endl;
        for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          cout<<BB[i][j]<<" ";
        }
        cout<<endl;
      }
      // MULTIPLICATION
      for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          C1[i][j] = 0;
          for(int k=0; k < 4; k++) { // k < q WILL ALSO WORK
            C1[i][j] += AA[i][k]*BB[k][j];
          }
        }
      }
	for(int i = 0; i < 4; i++) {
      for(int k = 0; k < 4; k++) {
        cout<<C1[i][k]<<" ";
      }
      cout<<endl;
    }
}


void multiplicar2(float A[]){
  float AA[10][10], BB[10][10];
    int io=0;
    for (int i=0; i <4; i++){
      for(int j=0; j<4; j++){
        AA[i][j] = A[io++];
      }
    }
      // MULTIPLICATION
      for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          C2[i][j] = 0;
          for(int k=0; k < 4; k++) { // k < q WILL ALSO WORK
            C2[i][j] += AA[i][k]*C1[k][j];
          }
        }
      }
	for(int i = 0; i < 4; i++) {
      for(int k = 0; k < 4; k++) {
        cout<<C2[i][k]<<" ";
      }
      cout<<endl;
    }
}

void multiplicar3(float A[]){
  float AA[10][10], BB[10][10];
    int io=0;
    for (int i=0; i <4; i++){
      for(int j=0; j<4; j++){
        AA[i][j] = A[io++];
      }
    }
      // MULTIPLICATION
      for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          C3[i][j] = 0;
          for(int k=0; k < 4; k++) { // k < q WILL ALSO WORK
            C3[i][j] += AA[i][k]*C2[k][j];
          }
        }
      }
	for(int i = 0; i < 4; i++) {
      for(int k = 0; k < 4; k++) {
        cout<<C3[i][k]<<" ";
      }
      cout<<endl;
    }
}
vector<float> my_point;

void multiplicar4(float A[]){
  float AA[10][10], BB[10][10];
    int io=0;
    for (int i=0; i <4; i++){
      for(int j=0; j<4; j++){
        AA[i][j] = A[io++];
      }
    }
      // MULTIPLICATION
      for(int i=0; i < 4; i++) {
        for(int j=0; j < 4; j++) {
          C4[i][j] = 0;
          for(int k=0; k < 4; k++) { // k < q WILL ALSO WORK
            C4[i][j] += C3[k][j]*AA[i][k];
          }
        }
      }
	for(int i = 0; i < 4; i++) {
      for(int k = 0; k < 4; k++) {
        cout<<C4[i][k]<<" ";
		my_point.push_back(C4[i][k]);
      }
      cout<<endl;
    }
}


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
	glGenBuffers(1, &FG5);	//marco
	glGenBuffers(1, &FG6);	//niño
	glGenBuffers(1, &FG7);	//cabelloniño
	glGenBuffers(1, &FG8);	//manomadre
	glGenBuffers(1, &FG9);	//manomadre
	glGenBuffers(1, &FG10); //manomadre

	//**********Triangulos*********************
	
	//*****array para dos figuras y EBO para un indice
  		cout<<"M = (T*(Ry*(S*Rz)))"<<endl;cout<<endl;      
		cout<<"MULTIPLICACION (S*Rz) = C1"<<endl;
		multiplicar1(scale,rotate_z);cout<<endl;cout<<endl;
		cout<<"MULTIPLICACION (Ry*C1) = C2"<<endl;
		multiplicar2(rotate_y);cout<<endl;cout<<endl;
		cout<<"MULTIPLICACION (T*C2) = M"<<endl;
		multiplicar3(traslacion);cout<<endl;cout<<endl;

		cout<<"MULTIPLICACION (M*X) punto despues de la transformación"<<endl;
		multiplicar4(points1);cout<<endl;cout<<endl;
		cout<<"triangulo ROJO [puntos Iniciales] AZUL[Despues de la transformación (M*X) ]"<<endl;


	float arr[my_point.size()];
	std::copy(my_point.begin(), my_point.end(), arr);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.6f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		
		//**********primera figura en VAO[0]******
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicearray), Indicearray, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(VAO[1]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);



		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		


		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[0]);
		glPointSize(5);
		//glDrawArrays(GL_TRIANGLES, 3, 6);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 1.0f, 0.0f);
 		glBindVertexArray(VAO[1]);
 		glDrawArrays(GL_TRIANGLES, 0,3);

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
	GLfloat *result = new GLfloat[3];
	if (key == GLFW_KEY_A and action == GLFW_PRESS)
	{ //siguiente multiplicacion en la secuencia
		co += 1;
	}
	if ((key == GLFW_KEY_D and action == GLFW_PRESS) or (co == 11))
	{ //reiniciar puntos y secuencia
		for (int i = 0; i < 16; i++)
		{
			points1[i] = points_base[i];
		}
		co = -1;
	}
	if (key == GLFW_KEY_S and action == GLFW_PRESS)
	{ //reiniciar solo puntos-
		for (int i = 0; i < 16; i++)
		{
			points1[i] = points_base[i];
		}
	}
	if (key == GLFW_KEY_M and action == GLFW_PRESS)
	{ 
		cout<<"SxRz = C1"<<endl;
		multiplicar1(scale,rotate_z);
		cout<<"RyxC1 = C2"<<endl;
		multiplicar2(rotate_y);
		cout<<"TxC2 = C3"<<endl;
		multiplicar3(traslacion);

		cout<<"MxX"<<endl;
		multiplicar4(points1);
		cout<<"-------------------------"<<endl;
	    for(int i=0; i<my_point.size(); i++){
			cout<<my_point[i]<<endl;
		}
	}
}
