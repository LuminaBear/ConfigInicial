#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	float vertices[] = {
		// Triángulo 1 (cabeza)
		-0.26f, 0.85f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA CABEZA 0 
		-0.1f, 0.94f, 0.0f,   0.2f,0.8f,0.8f, //ARRIBA CABEZA 1
		 0.06f, 0.85f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA CABEZA 2
		-0.1f, 0.8f, 0.0f,   0.2f,0.8f,0.8f, //ABAJO CABEZA 3

		-0.4f, 0.90f, 0.0f,   0.4f, 0.4f, 0.4f, //IZQUIERDA LENTE 4
		-0.1f, 0.73f, 0.0f,   0.4f, 0.4f, 0.4f, //ABAJO LENTE 5
		 0.2f, 0.90f, 0.0f,   0.4f, 0.4f, 0.4f, //DERECHA LENTE 6

		-0.3f, 0.65f, 0.0f,   0.2f, 0.2f, 0.2f, //IZQUIERDA ABAJO LENTE 7
		 0.1f, 0.65f, 0.0f,   0.2f, 0.2f, 0.2f, //DERECHA ABAJO LENTE 8

		-0.24f, 0.6f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA BOCA 9
		 0.04f, 0.6f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA BOCA 10
		-0.1f, 0.55f, 0.0f,   0.2f,0.8f,0.8f, //ABAJO BOCA 11

		-0.20f, 0.63f, 0.0f,   0.0f,0.0f,0.0f, //IZQUIERDA SONRISA 12
		 0.0f, 0.63f, 0.0f,   0.0f,0.0f,0.0f, //DERECHA SONRISA 13
		-0.1f, 0.58f, 0.0f,   0.0f,0.0f,0.0f, //ABAJO SONRISA 14
		-0.1f, 0.60f, 0.0f,   0.0f,0.0f,0.0f, //ARRIBA SONRISA 15

		-0.12f, 0.68f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ IZQ ARRIBA 16
		-0.14f, 0.68f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ IZQ ARRIBA 17
		-0.12f, 0.64f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ IZQ ABAJO 18
		-0.08f, 0.68f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ DER ARRIBA 19
		-0.06f, 0.68f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ DER ARRIBA 20
		-0.08f, 0.64f, 0.0f,   0.0f,0.0f,0.0f, //NARIZ DER ABAJO 21
		
		-0.31f, 0.5f, 0.0f,   1.0f, 0.95f, 0.4f, //IZQUIERDA PECHO 22
		 0.11f, 0.5f, 0.0f,   1.0f, 0.95f, 0.4f, //DERECHA ARRIBA PECHO 23

		-0.24f, 0.2f, 0.0f,   1.0f, 0.95f, 0.4f, //IZQUIERDA ABAJO PECHO 24
		 0.04f, 0.2f, 0.0f,   1.0f, 0.95f, 0.4f, //DERECHA ABAJO PECHO 25
		-0.1f, 0.2f, 0.0f,   1.0f, 0.95f, 0.4f, //ABAJO ABAJO PECHO 26
		-0.1f, 0.5f, 0.0f,   0.2f,0.8f,0.8f, //ABAJO ARRIBA PECHO 27

		-0.37f, 0.4f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA ARRIBA MANO 28
		-0.34f, 0.27f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA ABAJO MANO 29
		 0.17f, 0.4f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA ARRIBA MANO 30
		 0.14f, 0.27f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA ABAJO MANO 31

		-0.1f, 0.8f, 0.0f,   0.4f, 0.4f, 0.4f, //ARRIBA LENTE 32

		-0.24f, 0.01f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA IZQ PATA 33
		-0.14f, 0.01f, 0.0f,   0.2f,0.8f,0.8f, //IZQUIERDA DER PATA 34
		 0.04f, 0.01f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA IZQ PATA 35
		-0.06f, 0.01f, 0.0f,   0.2f,0.8f,0.8f, //DERECHA DERE PATA 36


	};
	unsigned int indices[] = {
		11,28,29, //BRAZO DERECHO
		11,30,31, //BRAZO IZQUIERDO
		1,33,34, //PATA IZQUIERDA
		1,35,36, //PATA DERECHA
		1,22,23, //PECHO ARRIBA
		0,1,2, //CABEZA
		0,2,3, //CABEZA ABAJO
		0,9,3, //BOCA IZQ
		2,10,3, //BOCA DER
		9,10,3, //BOCA MEDIO
		9,10,11, //BOCA ABAJO
		4,5,32, //LENTE ARRIBA IZQ
		6,5,32, //LENTE ARRIBA DER
		4,7,5, //LENTE ABAJO IZQ
		6,8,5, //LENTE ABAJO DER
		12,14,15, //SONRISA IZQ
		13,14,15, //SONRISA DER
		16,17,18, //NARIZ DER
		19,20,21, //NARIZ IZQ
		22,24,26, //PECHO BAJO IZQ
		23,25,26, //PECHO BAJO DER
		22,23,26, //PECHO BAJO RELLENO

	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,2);
        //glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, 66,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}