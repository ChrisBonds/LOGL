#version 460

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objColor; //alpha blending
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseStrength = max(dot(n, lightDir), 0.0);
	vec3 diffuse = lightColor * diffuseStrength; 
	vec3 ambient = lightColor * ambientStrength;
	vec3 result = ambient * objColor + diffuse * objColor;
	FragColor = vec4(result, 1.0);
}