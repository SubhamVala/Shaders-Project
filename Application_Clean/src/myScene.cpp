#pragma once
#include "myScene.h";

myScene::myScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	my_shader = new Shader("..\\Shaders\\vertexshader.glsl", "..\\Shaders\\fragmentshader.glsl");
	MakeVAO();
}

myScene::~myScene()
{
}

void myScene::MakeVAO() 
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);
	
	glCreateBuffers(1, &EBO);
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3);
	glVertexArrayElementBuffer(VAO, EBO);

	glEnableVertexArrayAttrib(VAO, 0);
	/*glEnableVertexArrayAttrib(VAO, 1);*/


	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	/*glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));*/

	glVertexArrayAttribBinding(VAO, 0, 0);
	/*glVertexArrayAttribBinding(VAO, 1, 0);*/
}

void myScene::update(float dt) {
	m_camera->update(dt);
	render();
}

void myScene::render() 
{
	m_model = glm::mat4(1.0f);

	//camera

	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	my_shader->use();

	//uniforms
	my_shader->setMat4("View", m_view);
	my_shader->setMat4("Projection", m_projection);
	my_shader->setMat4("Model", m_model);
	
	

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0) ;
	//glDrawArrays(GL_TRIANGLES, 0, 6);

	
	
	
}