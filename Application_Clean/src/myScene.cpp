#pragma once
#include "myScene.h";

myScene::myScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	MakeVAO();
}

void myScene::MakeVAO() 
{
	glCreateBuffers(1, &VBO);
	glNamedBufferStorage(VBO, sizeof(float) * 9, vertexData , GL_DYNAMIC_STORAGE_BIT);

	glCreateVertexArrays(1, &VAO);

	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3);

	glEnableVertexArrayAttrib(VAO, 0);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

	glVertexArrayAttribBinding(VAO, 0, 0);
}

void myScene::update(float dt) {
	m_camera->update(dt);
	render();
}

void myScene::render() 
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}