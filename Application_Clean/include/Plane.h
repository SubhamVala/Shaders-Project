#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/common.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Shader.h"

class Plane
{
public:
	Plane(float shine, int diffuseTexture, int specularTexture, int normalTexture); // constructer, taking colour, shine and specular strength
	~Plane() {};
	void setPlaneMaterialValues(Shader* shader);
	void setTransform(Shader* shader) { shader->setMat4("Model", m_transform); }
	void resetTransform() { m_transform = glm::mat4(1.0); }  // resets model matrix

	// Getters
	unsigned int getVAO() { return m_VAO; }
	unsigned int getVBO() { return m_VBO; }
	unsigned int getEBO() { return m_EBO; }
	glm::mat4& getModelMatrix() { return m_transform; }
	unsigned int getIndicesCount() { return floorIndices.size(); }
	 
	void rotate(float angle, glm::vec3 axis);
	void scale(float scaleFactor, glm::vec3 axis);
	void translate(glm::vec3 translatation);
	

private:
	const float floorLevel = -2.0f;
	const float floorSize = 7.0f;
	void makeVAO();
	
	unsigned int m_VAO, m_VBO, m_EBO;
	glm::mat4 m_transform;

	// properties of the floor.
	float m_shine;
	unsigned int m_diffuseTexture;
	unsigned int m_specularTexture;
	unsigned int m_normalTexture;

	// geometry data.

	std::vector<float> floorVertexData = {
	-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,  0.0,0.0,  1.0f, 0.0f, 0.0f,
	 floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,  1.0,0.0,  1.0f, 0.0f, 0.0f,
	 floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0,  1.0,1.0,  1.0f, 0.0f, 0.0f,
	-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0,  0.0,1.0,  1.0f, 0.0f, 0.0f
	};
	std::vector<unsigned int> floorIndices = {
		3,2,1,
		3,1,0
	};


};
