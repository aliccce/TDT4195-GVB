#include "shapes.hpp"
#include <stdio.h>	/* printf */
#include <string.h>
#include <stdlib.h> /* malloc */
#include <math.h>	/* sin, cos, fabs */
#include <vao.hpp>

unsigned int createPolygon(int n, float r, float g, float b, int quadrants, float height) {
	/* Returns a float array with coordinates on the form x, y, z of a polygon with n edges. 
	Quadrants say how many qadrants you want to draw. Default is set to four. 
	Note that n should be a multiple of 4 for this to work properly. */

	/* This is a formula that calculates how many vertices are needed, taking into account the amount of quadrants and edges. */
	const int SHAPE_VERTICES = ((quadrants * n) / 4 + 2);
	const int SHAPE_COMPONENTS = SHAPE_VERTICES * THREE_VALUES;	// Each vertice consists of three values.
	const int SHAPE_INDICES = ((quadrants * n) / 4) * TRIANGLE;					// Three values for each triangle - one triangle for each edge.
	const int EXTRUDE_COMPONENTS = SHAPE_COMPONENTS * 2;
	const int EXTRUDE_INDICES = SHAPE_VERTICES * 2 * TRIANGLE;


	float* vertices = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];	
	float* colors = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	unsigned int* indices = new unsigned int[SHAPE_INDICES + EXTRUDE_INDICES];	

	/**** CALCULATING SHAPE ****/

	const float rotate_angle = toRadians(2.0 * 180.0 / n);

	/* Creating center node */

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	float angle = -rotate_angle;

	for (int index = 0; index < SHAPE_COMPONENTS; index += 3)
	{
		vertices[index] = x;
		vertices[index + 1] = y;
		vertices[index + 2] = z;

		printf("(%f, %f, %f)\n", x, y, z);

		colors[index] = r;
		colors[index + 1] = g;
		colors[index + 2] = b;
		
		/* Calculating vertex for next loop */
		angle += rotate_angle;
		x = cos(angle);
		z = -sin(angle);
		// y doesn't change
	}

	int index = 0;

	for (int i = 1; i <= (quadrants * n)/4; i++)
	{
		indices[index] = 0;
		indices[index + 1] = i;
		indices[index + 2] = (i == n) ? 1 : (i + 1);	// if i == n: set value to 1 else i + 1.
		index += 3;
	}

	unsigned int startOnOne = (quadrants == 4) ? 1 : 0;
	extrude(vertices + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS, 
			indices + SHAPE_INDICES, EXTRUDE_INDICES, 
			vertices, SHAPE_COMPONENTS,
			indices, SHAPE_INDICES, 
			height, startOnOne);

	fillColors(colors + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		(r < SHADE) ? 0 : r - SHADE,
		(g < SHADE) ? 0 : g - SHADE,
		(b < SHADE) ? 0 : b - SHADE);

	for (int i = 0; i < SHAPE_COMPONENTS + EXTRUDE_COMPONENTS; i += 3) {
		printf("i: %d --- (%f, %f, %f)\n", i/3, vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	for (int i = 0; i < SHAPE_INDICES + EXTRUDE_INDICES; i += 3) {
		printf("triangle %d, %d, %d\n", indices[i], indices[i + 1], indices[i + 2]);
	}

	unsigned int vao = createVertexArrayObject(vertices, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS, 
												indices, SHAPE_INDICES + EXTRUDE_COMPONENTS, 
												colors, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}


unsigned int createTriangle(float r, float g, float b, float height) 
{
	

	/* Num of components for shape and extruded stuff */
	
	const int SHAPE_COMPONENTS = 3 * THREE_VALUES;
	const int SHAPE_INDICES = TRIANGLE;
	const int EXTRUDE_COMPONENTS = 2 * SHAPE_COMPONENTS;
	const int EXTRUDE_INDICES = 2 * 3 * TRIANGLE;
	const int EXTRUDE_OFFSET = 3;

	/*
	const int NUM_OF_VERTEX_VALUES = 3 * THREE_VALUES;		// Three vertices with three values.
	const int NUM_OF_INDICES = TRIANGLE;	*/			// One triangle
	
	float vertices[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	float colors[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	unsigned int indices[SHAPE_INDICES + EXTRUDE_INDICES];
	
	/**** CALCULATING SHAPES ****/
	createTriangleVertices(vertices, 1.0);
	fillColors(colors, SHAPE_COMPONENTS, r, g, b);
	
	for (int index = 0; index < SHAPE_INDICES; index += 1)
	{
		indices[index] = index;
	}
	/*
	float* extrudeVertices = new float[NUM_OF_VERTEX_VALUES * 2];
	unsigned int* extrudeIndices = new unsigned int[NUM_OF_VERTEX_VALUES * 2];
	float* extrudeColors = new float[NUM_OF_VERTEX_VALUES * 2];*/

	/**** CALCULATING EXTRUTION ****/
	extrude(vertices + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS, 
			indices + SHAPE_INDICES, EXTRUDE_INDICES, 
			vertices, SHAPE_COMPONENTS, 
			indices, SHAPE_INDICES, 
			0.1, 0);

	fillColors(colors + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		(r < SHADE) ? 0 : r - SHADE,
		(g < SHADE) ? 0 : g - SHADE,
		(b < SHADE) ? 0 : b - SHADE);


	unsigned int vao = createVertexArrayObject(vertices, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS, 
												indices, SHAPE_INDICES + EXTRUDE_INDICES,
												colors, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS);

	// Cleanup

	for (int i = 0; i < SHAPE_COMPONENTS + EXTRUDE_COMPONENTS; i += 3) {
		printf("(%f, %f, %f)\n", vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	for (int i = 0; i < SHAPE_INDICES + EXTRUDE_INDICES; i += 3) {
		printf("triangle %d, %d, %d\n", indices[i], indices[i + 1], indices[i + 2]);
	}


	return vao;
}    


unsigned int createParallellogram(float r, float g, float b, float skew, float height) {
	const int SHAPE_VERTICES = 4;
	const int SHAPE_COMPONENTS = SHAPE_VERTICES * THREE_VALUES;		// Four vertices with three values.
	const int SHAPE_INDICES = 2 * TRIANGLE;				// Two triangles
	const int EXTRUDE_COMPONENTS = SHAPE_COMPONENTS * 2;
	const int EXTRUDE_INDICES = SHAPE_VERTICES * 2 * TRIANGLE;

	float* vertices = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	float* colors = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	unsigned int* indices = new unsigned int[SHAPE_INDICES + EXTRUDE_INDICES];

	float x[] = { 0.6, -0.6, -0.6, 0.6 };
	float z[] = { -1.0, -1.0, 1.0, 1.0 };

	for (int index = 0; index < SHAPE_COMPONENTS; index += THREE_VALUES)
	{
		vertices[index] = x[index / THREE_VALUES] - skew * z[index / THREE_VALUES];
		vertices[index + 1] = 0.0;
		vertices[index + 2] = z[index / THREE_VALUES];


		printf("(%f, %f, %f)\n", vertices[index], vertices[index + 1], vertices[index + 2]);

		colors[index] = r;
		colors[index + 1] = g;
		colors[index + 2] = b;
	}

	int index = 0;

	for (int i = 1; i < 3; i++)
	{
		indices[index] = 0;
		indices[index + 1] = i;
		indices[index + 2] = i + 1;
		index += TRIANGLE;
	}

	extrude(vertices + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		indices + SHAPE_INDICES, EXTRUDE_INDICES,
		vertices, SHAPE_COMPONENTS,
		indices, SHAPE_INDICES,
		height, 0);

	fillColors(colors + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		(r < SHADE) ? 0 : r - SHADE,
		(g < SHADE) ? 0 : g - SHADE,
		(b < SHADE) ? 0 : b - SHADE);



	unsigned int vao = createVertexArrayObject(vertices, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS, 
		indices, SHAPE_INDICES + EXTRUDE_INDICES, 
		colors, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}


unsigned int createA(float r, float g, float b, float height) {
	
	float* bigTriangle = new float[(size_t) TRIANGLE * THREE_VALUES];
	float* tinyTriangle = new float[(size_t) TRIANGLE * THREE_VALUES];
	createTriangleVertices(bigTriangle, 1.0);
	createTriangleVertices(tinyTriangle, 0.7);

	const unsigned int SHAPE_VERTICES = 6;
	const size_t SHAPE_COMPONENTS = SHAPE_VERTICES * THREE_VALUES;		// Six vertices with three values.
	const size_t SHAPE_INDICES = 4 * TRIANGLE;
	const size_t EXTRUDE_COMPONENTS = SHAPE_COMPONENTS * 2;
	const size_t EXTRUDE_INDICES = SHAPE_VERTICES * 2 * TRIANGLE;

	float* vertices = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	float* colors = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	unsigned int* indices = new unsigned int[SHAPE_INDICES + EXTRUDE_INDICES];


	/**** CALCULATING SHAPE ****/

	unsigned int temp[] = { 1, 2, 3, 1, 3, 0, 3, 4, 5, 3, 5, 0 };	// Not dynamic, do not delete this
	memcpy(indices, temp, SHAPE_INDICES * sizeof(unsigned int));

	/* The tiny triangle is moved down to the same baseline as the big */
	float distance = fabs(bigTriangle[5] - tinyTriangle[5]);
	moveTriangle(tinyTriangle, distance);

	memcpy(vertices, bigTriangle, 6 * sizeof(float));
	memcpy(vertices + 6, tinyTriangle, 9 * sizeof(float));
	memcpy(vertices + 6 + 9, bigTriangle + 6, 3 * sizeof(float));
	switchPlaces(vertices, 2, 3);

	delete[] tinyTriangle;
	delete[] bigTriangle;	// Done with these

	fillColors(colors, SHAPE_COMPONENTS, r, g, b);

	/***** EXTRUDE *****/

	extrude(vertices + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		indices + SHAPE_INDICES, EXTRUDE_INDICES,
		vertices, SHAPE_COMPONENTS,
		indices, SHAPE_INDICES,
		height, 0);

	fillColors(colors + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		(r < SHADE) ? 0 : r - SHADE,
		(g < SHADE) ? 0 : g - SHADE,
		(b < SHADE) ? 0 : b - SHADE);

	unsigned int vao = createVertexArrayObject(vertices, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS,
		indices, SHAPE_INDICES + EXTRUDE_INDICES,
		colors, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS);

	for (int i = 0; i < SHAPE_COMPONENTS + EXTRUDE_COMPONENTS; i += 3) {
		printf("(%f, %f, %f)\n", vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	for (int i = 0; i < SHAPE_INDICES + EXTRUDE_INDICES; i += 3) {
		printf("triangle %d, %d, %d\n", indices[i], indices[i + 1], indices[i + 2]);
	}
	
	delete[] vertices;
	delete[] colors;
	delete[] indices;
	
	return vao;
}


unsigned int createStar(float r, float g, float b, float height) {
	const int SHAPE_VERTICES = 11;
	const int SHAPE_COMPONENTS = SHAPE_VERTICES * THREE_VALUES;	// n = Three values for each edge and three for the centroid vertex.
	const int SHAPE_INDICES = 10 * TRIANGLE;					// Three values for each triangle - one triangle for each edge.
	const int EXTRUDE_COMPONENTS = 2 * SHAPE_COMPONENTS;
	const int EXTRUDE_INDICES = SHAPE_VERTICES * 2 * TRIANGLE;

	float* vertices = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	float* colors = new float[SHAPE_COMPONENTS + EXTRUDE_COMPONENTS];
	unsigned int* indices = new unsigned int[SHAPE_INDICES + EXTRUDE_INDICES];

	const float rotate_angle = toRadians(72.0);
	const float scale = 0.5;

	/* Creating center node */

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	float v_angle = toRadians(-18.0);
	float point_angle = toRadians(18.0);

	for (int index = 0; index < SHAPE_COMPONENTS; index += THREE_VALUES)
	{
		if ((index / THREE_VALUES) % 2 == 0)	/* Pointing vertices */
		{
			vertices[index] = x;
			vertices[index + 1] = y;
			vertices[index + 2] = z;

			/* Calculating for non-pointing vertices */
			v_angle += rotate_angle;
			x = scale * cos(v_angle);
			z = scale * -sin(v_angle);
			// y doesn't change
		}
		else
		{
			vertices[index] = x;
			vertices[index + 1] = y;
			vertices[index + 2] = z;

			/* Calculating for non-pointing vertices */
			point_angle += rotate_angle;
			x = cos(point_angle);
			z = -sin(point_angle);
			// y doesn't change
		}
	}

	fillColors(colors, SHAPE_COMPONENTS, r, g, b);

	int index = 0;

	for (int i = 1; i < 10; i += 2)
	{
		// Inner triangle
		indices[index] = 0;
		indices[index + 1] = i;
		indices[index + 2] = (i == 9) ? 1 : i + 2;
		index += 3;

		// outer triangle
		indices[index] = i;
		indices[index + 1] = i + 1;
		indices[index + 2] = (i == 9) ? 1 : i + 2;
		index += 3;
	}


	extrude(vertices + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		indices + SHAPE_INDICES, EXTRUDE_INDICES,
		vertices, SHAPE_COMPONENTS,
		indices, SHAPE_INDICES,
		height, 1);

	fillColors(colors + SHAPE_COMPONENTS, EXTRUDE_COMPONENTS,
		(r < SHADE) ? 0 : r - SHADE,
		(g < SHADE) ? 0 : g - SHADE,
		(b < SHADE) ? 0 : b - SHADE);

	unsigned int vao = createVertexArrayObject(vertices, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS,
		indices, SHAPE_INDICES + EXTRUDE_INDICES,
		colors, SHAPE_COMPONENTS + EXTRUDE_COMPONENTS);

	for (int i = 0; i < SHAPE_COMPONENTS + EXTRUDE_COMPONENTS; i += 3) {
		printf("(%f, %f, %f)\n", vertices[i], vertices[i + 1], vertices[i + 2]);
	}

	for (int i = 0; i < SHAPE_INDICES + EXTRUDE_INDICES; i += 3) {
		printf("triangle %d, %d, %d\n", indices[i], indices[i + 1], indices[i + 2]);
	}
	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}






void extrude(float bufferVertices[], size_t bvLen, 
			unsigned int bufferIndices[], size_t biLen,
			float vertices[], size_t vLen, 
			unsigned int indices[], size_t iLen, float height, int startOnOne)
{
	/* Extrudes an object drawn in xz-plane in y-plane. The object itself is lifted by height. */
	/* Copying all coordinates in vertices to the buffer */

	memcpy(bufferVertices, vertices, vLen * sizeof(float));

	/* Lifting all shapes along y axis with height */
	for (size_t index = 1; index < vLen; index += 3) 
	{
		vertices[index] += height;
	}

	/* Doing another copy of the lifted vertices to the buffer */
	memcpy(bufferVertices + vLen, vertices, vLen * sizeof(float));

	/* We have all we need, so now we have to add indices to our index buffer
	(not to mistaken with a VBO index buffer) */
	unsigned int SHAPE_VERTICES = vLen / 3;		// Number of nodes in shape
	size_t index;
	size_t i = SHAPE_VERTICES + startOnOne;

	for (index = 0; index < biLen; index += 6)	/* Calculating two triangles at a time */
	{
		if (i == SHAPE_VERTICES * 2 - 1)
		{
			/* Lower triangle */
			bufferIndices[index] = i;
			bufferIndices[index + 1] = SHAPE_VERTICES + startOnOne;
			bufferIndices[index + 2] = i + startOnOne + 1;

			printf("Triangle %d, %d, %d\n", bufferIndices[index], bufferIndices[index + 1], bufferIndices[index + 2]);

			/* Upper triangle */
			bufferIndices[index + 3] = i;
			bufferIndices[index + 4] = i + startOnOne + 1;
			bufferIndices[index + 5] = i + SHAPE_VERTICES;
		} 
		else
		{
			/* Lower triangle */
			bufferIndices[index] = i;
			bufferIndices[index + 1] = i + 1;
			bufferIndices[index + 2] = i + SHAPE_VERTICES + 1;

			printf("Triangle %d, %d, %d\n", bufferIndices[index], bufferIndices[index + 1], bufferIndices[index + 2]);

			/* Upper triangle */
			bufferIndices[index + 3] = i;
			bufferIndices[index + 4] = i + SHAPE_VERTICES + 1;
			bufferIndices[index + 5] = i + SHAPE_VERTICES;
			
			printf("Triangle %d, %d, %d\n", bufferIndices[index], bufferIndices[index + 1], bufferIndices[index + 2]);
		}
		i += 1;
	}
}






void moveTriangle(float triangle[], float distance) {
	/* Triangle is moved along the z axis.
	Assumnes triangle is an array with 9 values on the form {x0, y0, z0, ... } */
	for (size_t i = 2; i < THREE_VALUES * TRIANGLE; i += 3)
	{
		triangle[i] += distance;
	}
}


void createTriangleVertices(float vertices[], float scale) {
	/* Vertices must be of size 9! */
	const size_t NUM_OF_VERTEX_VALUES = TRIANGLE * THREE_VALUES;		// Three vertices with three values.

	float angle = toRadians(90.0);
	const float rotate_angle = toRadians(120.0);
	float x = 0.0;
	float z = -scale;

	for (size_t index = 0; index < NUM_OF_VERTEX_VALUES; index += 3)
	{
		vertices[index] = x;
		vertices[index + 1] = 0.0;
		vertices[index + 2] = z;
		angle += rotate_angle;
		x = scale * cos(angle);
		z = scale * -sin(angle);
	}
}


void fillColors(float colors[], size_t length, float r, float g, float b) {
	for (size_t index = 0; index < length; index += 3)
	{	
		printf("Fill colors: %d / %d\n", index, length);
		colors[index] = r;
		colors[index + 1] = g;
		colors[index + 2] = b;
		printf("rgb = (%f, %f, %f)\n", colors[index], colors[index + 1], colors[index + 2]);
	}
	printf("Fill colors: Done\n");
}


float toRadians(float angleDegrees) {
	return angleDegrees * (PI / 180.0);
}


void switchPlaces(float *a, size_t index1, size_t index2)
{
	index1 *= THREE_VALUES;
	index2 *= THREE_VALUES;
	float temp[3];
	memcpy(temp, a + index1, THREE_VALUES * sizeof(float));
	memcpy(a + index1, a + index2, THREE_VALUES * sizeof(float));
	memcpy(a + index2, temp, THREE_VALUES * sizeof(float));
}

