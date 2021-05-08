/*
********************************************************
Computación Gráfica
GRUPO:
- Yhon yerson sanchez yucra
- Jose Gabriel Zevallos Delgado de la Flor
- Christopher Yquira Miranda

<PRESIONE B PARA VER LAS crecer las lineas y N para contrare>
*******************************************************
*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cmath>
#include <time.h>
#define M_PI 3.14159265358979323846 /* pi */
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

float &Acceso(float *vector, int indice)
{
	return vector[indice];
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
	clock_t time_end;
	time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while (clock() < time_end)
	{
	}
}

float tallo[] = {
        0.0f,0.0f,0.0f,
        0.1f,0.04f,0.0f,
        0.14f,0.12f,0.0f,//''''''''''''

        0.0f,0.0f,0.0f,
        0.04f,0.08f,0.0f,
        0.14f,0.12f,0.0f,

        0.0f,0.0f,0.0f,
        -0.04f,0.08f,0.0f,
         -0.14f,0.12f,0.0f,

         0.0f,0.0f,0.0f,
        -0.1f,0.04f,0.0f,
        -0.14f,0.12f,0.0f
    };
int nn = sizeof(tallo) / sizeof(tallo[0]);
        float flor[] = {
         0.0f, 0.26,0.0f,
        0.052f,0.29f,0.0f,
        0.06f,0.32f,0.0f,
        0.06f,0.36f,0.0f,
        0.03f,0.34f,0.0f,
        0.0f,0.36f,0.0f,
        -0.03f,0.34f,0.0f,
        -0.06f,0.36f,0.0f,
        -0.06f,0.32f,0.0f,
        -0.052f,0.29f,0.0f,
        0.0f,0.26f,0.0f,
        0.0f,0.0f,0.0f,
        0.0f,0.26f,0.0f,//14

        0.0f,0.32f,0.0f,

        0.0f,0.32f,0.0f,
        -0.03f,0.34f,0.0f,

        0.0f,0.32f,0.0f,

         0.0f,0.32f,0.0f,
         0.03f,0.34f,0.0f
    };

float array[] =
	{
		0.0f, 0.5f, 0.0f,  //A
		-0.2f, 0.0f, 0.0f, //B
		0.2f, 0.0f, 0.0f,  //C
		-0.2f, 0.4f, 0.0f, //D
		0.2f, 0.4f, 0.0f,  //E
		0.0f, 0.16f, 0.0f  //F

};
int n = sizeof(array) / sizeof(array[0]);

unsigned int Indicearray[] =
	{
		0, 1, 5,
		0, 5, 2,
		3, 4, 5};

float LineasCuadro[] = {
	-0.46f, 0.64f, 0.0f,
	0.44f, 0.64f, 0.0f,

	0.44f, 0.64f, 0.0f,
	0.44f, -0.57f, 0.0f,

	0.44f, -0.57f, 0.0f,
	-0.45f, -0.56f, 0.0f,

	-0.45f, -0.56f, 0.0f,
	-0.46f, 0.64f, 0.0f,
	////line1
	-0.43, 0.64f, 0.0f,
	-0.32f, -0.55f, 0.0f,
	////line2
	-0.45f, -0.02, 0.0f,
	-0.31f, 0.03, 0.0f,
	-0.31f, 0.03, 0.0f,
	-0.06f, 0.1, 0.0f,
	////linea3
	0.25f, 0.1, 0.0f,
	0.43f, 0.06, 0.0f
	////linea 4
};

float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left
	0.5f, -0.5f, 0.0f,	// right
	0.0f, 0.5f, 0.0f,	// top

	0.8f,0.4f,0.0f,
	0.6f,0.0f,0.0f,
	0.9f,0.0f,0.0f
};

void invertir(int pos, float value)
{
	for (int i = 0; i < n / 3; ++i)
	{
		Acceso(array, i * 3 + pos) += value;
		//      cout<<Acceso<<endl;
	}
}

void invertir_tallo(int pos, float value)
{
	for (int i = 0; i < nn / 3; ++i)
	{
		if(i!=0 or i!=3){
			Acceso(tallo, i * 3 + pos) += value;
		}
		//      cout<<Acceso<<endl;
	}
}




void print()
{
	for (int i = 0; i < n; ++i)
	{
		if (i % 3 == 0)
			cout << endl;
		cout << array[i] << " ";
	}
}

bool ani1 = true, ani2 = false, ani3 = false, ani4 = false, ro = false;
void animacion_yplus()
{
	float x = 0.01;
	if (Acceso(array, 1) < 1.0)
	{
		invertir(1, x);
		x += x;
	}
	else
	{
		ani1 = false;
		ani2 = true;
	}
}
void animacion_yless()
{
	float x = 0.01;
	if (Acceso(array, 4) > -1)
	{
		invertir(1, -x);
		x += x;
	}
	else
	{
		ani2 = false;
		ani3 = true;
	}
}
void animacion_dless()
{
	float x = 0.01;
	if (Acceso(array, 12) < 1)
	{
		invertir(0, x);
		x += x;
	}
	else
	{
		ani3 = false;
		ani4 = true;
	}
}
void animacion_aless()
{
	float x = 0.01;
	if (Acceso(array, 9) > -1)
	{
		invertir(0, -x);
		x += x;
	}
	else
	{
		ani4 = false;
	}
}

void animacion()
{
	if (ani1)
	{
		animacion_yplus();
		// 	    cout<<"1"<<endl;
	}
	else if (ani2)
	{
		animacion_yless();
		// 	    cout<<"2"<<endl;
	}
	else if (ani3)
	{
		animacion_dless();
		// 	    cout<<"3"<<endl;
	}
	else
	{
		animacion_aless();
	}
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
float ang = 1;
void mover()
{
	for (int i = 0; i < n / 3; ++i)
	{
		rotar(Acceso(array, i * 3 + 0), Acceso(array, i * 3 + 1), 0, 0.486, ang);
	}
	ang += 1;
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

	//*****array para dos figuras y EBO para un indice
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

	//**********lineas cuadro*****************
	glBindVertexArray(VAO[9]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LineasCuadro), LineasCuadro, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);


	//**********Triangulos*********************
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	


	float forw = 0.01;
	bool start = false;
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			if (Acceso(array, 1) < 1.0)
			{
				invertir(1, 0.01);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			if (Acceso(array, 4) > -1)
				invertir(1, -0.01);
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			if (Acceso(array, 12) < 1)
				invertir(0, 0.01);
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			if (Acceso(array, 9) > -1)
				invertir(0, -0.01);
		}

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			if (Acceso(array, 1) < 1.0 and Acceso(array, 9) > -1)
			{
				invertir(1, 0.01);
				invertir(0, -0.01);
			}
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			if (Acceso(array, 1) < 1.0 and Acceso(array, 12) < 1)
			{
				invertir(1, 0.01);
				invertir(0, 0.01);
			}
		}

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			if (Acceso(array, 4) > -1 and Acceso(array, 12) < 1)
			{
				invertir(1, -0.01);
				invertir(0, 0.01);
			}
		}

		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			if (Acceso(array, 4) > -1 and Acceso(array, 9) > -1)
			{
				invertir(1, -0.01);
				invertir(0, -0.01);
			}
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			start = true;
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			start = false;
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			ro = true;
		}
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			ro = false;
		}
		if (start)
			animacion();
		if (ro)
			mover();


		if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		{float cv = 0.01;
			cout<<"peresds"<<endl;
			cout<<Acceso(tallo, 6 )<<endl;
			Acceso(tallo, 6 ) += cv;
			Acceso(tallo, 15 ) += cv;
			Acceso(tallo, 24 ) -= cv;
			Acceso(tallo, 33 ) -= cv;

			Acceso(tallo, 13 ) += cv;
			Acceso(tallo, 22 ) += cv;

			Acceso(tallo, 4 ) -= cv;
			Acceso(tallo, 31 ) -= cv;

			Acceso(flor, 6 ) += cv;
			Acceso(flor, 3 ) += cv;
			
			Acceso(flor, 16 ) += cv;
			Acceso(flor, 22 ) += cv;

			Acceso(flor, 18 ) -= cv;
			Acceso(flor, 24 ) -= cv;

		}
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		{float cv = 0.01;
			Acceso(tallo, 6 ) -= cv;
			Acceso(tallo, 15 ) -= cv;
			Acceso(tallo, 24 ) += cv;
			Acceso(tallo, 33 ) += cv;

			Acceso(tallo, 13 ) -= cv;
			Acceso(tallo, 22 ) -= cv;

			Acceso(tallo, 4 ) += cv;
			Acceso(tallo, 31 ) += cv;
			Acceso(flor, 6 ) -= cv;
			Acceso(flor, 3 ) -= cv;
			Acceso(flor, 16 ) -= cv;
			Acceso(flor, 22 ) -= cv;

			Acceso(flor, 17 ) += cv;
			Acceso(flor, 23 ) += cv;
			Acceso(flor, 16 ) += cv;
			Acceso(flor, 24 ) += cv;

		
		}

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{float cv = 0.01;
		
			
			Acceso(tallo, 7 ) += cv;
			Acceso(tallo, 16 ) += cv;
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{float cv = 0.01;
		
			
			Acceso(tallo, 7 ) -= cv;
			Acceso(tallo, 16 ) -= cv;
		}
		if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		{
			
		}


		// 		animacion_zless();
		//**********primera figura en VAO[0]******
		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(array), array, GL_STATIC_DRAW);
		//********indcies para la figura en VAO[0]******
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indicearray), Indicearray, GL_STATIC_DRAW);
		//*********pointer para la figura VAO[0]************
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		//**********end**primera_figura*********


	//**********tallo*********************
		glBindVertexArray(VAO[2]);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		//************floar**********************
		glBindVertexArray(VAO[3]); 
		glBindBuffer(GL_ARRAY_BUFFER, VAO[3]); 
		glBufferData(GL_ARRAY_BUFFER, sizeof(flor), flor, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 
		glEnableVertexAttribArray(0);





/*
		glUseProgram(shaderProgram);
		glPointSize(10);
		glLineWidth(5.0f);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUniform4f(vertexColorLocation, 1.0f, 1.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
*/
// 		//********Lineas del cuadrado******
// 		glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
// 		glBindVertexArray(VAO[9]);
// 		glLineWidth(5.0f);
// 		glDrawArrays(GL_LINES, 0, 4);
// 
// 		//********triangulos***************
// 		glUniform4f(vertexColorLocation, 0.0f, 1.0f, 0.0f, 0.0f);
// 		glBindVertexArray(VAO[1]);
// 		glDrawArrays(GL_TRIANGLES, 0, 3);
// 
// 		//********triangulo 2***************
// 		glUniform4f(vertexColorLocation, 1.0f, 0.0f, 0.0f, 0.0f);
// 		glBindVertexArray(VAO[1]);
// 		glDrawArrays(GL_TRIANGLES, 3, 6);
//
		glBindVertexArray(VAO[2]);
        glPointSize(5);
        glDrawArrays(GL_TRIANGLES, 0,21);
      
        // then we draw the second triangle using the data from the second VAO
        glBindVertexArray(VAO[3]);
        glDrawArrays(GL_LINE_STRIP, 0, 19);





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
}
