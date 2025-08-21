#version 460

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objColor; //alpha blending
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = lightColor * ambientStrength;

	vec3 n = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	//float diff = max(dot(n, lightDir), 0.0);
	float diff = clamp(dot(n, lightDir), 0.0, 1.0);
	vec3 diffuse = lightColor * diff;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = (ambient + diffuse + specular) * objColor;
	FragColor = vec4(result, 1.0);
}