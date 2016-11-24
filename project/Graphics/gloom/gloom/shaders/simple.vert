#version 430 core

layout(location=0) in vec3 position;

layout(location=1) in vec4 acolor;
layout(location=1) out vec4 vcolor;

uniform layout(location=2) mat4x4 matrix;

/* {{a, d, 0, 0}, {b, e, 0, 0}, {0, 0, 1, 0}, {c, f, 0, 1}} */


void main()
{
    gl_Position = matrix * vec4(position, 1.0f);
	vcolor = acolor;
}
