#include "shapes.hpp"
#include <stdio.h>	/* printf */
#include <string.h>
#include <math.h>	/* sin, cos, fabs */
#include <vao.hpp>

unsigned int createPolygon(int n, float r, float g, float b, int quadrants) {
	/* Returns a float array with coordinates on the form x, y, z of a polygon with n edges. 
	Quadrants say how many qadrants you want to draw. Default is set to four. 
	Note that n should be a multiple of 4 for this to work properly. */

	/* This is a formula that calculates how many vertices are needed, taking into account the amount of quadrants and edges. */
	const int NUM_OF_VERTEX_VALUES = ((quadrants * n) / 4 + 2) * THREE_VALUES;	// Each vertice consists of three values.
	const int NUM_OF_INDICES = ((quadrants * n) / 4) * TRIANGLE;					// Three values for each triangle - one triangle for each edge.


	float* vertices = new float[NUM_OF_VERTEX_VALUES];	
	float* colors = new float[NUM_OF_VERTEX_VALUES];
	unsigned int* indices = new unsigned int[NUM_OF_INDICES];	

	const float rotate_angle = toRadians(2.0 * 180.0 / n);

	/* Creating center node */

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	float angle = -rotate_angle;

	for (int index = 0; index < NUM_OF_VERTEX_VALUES; index += 3)
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

	unsigned int vao = createVertexArrayObject(vertices, NUM_OF_VERTEX_VALUES, indices, NUM_OF_INDICES, colors, NUM_OF_VERTEX_VALUES);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}


unsigned int createTriangle(float r, float g, float b) {
	const int NUM_OF_VERTEX_VALUES = 3 * THREE_VALUES;		// Three vertices with three values.
	const int NUM_OF_INDICES = TRIANGLE;				// One triangle

	float* vertices = new float[NUM_OF_VERTEX_VALUES];
	float* colors = new float[NUM_OF_VERTEX_VALUES];
	unsigned int* indices = new unsigned int[NUM_OF_INDICES];

	createTriangleVertices(vertices, 1.0);
	fillColors(colors, NUM_OF_VERTEX_VALUES, r, g, b);

	for (int index = 0; index < NUM_OF_VERTEX_VALUES; index += 3)
	{
		indices[index / 3] = index / 3;
	}

	unsigned int vao = createVertexArrayObject(vertices, NUM_OF_VERTEX_VALUES, indices, NUM_OF_INDICES, colors, NUM_OF_VERTEX_VALUES);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}


unsigned int createParallellogram(float r, float g, float b, float skew) {
	const int NUM_OF_VERTEX_VALUES = 4 * THREE_VALUES;		// Four vertices with three values.
	const int NUM_OF_INDICES = 2 * TRIANGLE;				// Two triangles

	float* vertices = new float[NUM_OF_VERTEX_VALUES];
	float* colors = new float[NUM_OF_VERTEX_VALUES];
	unsigned int* indices = new unsigned int[NUM_OF_INDICES];

	float x[] = { 0.6, -0.6, -0.6, 0.6 };
	float z[] = { -1.0, -1.0, 1.0, 1.0 };

	for (int index = 0; index < NUM_OF_VERTEX_VALUES; index += THREE_VALUES)
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

	unsigned int vao = createVertexArrayObject(vertices, NUM_OF_VERTEX_VALUES, indices, NUM_OF_INDICES, colors, NUM_OF_VERTEX_VALUES);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}





unsigned int createA(float r, float g, float b) {
	/*
	float* bigTriangle = new float[TRIANGLE * THREE_VALUES];
	float* tinyTriangle = new float[TRIANGLE * THREE_VALUES];
	createTriangleVertices(bigTriangle, 1.0);
	createTriangleVertices(tinyTriangle, 0.7);*/

	const int NUM_OF_VERTEX_VALUES = 6 * THREE_VALUES;		// Six vertices with three values.
	const int NUM_OF_INDICES = 4 * TRIANGLE;
	
	float vertices[] = { 0.00000, 1.000000, 0.000000, 0.000000, 0.550000, 0.000000, 
						-0.866025, -0.500000, 0.000000, -0.606218, -0.500000, 0.000000, 
						0.866026, -0.500000, 0.000000, 0.606218, -0.500000, 0.000000 };

	float colors[] = { 1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0,
		1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0 };

	unsigned int indices[] = { 2, 3, 1, 2, 1, 0, 1, 4, 0, 1, 5, 4 };

	/*
	const float distance = fabs(bigTriangle[4] - tinyTriangle[4]);
	printf("distance %f", distance);
	moveTriangle(tinyTriangle, distance);
	
	int index = 0;
	float x, y, z;
	
	for (int i = 0; i < TRIANGLE * THREE_VALUES; i += 3)
	{
		memcpy(vertices + index, bigTriangle + i, 3 * sizeof(float));

		printf("%f, %f, %f, ", vertices[index], vertices[index + 1], vertices[index + 2]);
		
		index += 3;

		memcpy(vertices + index, tinyTriangle + i, 3 * sizeof(float));
		printf("%f, %f, %f, ", vertices[index], vertices[index + 1], vertices[index + 2]);

		index += 3;
	}
	
	delete[] tinyTriangle;
	delete[] bigTriangle;*/

	//fillColors(colors, NUM_OF_VERTEX_VALUES, r, g, b);

	//printf("rgb = %f, %f, %f\n", colors[0], colors[1], colors[2]);


	unsigned int vao = createVertexArrayObject(vertices, NUM_OF_VERTEX_VALUES, indices, NUM_OF_INDICES, colors, NUM_OF_VERTEX_VALUES);
	printf("Do we reach this?\n");

	// Cleanup
	/*  n nn mn 
	delete[] vertices;
	delete[] indices;
	delete[] colors;
	*/
	return vao;
}


unsigned int createStar(float r, float g, float b) {
	const int NUM_OF_VERTEX_VALUES = 11 * THREE_VALUES;	// n = Three values for each edge and three for the centroid vertex.
	const int NUM_OF_INDICES = 10 * TRIANGLE;					// Three values for each triangle - one triangle for each edge.


	float* vertices = new float[NUM_OF_VERTEX_VALUES];
	float* colors = new float[NUM_OF_VERTEX_VALUES];
	unsigned int* indices = new unsigned int[NUM_OF_INDICES];

	const float rotate_angle = toRadians(72.0);
	const float scale = 0.5;

	/* Creating center node */

	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

	float v_angle = toRadians(-18.0);
	float point_angle = toRadians(18.0);

	for (int index = 0; index < NUM_OF_VERTEX_VALUES; index += THREE_VALUES)
	{
		if ((index / THREE_VALUES) % 2 == 0)	/* Pointing vertices */
		{
			vertices[index] = x;
			vertices[index + 1] = y;
			vertices[index + 2] = z;

			/* Calculating for non-pointing vertices */
			v_angle += rotate_angle;
			x = scale * cos(v_angle);
			y = scale * sin(v_angle);
			// z doesn't change
		}
		else
		{
			vertices[index] = x;
			vertices[index + 1] = y;
			vertices[index + 2] = z;

			/* Calculating for non-pointing vertices */
			point_angle += rotate_angle;
			x = cos(point_angle);
			y = sin(point_angle);
			// z doesn't change
		}
	}

	fillColors(colors, NUM_OF_VERTEX_VALUES, r, g, b);

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


	unsigned int vao = createVertexArrayObject(vertices, NUM_OF_VERTEX_VALUES, indices, NUM_OF_INDICES, colors, NUM_OF_VERTEX_VALUES);

	// Cleanup
	delete[] vertices;
	delete[] indices;
	delete[] colors;

	return vao;
}


void moveTriangle(float* triangle, float distance) {
	/* Triangle is moved along the y axis.
	Assumnes triangle is an array with 9 values on the form {x0, y0, z0, ... } */
	for (int i = 1; i < THREE_VALUES * TRIANGLE; i += 3)
	{
		triangle[i] -= distance;
	}

}


void createTriangleVertices(float* vertices, float scale) {
	/* Vertices must be of size 9! */
	const int NUM_OF_VERTEX_VALUES = TRIANGLE * THREE_VALUES;		// Three vertices with three values.

	float angle = toRadians(90.0);
	const float rotate_angle = toRadians(120.0);
	float x = 0.0;
	float y = scale;

	for (int index = 0; index < NUM_OF_VERTEX_VALUES; index += 3)
	{
		vertices[index] = x;
		vertices[index + 1] = y;
		vertices[index + 2] = 0.0;
		angle += rotate_angle;
		x = scale * cos(angle);
		y = scale * sin(angle);
	}
}


void fillColors(float* colors, int length, float r, float g, float b) {
	for (int index = 0; index < length; index += THREE_VALUES) {
		colors[index] = r;
		colors[index + 1] = g;
		colors[index + 2] = b;
	}
}


float toRadians(float angleDegrees) {
	return angleDegrees * (PI / 180.0);
}

