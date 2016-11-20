
#define HEXAGON_COORDINATES 7
#define HEXAGON_TRIANGLES 6
#define TRIANGLE 3
#define THREE_VALUES 3
#define TINY_TRIANGLE_SCALE 0.7

#ifndef PI 
	#define PI 3.14159265
#endif


unsigned int createPolygon(int n, float r, float g, float b, int quadrants=4);
unsigned int createTriangle(float r, float g, float b);
unsigned int createParallellogram(float r, float g, float b, float skew=0.4);
unsigned int createStar(float r, float g, float b);
unsigned int createA(float r, float g, float b);

void createTriangleVertices(float* vertices, float scale);
void moveTriangle(float* triangle, float distance);
void fillColors(float* colors, int length, float r, float g, float b);



float toRadians(float angleDegrees);