#pragma once
#include "Light.h"
#include "Shader.h"

class PointLight : public Light
{
public:
	PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants); // constructors for PointLight
	~PointLight() {};

	void setLightUniforms(Shader* shader); // sets the uniforms for the light

	void setConstants(glm::vec3& constants) { m_constants = constants; }
	void setPosition(glm::vec3& position) { m_position = position; }

	glm::vec3& getPosition() { return m_position; }
	glm::vec3& getConstants() { return m_constants; }


protected:
	glm::vec3 m_constants;
	glm::vec3 m_position;

};

