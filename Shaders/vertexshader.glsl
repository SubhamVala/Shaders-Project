#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNom;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


out vec3 normal;
out vec3 posInWS;	// passes position in world space to the fragmentshader.

void main(){

	normal = mat3(transpose(inverse(Model))) * aNom;

	vec4 worldSpace = Model * vec4(aPos, 1.0);			  // the vertex in world space as vec4.
	posInWS = worldSpace.xyz;							 // the vertex in world space as vec3.
	gl_Position = Projection * View * worldSpace;         // already multiplied model matrix (Model * V).

}