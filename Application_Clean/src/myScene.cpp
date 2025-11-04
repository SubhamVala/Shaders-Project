#pragma once
#include "myScene.h";

myScene::myScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	my_shader = new Shader("..\\Shaders\\vertexshader.glsl", "..\\Shaders\\fragmentshader.glsl");
	my_shader->use();
	MakeVAO();
}

myScene::~myScene()
{
}

void myScene::MakeVAO() 
{
	glCreateBuffers(1, &VBO); // creates vertex buffer object
	glNamedBufferStorage(VBO, sizeof(float) * vertexData.size(), vertexData.data(), GL_DYNAMIC_STORAGE_BIT);
	
	glCreateBuffers(1, &EBO); // creates an element buffer object.
	glNamedBufferStorage(EBO, sizeof(unsigned int) * cubeIndices.size(), cubeIndices.data(), GL_DYNAMIC_STORAGE_BIT);


	glCreateVertexArrays(1, &VAO); // creates vertex array object.
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 6);
	glVertexArrayElementBuffer(VAO, EBO); // Adding EBO TO VBO

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);


	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));


	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);

}

void myScene::update(float dt) {
	m_camera->update(dt);
	render();
}

void myScene::render() 
{
	m_model = glm::mat4(1.0f); // identity matrix
	//camera
	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();

	//set uniforms
	my_shader->setMat4("Model", m_model);
	my_shader->setMat4("View", m_view);
	my_shader->setMat4("Projection", m_projection);



	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);

	// second cube
	m_model = glm::translate(m_model, glm::vec3(5, 0.0, 0.0));

	m_model = glm::rotate(m_model, (float)(glfwGetTime() * 3), glm::vec3(2.0, 0.0, 2.0));

	m_model = glm::scale(m_model, glm::vec3(1.5, 1.5, 1.5));

	my_shader->setMat4("Model", m_model);
	//draw call for cube 2.
	glDrawElements(GL_TRIANGLES, vertexData.size(), GL_UNSIGNED_INT, 0);

	

}