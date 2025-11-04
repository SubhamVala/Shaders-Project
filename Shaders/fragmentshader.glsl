#version 460 core

out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;
uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightDirection;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;


vec3 n = normalize(normal);						  // n = normalized surface normal.
vec3 viewDir = normalize(viewPos - posInWS);	// PosInWS from VertexShader.

vec3 getDirectionalLight();  //foward declared functions, for void main.

void main() {

	vec3 result = getDirectionalLight();
	FragColor = vec4(result, 1.0);
}


// Vec3 function for the light.

vec3 getDirectionalLight() {      
		// ambient
	vec3 ambient = cubeColor * lightColor * ambientFactor;			//AMBIENT!!!

	// diffuse
	float diffuseFactor = dot(n, -lightDirection) ;  // negate lightdirection for lambertslaw.
	diffuseFactor = max(diffuseFactor, 0.0f) ;      // ensures diffuseFactor is not a negative.
	vec3 diffuse = cubeColor * lightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong, Specular

	vec3 h = normalize(-lightDirection + viewDir);	//negate lightDirection again so you get fragmentshader -> light
	float specLevel = dot(n, h) ; 
	specLevel = max(specLevel, 0.0) ;				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = lightColor * specLevel * specStrength;               //SPECULAR!

	return ambient + diffuse + specular;				//BLINN PHONG!!!
}

