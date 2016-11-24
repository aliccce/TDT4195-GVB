#include "vao.hpp"
#include "checkerboard.hpp"
#include <io.h>


Board::Board(unsigned int n, unsigned int m)
{
	this->n = n;
	this->m = m;
	this->boardId = createBoard();
}


unsigned int Board::createBoard()
{
	/* Creates a nxm checkered board with 0.1*0.1 squares, starting in upper left corner. 
	It is made on the xz plane, meaning that the world needs to be tilted for the board to show.
	Each square consists of two triangles, made with four nodes.
	
	Returns a VAO with vertices and colors in the VBO */
	int n = this->n;
	int m = this->m;


	const int numOfValues = n * m * 4 * 3;			// n*m squares with four coordinates, each with three values (to build two triangles)
	const int numOfIndices = n * m * 2 * 3;		// n*m squares with two triangles consisting of three corners
	float* vertices = new float[numOfValues];
	unsigned int* indices = new unsigned int[numOfIndices];
	float* colors = new float[numOfValues];

	const float delta = 0.2;
	float x = -1.0;
	float y = 0.0;
	float z = -1.0;
	int index = 0;		// Used for indices
	int indexVertex = 0;
	int vertex = 0;		// Used for counting coordinates
	int colorindex = 0;	// Color index

	float r = 0.0;
	float g = 0.0;
	float b = 1.0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			/* Colors */
			/* All coordinates in the same square will have the same color */
			for (int i = 0; i < 4; i++) {
				colors[colorindex] = r;
				colors[colorindex + 1] = g;
				colors[colorindex + 2] = b;
				colorindex += 3;
			}

			/* Colors for next square: */
			// If m is even, and we're on the last column, then colors shouldn't change.
			if (!(j == m - 1 && m % 2 == 0)) {
				if (r == 1.0) {
					r = 0.0;
					b = 1.0;
				}
				else {
					r = 1.0;
					b = 0.0;
				}
			}


			/* Indices */

			/* First triangle */

			indices[index] = indexVertex;
			indices[index + 1] = indexVertex + 2;
			indices[index + 2] = indexVertex + 1;

			/* Second triangle */
			indices[index + 3] = indexVertex + 1;
			indices[index + 4] = indexVertex + 2;
			indices[index + 5] = indexVertex + 3;
			index += 6;
			indexVertex += 4;

			/* Coordinates */
			/* Upper left corner */

			vertices[vertex] = x;
			vertices[vertex + 1] = y;
			vertices[vertex + 2] = z;
			vertex += 3;
			x += delta;

			/* Upper right corner */
			vertices[vertex] = x;
			vertices[vertex + 1] = y;
			vertices[vertex + 2] = z;
			vertex += 3;
			x -= delta;
			z += delta;

			/* Lower left corner */
			vertices[vertex] = x;
			vertices[vertex + 1] = y;
			vertices[vertex + 2] = z;
			vertex += 3;
			x += delta;

			/* Lower right corner */
			vertices[vertex] = x;
			vertices[vertex + 1] = y;
			vertices[vertex + 2] = z;
			vertex += 3;
			z -= delta;	// Readying z for next loop


		}

		x = -1.0;
		z += delta;
	}
	unsigned int vao = createVertexArrayObject(vertices, numOfValues, indices, numOfIndices, colors, numOfValues);
	return vao;

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;
}

