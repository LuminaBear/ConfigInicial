//Martinez Perez Isaac Tadeo
//Gpo 1
//320281589

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f;

//Dedos
float pulgar1 = 0.0f, pulgar2 = 0.0f, pulgar3 = 0.0f;
float indice1 = 0.0f, indice2 = 0.0f, indice3 = 0.0f;
float medio1 = 0.0f, medio2 = 0.0f, medio3 = 0.0f;
float anular1 = 0.0f, anular2 = 0.0f, anular3 = 0.0f;
float menique1 = 0.0f, menique2 = 0.0f, menique3 = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Modelado jerarquico - Isaac Tadeo Martinez Perez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model Antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		//================ PULGAR =================
		//Falange A
		model = glm::translate(modelTemp2, glm::vec3(0.1f, -0.25f, 0.45f)); //sale del costado de la palma
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 0.0f, 1.0f)); //orientacion natural
		model = glm::rotate(model, glm::radians(pulgar1), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange B
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pulgar2), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.28f, 0.22f));
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange C
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pulgar3), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.25f, 0.2f));
		color = glm::vec3(0.0f, 0.5f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//================ DEDO INDICE =================
		//Falange A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.2f));
		model = glm::rotate(model, glm::radians(indice1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.28f, 0.22f));
		color = glm::vec3(0.9f, 0.8f, 0.2f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(indice2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.45f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.26f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(indice3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.23f, 0.18f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//================ DEDO MEDIO =================
		//Falange A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, 0.0f));
		model = glm::rotate(model, glm::radians(medio1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.55f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 0.3f, 0.25f));
		color = glm::vec3(0.3f, 1.0f, 0.3f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange B
		model = glm::translate(modelTemp, glm::vec3(0.55f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(medio2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.28f, 0.22f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange C
		model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(medio3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.75f, 0.25f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//================ DEDO ANULAR =================
		//Falange A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.35f, -0.2f));
		model = glm::rotate(model, glm::radians(anular1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.28f, 0.22f));
		color = glm::vec3(1.0f, 0.4f, 0.4f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(anular2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.45f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.26f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange C
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(anular3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.23f, 0.18f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//================ DEDO MEÑIQUE =================
		//Falange A
		model = glm::translate(modelTemp2, glm::vec3(0.25f, 0.32f, -0.4f));
		model = glm::rotate(model, glm::radians(menique1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.25f, 0.2f));
		color = glm::vec3(0.6f, 0.6f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange B
		model = glm::translate(modelTemp, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(menique2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.7f, 0.23f, 0.18f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Falange C
		model = glm::translate(modelTemp, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(menique3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.55f, 0.2f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 float clamp(float value, float min, float max) {
	 if (value < min) return min;
	 if (value > max) return max;
	 return value;
 }

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		hombro += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		hombro -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		codo += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		codo -= 0.18f;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 muneca += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 muneca -= 0.18f;

	 //================ PULGAR =================
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
	 {
		 //Pulgar
		 pulgar1 -= 0.25f;
		 pulgar2 -= 0.25f;
		 pulgar3 -= 0.25f;
	 }
	 if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	 {
		 //Pulgar
		 pulgar1 += 0.25f;
		 pulgar2 += 0.25f;
		 pulgar3 += 0.25f;
	 }

	 //================ INDICE =================
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	 {
		 //Indice
		 indice1 += 0.25f;
		 indice2 += 0.25f;
		 indice3 += 0.25f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	 {
		 //Indice
		 indice1 -= 0.25f;
		 indice2 -= 0.25f;
		 indice3 -= 0.25f;
	 }

	 //================ MEDIO =================
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	 {
		 //Medio
		 medio1 += 0.25f;
		 medio2 += 0.25f;
		 medio3 += 0.25f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	 {
		 //Medio
		 medio1 -= 0.25f;
		 medio2 -= 0.25f;
		 medio3 -= 0.25f;
	 }

	 //================ ANULAR =================
	 if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	 {
		 //Anular
		 anular1 += 0.25f;
		 anular2 += 0.25f;
		 anular3 += 0.25f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	 {
		 //Anular
		 anular1 -= 0.25f;
		 anular2 -= 0.25f;
		 anular3 -= 0.25f;
	 }

	 //================ MEÑIQUE =================
	 if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	 {
		 //Menique
		 menique1 += 0.25f;
		 menique2 += 0.25f;
		 menique3 += 0.25f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	 {
		 //Menique
		 menique1 -= 0.25f;
		 menique2 -= 0.25f;
		 menique3 -= 0.25f;
	 }

	 if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	 {
		 //Pulgar
		 pulgar1 -= 0.25f;
		 pulgar2 -= 0.25f;
		 pulgar3 -= 0.25f;
		 //Indice
		 indice1 += 0.18f;
		 indice2 += 0.18f;
		 indice3 += 0.18f;
		 //Medio
		 medio1 += 0.18f;
		 medio2 += 0.18f;
		 medio3 += 0.18f;
		 //Anular
		 anular1 += 0.18f;
		 anular2 += 0.18f;
		 anular3 += 0.18f;
		 //Meñique
		 menique1 += 0.18f;
		 menique2 += 0.18f;
		 menique3 += 0.18f;
	 }

	 if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	 {
		 //Pulgar
		 pulgar1 += 0.25f;
		 pulgar2 += 0.25f;
		 pulgar3 += 0.25f;
		 //Indice
		 indice1 -= 0.18f;
		 indice2 -= 0.18f;
		 indice3 -= 0.18f;
		 //Medio
		 medio1 -= 0.18f;
		 medio2 -= 0.18f;
		 medio3 -= 0.18f;
		 //Anular
		 anular1 -= 0.18f;
		 anular2 -= 0.18f;
		 anular3 -= 0.18f;
		 //Meñique
		 menique1 -= 0.18f;
		 menique2 -= 0.18f;
		 menique3 -= 0.18f;
	 }

	 // Restricciones naturales del brazo
	 hombro = clamp(hombro, -90.0f, 90.0f);
	 codo = clamp(codo, 0.0f, 145.0f);
	 muneca = clamp(muneca, -70.0f, 70.0f);

	 //================ LIMITES PULGAR =================
	 pulgar1 = clamp(pulgar1, -25.0f, 10.0f);
	 pulgar2 = clamp(pulgar2, -45.0f, 20.0f);
	 pulgar3 = clamp(pulgar3, -65.0f, 30.0f);

	 //================ LIMITES INDICE =================
	 indice1 = clamp(indice1, -50.0f, 0.0f);
	 indice2 = clamp(indice2, -84.0f, 0.0f);
	 indice3 = clamp(indice3, -64.0f, 0.0f);

	 //================ LIMITES MEDIO =================
	 medio1 = clamp(medio1, -50.0f, 0.0f);
	 medio2 = clamp(medio2, -84.0f, 0.0f);
	 medio3 = clamp(medio3, -64.0f, 0.0f);

	 //================ LIMITES ANULAR =================
	 anular1 = clamp(anular1, -50.0f, 0.0f);
	 anular2 = clamp(anular2, -84.0f, 0.0f);
	 anular3 = clamp(anular3, -64.0f, 0.0f);

	 //================ LIMITES MEÑIQUE =================
	 menique1 = clamp(menique1, -50.0f, 0.0f);
	 menique2 = clamp(menique2, -84.0f, 0.0f);
	 menique3 = clamp(menique3, -64.0f, 0.0f);
}