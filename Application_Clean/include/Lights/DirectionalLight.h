#pragma once
#pragma once

#include "Shader.h"
#include "Light.h"

class DirectionalLight : public Light {

public:
	//Contructed needs a colour, direction and ambient value.
	DirectionalLight(glm::vec3 colour, glm::vec3 direction, float ambient = 0.5);
	~DirectionalLight() {};
	//sets light uniforms in the shader
	void setLightUniforms(Shader* shader);

	//getters and setters
	void setDirection(glm::vec3& dir) { m_direction = dir; }
	void setAmbient(float& a) { m_ambientFactor = a; }
	glm::vec3& setDirection() { return m_direction; }
	float& setAmbient() { return m_ambientFactor; }


private:
	glm::vec3 m_direction;
	float m_ambientFactor;

};