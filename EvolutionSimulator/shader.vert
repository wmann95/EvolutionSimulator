#version 330 core

in vec3 vp;

uniform mat4 transform;
uniform mat4 scale;
uniform mat4 rotate;

void main()
{
	gl_Position = transform * scale * rotate * vec4(vp, 1.0);
}