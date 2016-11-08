#include "colors.hpp"
#include "sceneGraph.hpp"


float* generateColorArray(int node_number, float red, float green, float blue, float varying_degree)
{
	/* Generates an array filled with rgba-values, varying based on the input color */


	const int num_of_values = node_number * 4; // This will correspond to RGBA
	float* colors = new float[num_of_values];
	int plus = 1;

	for (int i = 0; i < num_of_values; i++) {
		switch (i % 4) {
		case 0:
			colors[i] = getRandomValue(red, varying_degree);
			break;
		case 1:
			colors[i] = getRandomValue(green, varying_degree);
			break;
		case 2:
			colors[i] = getRandomValue(blue, varying_degree);
			break;
		case 3:
			colors[i] = 1.0;
			break;
		}

		if (colors[i] > 1.0) {
			colors[i] = 1.0;
		}
	}

	return colors;

}


float getRandomValue(float channel, float varying_degree) {
	return channel + varying_degree * random();
}