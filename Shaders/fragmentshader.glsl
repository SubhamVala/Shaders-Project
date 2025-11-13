#version 460 core


out vec4 FragColor;

// takes in from vertexShader
in vec3 normal;
in vec3 posInWS;
in vec2 uv;
in vec3 tan;
in mat3 TBN;

uniform vec3 viewPos;
uniform vec3 cubeColor;

// Floor Uniforms
uniform vec3 floorColor;
uniform float floorSpecStrength;

// Directional Light uniforms
uniform vec3 lightColor;
uniform vec3 lightDirection;

// Point light Uniforms
uniform vec3 plightPosition;
uniform vec3 plightColor;
uniform vec3 pAttentuation;

uniform float ambientFactor;
uniform float shine;

// SpotLight Uniforms
uniform vec3 slightPosition;
uniform vec3 slightColour;
uniform vec3 sAttentuation;
uniform vec3 sDirection;
uniform vec2 sRadii;
uniform int useNM;
uniform int useDL;
uniform int usePL;
uniform int useSL;

// Material properties
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2D normalMap;

vec3 viewDir = normalize(viewPos - posInWS);	// PosInWS from VertexShader.
vec3 ld = normalize(-lightDirection);          // negated -lightDirection, so you get fragmentshader -> light
vec3 sd = normalize(-sDirection);             // negated -sDirection
vec3 n = normalize(normal);						 // n = normalized surface normal.


//foward declared functions, for void main.
vec3 getDirectionalLight();  
vec3 getPointLight();
vec3 getSpotLight();

void main() {

	// if Q is pressed then it will turn the normal mapping off.
	if(useNM==0) {
	n = texture(normalMap, uv).rgb;
	n = n * 2.0 - 1.0;
	n = normalize(TBN * n);
	}

	// Shows all the lights.
	vec3 result = getDirectionalLight();
	result += getPointLight() + getSpotLight();
	FragColor = vec4(result, 1.0);
}


// Vec3 function for the light.
vec3 getDirectionalLight() {     

	// texture for the objects and speculars
	vec3 objCol = texture(diffuseMap, uv).rgb ; 
	float specStrength = texture(specularMap, uv).r;

	// ambient
	vec3 ambient = objCol * lightColor * ambientFactor;			//AMBIENT!!!

	// diffuse
	float diffuseFactor = dot(n, ld) ;  // negated lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f) ;      // ensures diffuseFactor is not a negative.
	vec3 diffuse = objCol * lightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong, Specular

	vec3 h = normalize(ld + viewDir);	//negated lightDirection 
	float specLevel = dot(n, h) ; 
	specLevel = max(specLevel, 0.0) ;				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = lightColor * specLevel * specStrength;               //SPECULAR!

	// if key is pressed then turns off directional light.
	if (useDL==0) 
	{
		return ambient + diffuse + specular;				//BLINN PHONG!!!
	}
}

vec3 getPointLight() {

	// texture for the objects and speculars
	vec3 objCol = texture(diffuseMap, uv).rgb ; 
	float specStrength = texture(specularMap, uv).r;

	// attn
	float distance = length(plightPosition - posInWS);
	float attn = 1.0 / (pAttentuation.x + (pAttentuation.y * distance) + (pAttentuation.z*(distance * distance)));

	float ambientFactor = 0.1;

	vec3 lightDir = normalize((plightPosition - posInWS));
	vec3 ambient = objCol * plightColor * ambientFactor;

	// BLINN PHONG
	// Diffuse

	float diffuseFactor = dot(n, lightDir);  // negate lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f);      // ensures diffuseFactor is not a negative.
	vec3 diffuse = objCol * plightColor * diffuseFactor;			//DIFFUSE!

	// Blinn Phong
	// Specular

	vec3 h = normalize(lightDir + viewDir);	//negate lightDirection again so you get fragmentshader -> light
	float specLevel = dot(n, h);
	specLevel = max(specLevel, 0.0);				// ensures specLevel > 0/not negative.
	specLevel = pow(specLevel, shine);				// raises the specLevel to the power of shine.
	vec3 specular = plightColor * specLevel * specStrength;               //SPECULAR!

	diffuse = diffuse * attn;
	specular = specular * attn;

	// if button pressed then turns off pointlight
	if(usePL==0) {
	return diffuse + specular + ambient;
	}
	

}

vec3 getSpotLight() {

	// texture for the objects and speculars
	vec3 objCol = texture(diffuseMap, uv).rgb ; 
	float specStrength = texture(specularMap, uv).r;

	float ambientFactor = 0.05;

	vec3 sLightDir = normalize((sDirection));
	vec3 lightDir = normalize((viewPos - posInWS));     
	vec3 ambient = objCol * slightColour * ambientFactor;

	float distance = length(slightPosition - posInWS);
	float attn = 1.0 / (sAttentuation.x + (sAttentuation.y * distance) + (sAttentuation.z * (distance * distance)));

	
	// BLINN PHONG
	// Diffuse
	float diffuseFactor = dot(n, sd);  // negate lightdirection
	diffuseFactor = max(diffuseFactor, 0.0f);      // ensures diffuseFactor is not a negative.
	vec3 diffuse = objCol * slightColour * diffuseFactor;			//DIFFUSE!

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

	// if the button is pressed, it will turn off spot light.
	if(useSL== 0) {
		return diffuse + specular + ambient;
	}
}