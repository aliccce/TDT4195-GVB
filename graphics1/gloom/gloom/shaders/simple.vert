#version 430 core

in vec3 position;

layout(location=1) in vec4 acolor;
layout(location=1) out vec4 vcolor;


void main()
{
    gl_Position = vec4(position, 1.0f);
	vcolor = acolor;
}
