// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtx/transform.hpp> 
#include <glm/vec3.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include "PATH.hpp"
#include "camera.cpp"
#include "vao.cpp"
#include "sphere.hpp"

// Create camera-object
Camera camera = Camera(0.1f, 0.1f);

// Uniform matrix
glm::mat4x4 matrix(1); 

void runProgram(GLFWwindow* window)
{
	// Set GLFW callback mechanism(s)
	glfwSetKeyCallback(window, keyboardCallback);

	// Enable depth (Z) buffer (accept "closest" fragment)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Configure miscellaneous OpenGL settings
	glEnable(GL_CULL_FACE);

	// Set default colour after clearing the colour buffer
	glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

	// Set up your scene here (create Vertex Array Objects, etc.)


	float pyramid[] = { 0.0, -0.3, -0.3,		// back pyramid
						0.0, -0.3, -0.9,
						-0.6, -0.3, -0.9,
						-0.6, -0.3, -0.3,
						-0.3, 0.3, -0.6,

						0.7, -0.3, 0.3,		// front pyramid
						0.7, -0.3, -0.3,
						0.1, -0.3, -0.3,
						0.1, -0.3, 0.3,
						0.4, 0.3, 0.0 };


	float pyramid_colors[] = { 0.6, 0.2, 0.3, 1.0,
							0.3, 0.1, 0.5, 1.0,
							0.4, 0.2, 0.4, 1.0,
							1.0, 0.7, 0.2, 1.0,
							1.0, 0.9, 0.5, 1.0,

							0.6, 0.1, 0.4, 1.0,
							0.3, 0.1, 0.5, 1.0,
							0.6, 0.2, 0.3, 1.0,
							1.0, 0.7, 0.2, 1.0,
							1.0, 0.9, 0.5, 1.0 };


	unsigned int pyramid_indices[] = { 0, 1, 4,
							1, 2, 4,
							2, 3, 4,
							3, 0, 4,

							5, 6, 9,
							6, 7, 9,
							7, 8, 9,
							8, 5, 9};

	// Create sphere, and get its VAO-id
	unsigned int arrayId = createVertexArrayObject(pyramid, 30, pyramid_indices, 24, pyramid_colors, 40);

	//unsigned int arrayId = createCircleVAO(10, 5);


	// Create SHADERS
	Gloom::Shader shader;
	// These paths ain't pretty at all but we couldn't find the root of this project and desperate times calls for desperate measures..
	shader.attach(SIMPLE_VERT);
	shader.attach(SIMPLE_FRAG);

	shader.link();

	
	shader.activate();
	matrix *= (glm::mat4x4) glm::perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.01f, 100.0f);
	matrix *= (glm::mat4x4) glm::lookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	

	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear colour and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate the shader
		shader.activate();

		// Creating uniforms
		// Creating a glm identity matrix
		
		glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(matrix));

		// Bind and draw VAO
		glBindVertexArray(arrayId);
		glDrawElements(GL_TRIANGLES, 1000, GL_UNSIGNED_INT, 0);

		// Deactivate the shader
		shader.deactivate();

		// Handle other events
		glfwPollEvents();

		// Flip buffers
		glfwSwapBuffers(window);
	}

	shader.destroy();
}


void keyboardCallback(GLFWwindow* window, int key, int scancode,
	int action, int mods)
	
{	
	if (action == GLFW_PRESS || action == GLFW_REPEAT) 
	{
		// Use escape key for terminating the GLFW window
		if (key == GLFW_KEY_ESCAPE) { glfwSetWindowShouldClose(window, GL_TRUE); }

		// Camera movement
		else if (key == GLFW_KEY_RIGHT) { matrix *= camera.moveRight(); }
		else if (key == GLFW_KEY_LEFT) { matrix *= camera.moveLeft(); }
		else if (key == GLFW_KEY_UP) { matrix *= camera.moveForward(); }
		else if (key == GLFW_KEY_DOWN) { matrix *= camera.moveBackward(); }
		else if (key == GLFW_KEY_J)	{ matrix *= camera.moveUp(); }
		else if (key == GLFW_KEY_K)	{ matrix *= camera.moveDown(); }
		else if (key == GLFW_KEY_W)	{ matrix *= camera.lookUp(); }
		else if (key == GLFW_KEY_S)	{ matrix *= camera.lookDown(); }
		else if (key == GLFW_KEY_A)	{ matrix *= camera.lookLeft(); }
		else if (key == GLFW_KEY_D) { matrix *= camera.lookRight();	}
	}
}

/* Moving camera to the right
This is done by moving the elements left, and updating camera coordinates */


/* Moving camera to the left (by moving elements to the right) */



/* Look up

This is done by translating the camera to origo, rotating the camera about the x-axis, and then translating the camera back to it's position.
It is not actually the camera that is moved or rotated, but the elements - they are moved the same relative distance as would be needed to move the camera to
origo, then rotated about the camera (origo), and then they are moved back again.

It is rotated about the x-axis, which is a bit weird if your looking towards the right or the left - you will somehow spin instead.
*/

/* Look left - this is done the way as with look up and  look down, except it's rotated about the y-axis. */
