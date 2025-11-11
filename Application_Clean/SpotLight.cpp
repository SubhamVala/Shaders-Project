#include "Lights/SpotLight.h"
#include "Lights/Light.h"

SpotLight::SpotLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants, glm::vec3 dir, glm::vec2 radii) :

	PointLight(colour, position, constants),
	m_direction(dir),
	m_radii(radii)
{}

void SpotLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("slightColour", m_colour);
	shader->setVec3("slightPosition", m_position);
	shader->setVec3("sAttentuation", m_constants);
	shader->setVec2("sRadii", m_radii);
	shader->setVec3("sDirection", m_direction);
}
