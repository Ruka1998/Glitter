#version 330 core

out vec4 fragColor;

in vec3 ourColor;

uniform float greenColor;

void main()
{
	fragColor = vec4(0.0f, greenColor, 0.0f, 1.0f);
}