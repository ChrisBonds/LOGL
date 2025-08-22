#version 450
//NEEDS TEXTURES TO WORK PROPERLY DO THIS TOMORROW
precision highp float;

in vec3 aPos;
//in vec2 texcoord; not yet 
in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 modelTransposedInverse;

//out vec2 tc; not yet
out vec3 wfn; //fragment normal in world space
out vec3 vPos;

void main(){
	wfn = vec3(modelTransposedInverse * vec4(aNormal, 0.0));
	vec4 vPos4 = model * vec4(aPos, 1.0);
	vPos = vPos4.xyz / vPos4.w;
	gl_Position = projection * view * vPos4;
}
