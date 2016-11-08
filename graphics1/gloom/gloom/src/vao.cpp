#include "vao.hpp"

unsigned int createVertexArrayObject(
	float* vertexCoordinates,
	unsigned int lengthVertices,
	unsigned int* indices,
	unsigned int lengthIndices, 
	float* colors, 
	unsigned int lengthColors) 
{
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