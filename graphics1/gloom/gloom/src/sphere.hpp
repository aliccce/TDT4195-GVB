#pragma once

#include <math.h>
#include "SceneGraph.hpp"

unsigned int createCircleVAO(unsigned int slices, unsigned int layers);
unsigned int createVertexArrayObject(float* vertexCoordinates, unsigned int lengthVertices, unsigned int* indices, unsigned int lengthIndices, float* colors, unsigned int lengthColors);