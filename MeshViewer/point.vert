#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	gl_PointSize = 5.0;
}