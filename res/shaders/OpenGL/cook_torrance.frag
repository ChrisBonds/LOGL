#version 450 

#include "brdfing.glsl"

precision highp float;

out vec4 FragColor;

//in vec2 tc; nuh uh
in vec3 wfn;
in vec3 vPos;

//uniform sampler2D baseColorTexture; //albedo for dielectrics or F0 for metals 
//uniform sampler2D roughnessTexture;
//uniform sampler2D normalTexture;
//uniform sampler2D emissionTexture;
uniform float u_metallic; 
uniform float u_reflectance;
uniform float u_perpIrradiance; //default = 10
uniform vec4 u_lightColor; //might switch to vec3
uniform vec3 u_lightDir;
uniform vec3 u_camPos;

//use until configured with textures
uniform vec3 u_objColor;
uniform float u_roughness;
uniform vec4 u_emission;


void main(){
	//vec3 baseColor = rgb2lin(texture(baseColorTexture, tc).rgb); //uh oh
	//float roughness = texture(roughnessTexture, tc).r;
	//vec4 emission = texture(emissionTexture, tc);
	vec3 baseColor = u_objColor;
	float roughness = u_roughness;
	vec4 emission = u_emission;
	vec3 lightDir = normalize(-u_lightDir); //towards light
	vec3 viewDir = normalize(u_camPos - vPos);
	vec3 n = normalize(wfn);

	n = applyNormalMap(n, viewDir, tc);
	vec3 radiance = rgb2lin(emission.rgb);
	float irradiance = max(dot(lightDir, n), 0.0) * u_perpIrradiance;
	if(irradiance > 0.0){
		vec3 brdf = microfacetBRDF(lightDir, viewDir, n, u_metallic, u_roughness, baseColor, u_reflectance);
		radiance += brdf * irradiance * u_lightColor.rgb;
	}
	FragColor.rgb = lin2rgb(radiance);
	FragColor.a = 1.0;

}
