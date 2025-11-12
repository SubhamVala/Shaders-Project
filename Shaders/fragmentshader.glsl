#version 460 core

out vec4 FragColor;
in vec3 normal;
in vec3 posInWS;

uniform vec3 viewPos;
uniform vec3 cubeColor;

// Directional Light uniforms
uniform vec3 lightColor;
uniform vec3 lightDirection;

// Point light Uniforms
uniform vec3 plightPosition;
uniform vec3 plightColor;
uniform vec3 pAttentuation;

uniform float ambientFactor;
uniform float shine;
uniform float specStrength;

// SpotLight Uniforms
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttentuation;
uniform vec3 sDirection;
uniform vec2 sRadii;


vec3 n = normalize(normal);						  // n = normalized surface normal.
vec3 viewDir = normalize(viewPos - posInWS);	// PosInWS from VertexShader.
vec3 ld = normalize(-lightDirection);         // negated -lightDirection, so you get fragmentshader -> light
vec3 sd = normalize(-sDirection);             // negated -sDirection

vec3 getDirectionalLight();  //foward declared functions, for void main.
vec3 getPointLight();
vec3 getSpotLight();

void main() {
	 
	vec3 result = getDirectionalLight() * 0;
	result += getSpotLight();
	FragColor = vec4(result, 1.0);
}


// Vec3 function for the light.

vec3 getDirectionalLight() {      
	// ambient
	vec3 ambient = cubeColor * lightColor * ambientFactor;			//AMBIENT!!!

	// diffuse
	float diffuseFactor = dot(n, ld) ;  // negated lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f) ;      // ensures diffuseFactor is not a negative.
	vec3 diffuse = cubeColor * lightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong, Specular

	vec3 h = normalize(ld + viewDir);	//negated lightDirection 
	float specLevel = dot(n, h) ; 
	specLevel = max(specLevel, 0.0) ;				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = lightColor * specLevel * specStrength;               //SPECULAR!

	return ambient + diffuse + specular;				//BLINN PHONG!!!
}

vec3 getPointLight() {

	// attn
	float distance = length(plightPosition - posInWS);
	float attn = 1.0 / (pAttentuation.x + (pAttentuation.y * distance) + (pAttentuation.z*(distance * distance)));

	float ambientFactor = 0.7;
	vec3 lightDir = normalize((plightPosition - posInWS));
	vec3 ambient = cubeColor * plightColor * ambientFactor;

	// BLINN PHONG
	// Diffuse

	float diffuseFactor = dot(n, lightDir);  // negate lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f);      // ensures diffuseFactor is not a negative.
	vec3 diffuse = cubeColor * plightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong
	// Specular

	vec3 h = normalize(lightDir + viewDir);	//negate lightDirection again so you get fragmentshader -> light
	float specLevel = dot(n, h);
	specLevel = max(specLevel, 0.0);				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = plightColor * specLevel * specStrength;               //SPECULAR!

	diffuse = diffuse * attn;
	specular = specular * attn;

	return diffuse + specular + ambient;

}

vec3 getSpotLight() {

	float ambientFactor = 0.3;

	vec3 sLightDir = normalize((slightPosition - posInWS));
	vec3 lightDir = normalize((viewPos - posInWS));     
	vec3 ambient = cubeColor * slightColour * ambientFactor;

	float distance = length(slightPosition - posInWS);
	float attn = 1.0 / (sAttentuation.x + (sAttentuation.y * distance) + (sAttentuation.z * (distance * distance)));

	
	// BLINN PHONG
	// Diffuse
	float diffuseFactor = dot(n, sd);  // negate lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f);      // ensures diffuseFactor is not a negative.
	vec3 diffuse = cubeColor * slightColour * diffuseFactor;			//DIFFUSE!

	// Blinn Phong,
	// Specular
	vec3 h = normalize(sd + viewDir);	//negate lightDirection again so you get fragmentshader -> light
	float specLevel = dot(n, h);
	specLevel = max(specLevel, 0.0);				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = slightColour * specLevel * specStrength;               //SPECULAR!
	

	diffuse = diffuse * attn;
	specular = specular * attn;


	//spot light
	//lightDir -> fragment to light, sLightdir is light to X, negate so both vectors point from light
	float theta = dot(-lightDir, normalize(sLightDir));
	float denom = (sRadii.x - sRadii.y);
	float intensity = (theta - sRadii.y) / denom;
	intensity = clamp(intensity, 0.0, 1.0);

	diffuse = diffuse * intensity;
	specular = specular * intensity;

	return diffuse + specular;
	

}