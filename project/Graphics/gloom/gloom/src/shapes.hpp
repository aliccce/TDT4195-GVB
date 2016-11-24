#include "glm/mat4x4.hpp"

#define HEXAGON_COORDINATES 7
#define HEXAGON_TRIANGLES 6
#define TRIANGLE 3
#define THREE_VALUES 3
#define TINY_TRIANGLE_SCALE 0.7
#define SHADE 0.1

#ifndef PI 
	#define PI 3.14159265
#endif


class Shape
{
	int row;
	int col;
	int shapeType;
	float centerX;
	float centerY;

public:

	unsigned int vaoID;
	glm::mat4x4 modelMatrix;

	void setRow(int i) { row = i; }
	void setCol(int j) { col = j; }
	void setType(int type) { shapeType = type; }
	void setCenterX(float x) { centerX = x; }
	void setCenterY(float y) { centerY = y; }
	void setVaoID(unsigned int id) { vaoID = id; }

	int getRow() { return row; }
	int getCol() { return col; }
	int getType() { return shapeType; }
	float getCenterX() { return centerX; }
	float getCenterY() { return centerY; }
	unsigned int getId() { return vaoID; }

	void makeShape();
	void model();

};


unsigned int createPolygon(int n, float r, float g, float b, int quadrants = 4, float height = 0.15);
unsigned int createTriangle(float r, float g, float b, float height = 0.15);
unsigned int createParallellogram(float r, float g, float b, float skew = 0.4, float height = 0.15);
unsigned int createStar(float r, float g, float b, float height = 0.15);
unsigned int createA(float r, float g, float b, float height = 0.15);

void createTriangleVertices(float* vertices, float scale);
void moveTriangle(float* triangle, float distance);
void fillColors(float* colors, size_t length, float r, float g, float b);

void extrude(float bufferVertices[], size_t bvLen,
	unsigned int bufferIndices[], size_t biLen,
	float vertices[], size_t vLen,
	unsigned int indices[], size_t iLen, float height, int startOnOne);

float toRadians(float angleDegrees);
void switchPlaces(float *a, size_t index1, size_t index2);




