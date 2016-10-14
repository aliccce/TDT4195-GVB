#version 430 core

in vec3 position;

void main()
{
	float x = -position[0];
	float y = -position[1];
	float z = position[2];
    gl_Position = vec4(x, y, z, 1.0f);
}
