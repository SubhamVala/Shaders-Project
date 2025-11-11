#include <Lights/PointLight.h>

PointLight::PointLight(glm::vec3 colour, glm::vec3 position, glm::vec3 constants) :
	Light(colour),
	m_position(position),
	m_constants(constants)
{}

void PointLight::setLightUniforms(Shader* shader)
{
	shader->use();
	shader->setVec3("plightColor", m_colour);
	shader->setVec3("plightPosition", m_position);
	shader->setVec3("pAttentuation", m_constants);
}