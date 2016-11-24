// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "PATH.hpp"
#include "camera.hpp"

#include "readBoard.hpp"


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

	Board *board = new Board(5, 8);
	readFile(board, "C:/Users/alice/Documents/GitHub/tdt4195-gvb/project/Graphics/gloom/gloom/src/example.txt");
	printf("board size %d", board->pieces.size());
	
	for (size_t index = 0; index < board->pieces.size(); index++)
	{
		Shape *piece = board->pieces[index];
		printf("\n%d,     ", piece->vaoID);
		piece->makeShape();
		piece->model();
		printf("%d\n", piece->vaoID);

	}



	// Create SHADERS
	Gloom::Shader shader;
	// Paths are defined in the file PATHS.cpp
	shader.attach(SIMPLE_VERT);
	shader.attach(SIMPLE_FRAG);
	shader.link();

	
	shader.activate();

	matrix *= (glm::mat4x4) glm::perspective(45.0f, (float)windowWidth / (float)windowHeight, 0.01f, 100.0f);
	matrix *= (glm::mat4x4) glm::lookAt(glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	

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
		glBindVertexArray(board->boardId);
		glDrawElements(GL_TRIANGLES, 999, GL_UNSIGNED_INT, 0);

		for (Shape *piece : board->pieces)
		{
			glBindVertexArray(piece->vaoID);
			glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(matrix * piece->modelMatrix));

			glDrawElements(GL_TRIANGLES, 999, GL_UNSIGNED_INT, 0);
		}



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
