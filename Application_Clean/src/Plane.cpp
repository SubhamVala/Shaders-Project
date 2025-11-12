#include "Plane.h"
#include "myScene.h"
#include "Lights/Light.h"

Plane::Plane(glm::vec3 col, float shine, float specStrength) :

	m_floorColour(col),
	m_shine(shine),
	m_specularStrength(specStrength)	
{
	makeVAO();
	resetTransform();
}


void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("floorColor", m_floorColour);
	shader->setFloat("floorShine", m_shine);
	shader->setFloat("floorSpecStrength", m_specularStrength);

}

void Plane::makeVAO()
{
	glCreateBuffers(1, &m_VBO); // creates vertex buffer object
	glNamedBufferStorage(m_VBO, sizeof(float) * floorVertexData.size(), floorVertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &m_EBO); // creates an element buffer object.
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &m_VAO); // creates vertex array object.
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * 6);
	glVertexArrayElementBuffer(m_VAO, m_EBO); // Adding EBO TO VBO


	glEnableVertexArrayAttrib(m_VAO, 0);

	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	
	glVertexArrayAttribBinding(m_VAO, 0, 0);
}