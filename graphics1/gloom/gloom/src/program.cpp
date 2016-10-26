// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"


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

	float vertices[] = { -0.3, -0.5, 0.0, 0.3, -0.5, 0.0, 0.0, 0.5, 0.0,
						-0.7, 0.95, 0.0, -0.8, 0.4, 0.0, -0.3, 0.9, 0.0,
						0.3, -0.05, 0.0, 0.5, -0.07, 0.0, 0.5, 0.4, 0.0,
						0.15, 0.8, 0.0, 0.3, 0.85, 0.0, 0.2, 1.0, 0.0,
						-0.7, -0.99, 0.0, -0.2, -0.8, 0.0, -0.8, -0.1, 0,0};

	float vert[] = { 0.0, 0.8, 0.0, -0.2, 0.4, 0.0,	// v0 v1
					0.2, 0.4, 0.0, -0.4, 0.0, 0.0,	// v2 v3
					0.0, 0.0, 0.0, 0.4, 0.0, 0.0,	// v4 v5
					-0.6, -0.4, 0.0, -0.2, -0.4, 0.0, // v6 v7
					0.2, -0.4, 0.0, 0.6, -0.4, 0.0 }; // v8 v9

	float vertices_2[] = { 0.1, 0.1, 0.0, 0.5, 0.1, 0.0, 0.1, 0.5, 0.0 };

	float colors[] = { 1.0, 0.0, 0.0, 1.0, 
					1.0, 0.5, 0.0, 1.0,
					1.0, 0.0, 0.5, 1.0,
					1.0, 1.0, 0.0, 1.0,
					0.5, 0.5, 0.5, 1.0,
					0.5, 0.0, 1.0, 1.0,
					0.0, 1.0, 0.0, 1.0,
					0.0, 1.0, 0.5, 1.0,
					0.0, 0.5, 1.0, 1.0,
					0.0, 0.0, 1.0, 1.0 };

	int indexes[] = { 0, 1, 2, 1, 3, 4, 2, 4, 5, 3, 6, 7, 4, 7, 8, 5, 8, 9};

	// Call VAO-function
	unsigned int arrayId = createVertexArrayObject(vert, sizeof(vert) / sizeof(*vert), indexes, sizeof(indexes) / sizeof(*indexes), colors, sizeof(colors)/sizeof(*colors));

	// Create SHADERS

	Gloom::Shader shader;
	// These paths ain't pretty at all but we couldn't find the root of this project and desperate times calls for desperate measures..
	shader.attach("c:/users/alice/documents/github/tdt4195-gvb/graphics1/gloom/gloom/shaders/simple.vert");
	shader.attach("c:/users/alice/documents/github/tdt4195-gvb/graphics1/gloom/gloom/shaders/simple.frag");
	shader.link();


	// Rendering Loop
	while (!glfwWindowShouldClose(window))
	{
		// Clear colour and depth buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Activate the shader
		shader.activate();

		// Draw your scene here
		glDrawElements(GL_TRIANGLES, 21, GL_UNSIGNED_INT, 0);

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
	// Use escape key for terminating the GLFW window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}


unsigned int createVertexArrayObject(float* vertexCoordinates, unsigned int lengthVertices, int* indices, unsigned int lengthIndices, float* colors, unsigned int lengthColors) {
	/* VertexCoordinates is assumed to contain coordinates for a triangle on the form (x, y, z). */

	// Create a VAO, with ID stored in arrayId and bind it
	unsigned int arrayId = 0;
	glGenVertexArrays(1, &arrayId);
	glBindVertexArray(arrayId);

	// Create a buffer with ID stored in bufferId and bind it
	unsigned int coordBufferId = 0;
	glGenBuffers(1, &coordBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, coordBufferId);

	// Give the buffer some data
	glBufferData(GL_ARRAY_BUFFER, lengthVertices * sizeof(float), vertexCoordinates, GL_STATIC_DRAW);

	// Define how the data is structured
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);
	glEnableVertexAttribArray(0);

	// Creating and binding the color-buffer
	unsigned int colorsBufferId = 0;
	glGenBuffers(1, &colorsBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, colorsBufferId);

	// Give the color-buffer its data
	glBufferData(GL_ARRAY_BUFFER, lengthColors * sizeof(float), colors, GL_STATIC_DRAW);

	// Define attribute pointers. The color-buffer has index 1 (location=1).
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(1);

	// Create and bind an index buffer
	unsigned int indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	
	// Give the index buffer some data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, lengthIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	return arrayId;
}