#version 460

out vec4 FragColor;

uniform vec3 objColor; //alpha blending
uniform vec3 lightColor;

void main()
{
	FragColor = vec4(objColor * lightColor, 1.0);
}