
#include <iostream>
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtx/transform.hpp> 
#include <glm/vec3.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include "PATH.hpp"
#include "sphere.hpp"

using namespace std;

// Creates a VAO containing a sphere with a resolution specified by slices and layers, with a radius of 1.

unsigned int createCircleVAO(unsigned int slices, unsigned int layers) {

	// Calculating how large our buffers have to be
	// The sphere is defined as layers containing rectangles. Each rectangle requires us to draw two triangles
	const unsigned int PRIMITIVES_PER_RECTANGLE = 2;
	const unsigned int triangleCount = slices * layers * PRIMITIVES_PER_RECTANGLE;

	// Allocating buffers
	const unsigned int VERTICES_PER_TRIANGLE = 3;
	const unsigned int COMPONENTS_PER_VERTEX = 3;
	float* vertices = new float[triangleCount * VERTICES_PER_TRIANGLE * COMPONENTS_PER_VERTEX];
	unsigned int* indices = new unsigned int[triangleCount * VERTICES_PER_TRIANGLE];

	// Slices require us to define a full revolution worth of triangles.
	// Layers only requires angle varying between the bottom and the top (a layer only covers half a circle worth of angles)
	const float degreesPerLayer = 180.0 / (float) layers;
	const float degreesPerSlice = 360.0 / (float) slices;

	// Keeping track of the triangle index in the buffer. 
	// This implementation is fairly naive in the sense that it does not reuse vertices with the index buffer.
	int i = 0;

	// Constructing the sphere one layer at a time
	for (int layer = 0; layer < layers; layer++) {
		int nextLayer = layer + 1;

		// Angles between the vector pointing to any point on a particular layer and the negative z-axis
		float currentAngleZDegrees = degreesPerLayer * layer;
		float nextAngleZDegrees = degreesPerLayer * nextLayer;

		// All coordinates within a single layer share z-coordinates. 
		// So we can calculate those of the current and subsequent layer here.
		float currentZ = -cos(toRadians(currentAngleZDegrees));
		float nextZ = -cos(toRadians(nextAngleZDegrees));

		// The row of vertices forms a circle around the vertical diagonal (z-axis) of the sphere.
		// These radii are also constant for an entire layer, so we can precalculate them.
		float radius = sin(toRadians(currentAngleZDegrees));
		float nextRadius = sin(toRadians(nextAngleZDegrees));

		// Now we can move on to constructing individual slices within a layer
		for (int slice = 0; slice < slices; slice++) {
			
			// The direction of the start and the end of the slice in the xy-plane
			float currentSliceAngleDegrees = slice * degreesPerSlice;
			float nextSliceAngleDegrees = (slice + 1) * degreesPerSlice;

			// Determining the direction vector for both the start and end of the slice
			float currentDirectionX = cos(toRadians(currentSliceAngleDegrees));
			float currentDirectionY = sin(toRadians(currentSliceAngleDegrees));

			float nextDirectionX = cos(toRadians(nextSliceAngleDegrees));
			float nextDirectionY = sin(toRadians(nextSliceAngleDegrees));

			// Now we have all information needed to create triangles

			// Triangle 1
			
			vertices[3 * i + 0] = radius * currentDirectionX;
			vertices[3 * i + 1] = radius * currentDirectionY;
			vertices[3 * i + 2] = currentZ;

			indices[i] = i;
			i++;

			vertices[3 * i + 0] = radius * nextDirectionX;
			vertices[3 * i + 1] = radius * nextDirectionY;
			vertices[3 * i + 2] = currentZ;

			indices[i] = i;
			i++;

			vertices[3 * i + 0] = nextRadius * nextDirectionX;
			vertices[3 * i + 1] = nextRadius * nextDirectionY;
			vertices[3 * i + 2] = nextZ;

			indices[i] = i;
			i++;

			// Triangle 2

			vertices[3 * i + 0] = radius * currentDirectionX;
			vertices[3 * i + 1] = radius * currentDirectionY;
			vertices[3 * i + 2] = currentZ;

			indices[i] = i;
			i++;

			vertices[3 * i + 0] = nextRadius * nextDirectionX;
			vertices[3 * i + 1] = nextRadius * nextDirectionY;
			vertices[3 * i + 2] = nextZ;

			indices[i] = i;
			i++;

			vertices[3 * i + 0] = nextRadius * currentDirectionX;
			vertices[3 * i + 1] = nextRadius * currentDirectionY;
			vertices[3 * i + 2] = nextZ;

			indices[i] = i;
			i++;
		}
	}

	cout << *vertices;

	// Sending the created buffers over to OpenGL.
	// Don't forget to modify this to fit the function you created yourself!
	// You will have to include a file which contains the implementation of this function for this to work.
	const unsigned int num_of_colors = triangleCount * 4;
	float colors[200] = {0.0};

	unsigned int vao_id = createVertexArrayObject(vertices, sizeof(vertices) / sizeof(*vertices), indices, sizeof(indices) / sizeof(*indices), colors, 1);

	// Cleaning up after ourselves
	delete[] vertices;
	delete[] indices;
	

	return vao_id;
}

unsigned int createVertexArrayObject(float* vertexCoordinates, unsigned int lengthVertices, unsigned int* indices, unsigned int lengthIndices, float* colors, unsigned int lengthColors) {
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