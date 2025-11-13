#include "Plane.h"
#include "myScene.h"
#include "Lights/Light.h"

Plane::Plane(float shine, int diffuseTexture, int specularTexture, int normalTexture) :

	m_diffuseTexture(diffuseTexture),
	m_shine(shine),
	m_specularTexture(specularTexture)	,
	m_normalTexture(normalTexture)
{
	makeVAO();
	resetTransform();
}

void Plane::setPlaneMaterialValues(Shader* shader)
{
	shader->use();
	shader->setFloat("shine", m_shine);
	shader->setInt("diffuseMap", 0);
	shader->setInt("specularMap", 1);
	shader->setInt("normalMap", 2);
	
	glBindTextureUnit(0, m_diffuseTexture);
	glBindTextureUnit(1, m_specularTexture);
	glBindTextureUnit(2, m_normalTexture);

}

void Plane::makeVAO()
{
	glCreateBuffers(1, &m_VBO); // creates vertex buffer object
	glNamedBufferStorage(m_VBO, sizeof(float) * floorVertexData.size(), floorVertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &m_EBO); // creates an element buffer object.
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * floorIndices.size(), floorIndices.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &m_VAO); // creates vertex array object.
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * 11);
	glVertexArrayElementBuffer(m_VAO, m_EBO); // Adding EBO TO VBO

	// creates attributes for positon, normals, uvs and tangent.
	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);
	glEnableVertexArrayAttrib(m_VAO, 2);
	glEnableVertexArrayAttrib(m_VAO, 3);

	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO, 2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO, 3, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float));
	
	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);
	glVertexArrayAttribBinding(m_VAO, 2, 0);
	glVertexArrayAttribBinding(m_VAO, 3, 0);
}