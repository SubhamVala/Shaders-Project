#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNom;
layout(location = 2) in vec2 aUv;
layout(location = 3) in vec3 aTan;

// creates the Model, view, project matrix.
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// outs the vectors for fragment shader to go in.
out vec2 uv;
out vec3 tan;
out vec3 normal;
out vec3 posInWS;	// passes position in world space to the fragmentshader.
out mat3 TBN;

void main(){

	normal = mat3(transpose(inverse(Model))) * aNom;
	uv = aUv;
	tan = aTan;

	// calculates the TBN matrix.
	vec3 T = (Model * vec4(aTan, 0.0)).xyz;
	vec3 N = normal;
	vec3 B = normalize(cross(T,N));
	TBN = mat3(T, B, N);

		vec4 worldSpace = Model * vec4(aPos, 1.0);			  // the vertex in world space as vec4.
	posInWS = worldSpace.xyz;							 // the vertex in world space as vec3.
	gl_Position = Projection * View * worldSpace;         // already multiplied model matrix (Model * V).
}