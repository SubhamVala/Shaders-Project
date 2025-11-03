#version 460 core

layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aCol;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


out vec3 vertexColour;
void main(){
	/*vertexColour = aCol ;*/
	gl_Position = Projection * View * Model * vec4(aPos, 1.0) ;

}