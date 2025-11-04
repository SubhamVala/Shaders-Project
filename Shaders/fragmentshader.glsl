#version 460 core

out vec4 FragColor;

in vec3 normal;
in vec3 posInWS;

vec3 viewPos = vec3(0.0,0.0,0.8);
vec3 cubeColor = vec3(0.1,0.2,0.3);
vec3 lightColor = vec3(1.0f);
vec3 lightDirection = vec3(-1.0f,-1.0f,-1.0f);
vec3 n = normalize(normal);						  // n = normalized surface normal.
vec3 viewDir = normalize(viewPos - posInWS);	// PosInWS from VertexShader.

float ambientFactor = 0.5;
float shine = 10.0f;
float specStrength = 0.9f;

vec3 getDirectionalLight();

void main() {

	vec3 result = getDirectionalLight();
	FragColor = vec4(result, 1.0);
}


vec3 getDirectionalLight() {      //vec3 function for the light.
	// ambient
	vec3 ambient = cubeColor * lightColor * ambientFactor;			//AMBIENT!!!

	// diffuse
	float diffuseFactor = dot(n, -lightDirection) ;  // negate lightdirection for lambertslaw.
	diffuseFactor = max(diffuseFactor, 0.0f) ;      // ensures diffuseFactor is not a negative.
	vec3 diffuse = cubeColor * lightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong Specular

	vec3 h = normalize(-lightDirection + viewDir);	//negate lightDirection again so you get fragmentshader -> light
	float specLevel = dot(n, h) ; 
	specLevel = max(specLevel, 0.0) ;				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = lightColor * specLevel * specStrength;               //SPECULAR!

	return ambient + diffuse + specular;				//BLINN PHONG!!!!
}

