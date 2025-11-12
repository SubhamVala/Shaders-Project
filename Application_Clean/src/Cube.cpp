#include "Cube.h"
#include "myScene.h"

Cube::Cube(glm::vec3 col, float shine, float specStrength) : m_colour(col), m_shine(shine), m_specularStrength(specStrength)
{
	makeVAO();
	resetTranform();


}

Cube::~Cube()
{
}

void Cube::setCubeMaterialValues(Shader* shader)
{
	shader->use();
	shader->setVec3("cubeColor", m_colour);
	shader->setFloat("shine", m_shine);
	shader->setFloat("specStrength", m_specularStrength);
}

void Cube::rotate(float angle, glm::vec3 axis)
{
	m_transform = glm::rotate(m_transform, glm::radians(angle), axis);
}

void Cube::scale(float scaleFactor, glm::vec3 axis)
{
	m_transform = glm::scale(m_transform, glm::vec3(scaleFactor) * axis);
}

void Cube::translate(glm::vec3 translatation)
{
	m_transform = glm::translate(m_transform, translatation);
}

void Cube::makeVAO()
{
	glCreateBuffers(1, &m_VBO); // creates vertex buffer object
	glNamedBufferStorage(m_VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);

	glCreateBuffers(1, &m_EBO); // creates an element buffer object.
	glNamedBufferStorage(m_EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &m_VAO); // creates vertex array object.
	glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, sizeof(float) * 8);
	glVertexArrayElementBuffer(m_VAO, m_EBO); // Adding EBO TO VBO

	glEnableVertexArrayAttrib(m_VAO, 0);
	glEnableVertexArrayAttrib(m_VAO, 1);
	glEnableVertexArrayAttrib(m_VAO, 2);


	glVertexArrayAttribFormat(m_VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(m_VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(m_VAO, 2, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));


	glVertexArrayAttribBinding(m_VAO, 0, 0);
	glVertexArrayAttribBinding(m_VAO, 1, 0);
	glVertexArrayAttribBinding(m_VAO, 2, 0);
	

}