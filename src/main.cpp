//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include <shader.hpp>


using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;

 
int main() {

	//TODO

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);


	//initGLFW

	GLFWwindow * window;

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hola mundo", nullptr, nullptr);
	
	if (!window) {
		std::cout << "Error al cargar la ventana" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Error al cargar glew" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetKeyCallback(window, key_callback2);

	while (!glfwWindowShouldClose(window)) {
		int screenwithd, screenHeight;

		glfwGetFramebufferSize(window, &screenwithd, &screenHeight);
		glViewport(0, 0, screenwithd, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10.f, 10.f, 10.f, -10.f, -1.f, 10.f);
		glMatrixMode(GL_MODELVIEW);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);



	//fondo
	//TODO


	//cargamos los shader
	GLuint programID = LoadShaders("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");

	// Definir el buffer de vertices

	GLfloat vertexData[] = {
		//  X     Y     Z
		0.5f, 0.5f,  0,		// Top Right
		0.5f, -0.5f,	 0,		// Bottom Right
		-0.5f, -0.5f, 0,		// Bottom Left
		-0.5f, 0.5f,	0		// Top Left 
	};



	// Definir el EBO

	GLuint indices[] = {
		1,3,0,//1ST
		1,2,3 };//2ND



	// Crear los VBO, VAO y EBO

	GLuint VBO;
	GLuint VAO;
	GLuint EBO;


	//reservar memoria para el VAO, VBO y EBO	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	//Establecer el objeto
	//Declarar el VBO y el EBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//Enlazar el buffer con openGL
	glBindVertexArray(VAO);//VAO
	

	

	//Establecer las propiedades de los vertices
	glEnableVertexAttribArray(programID);
	//glVertexAttribPointer(programID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glVertexAttribPointer(programID, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	///////////////////////////////////
	// unbind the VAO, the VBO and the EBO	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	/////////////////////////////////////

	//	//liberar el buffer
	//glDeleteVertexArrays(1, &VAO);
	//glGenBuffers(1, &EBO);
	//
	////liberar el buffer de vertices
	//glDeleteBuffers(1, &VBO);



	//int x = 1;
	////bucle de dibujado
	//while (x == 1)
	//{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions

		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//

														   //establecer el shader
		glUseProgram(programID);

		//pintar el VAO
		glBindVertexArray(VAO);

		//pintar VBO//
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//

		//pintar EBO//
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//

		//pintar con lineas
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//pintar con triangulos
		//glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);//

		// Swap the screen buffers
		while (!glfwWindowShouldClose(window)) {
			glBindVertexArray(VAO);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glfwSwapBuffers(window);
		}
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

	/*}*/
	// liberar la memoria de los VAO, EBO y VBO

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

