#pragma once
#include "myScene.h";

// constructor which initilises the windows and inputHandler
myScene::myScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	// creates the camera and attaches the input handler
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	// takes the vertex and fragment shader and compiles
	my_shader = new Shader("..\\Shaders\\vertexshader.glsl", "..\\Shaders\\fragmentshader.glsl");

	unsigned int cubeNorm = TextureManager::loadTexture("..\\Resources\\normalCube.jpg");
	// takes texture of cube and compiles inside fragment shader.
	unsigned int cubeDiff = TextureManager::loadTexture("..\\Resources\\diffuseCube.jpg");
	unsigned int cubeSpec = TextureManager::loadTexture("..\\Resources\\specularCube.jpg");
	// takes textures of floor and compiles inside fragment shader.
	//unsigned int floorDiff = TextureManager::loadTexture("..\\Resources\\diffuseFloor.jpg");
	//unsigned int floorSpec = TextureManager::loadTexture("..\\Resources\\specularFloor.jpg");
	// creates the directional lights and gives the uniforms a value
	m_directionalLight = new DirectionalLight(glm::vec3(1.0), glm::vec3(-1.0f, -1.0f, 0.0f));
	m_directionalLight->setLightUniforms(my_shader);
	// creates the pointlight and gives the uniforms a value
	m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0009f, 0.0000032f));
	m_pointLight->setLightUniforms(my_shader);
	// creates the spotlight and gives the uniforms a value
	m_spotLight = new SpotLight(glm::vec3(0.5, 1.0, 0.0), glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.027, 0.0028), m_camera->getFront(), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	m_spotLight->setLightUniforms(my_shader);
	// creates the cube and gives the uniforms a value.
	m_cube = new Cube(64, cubeDiff, cubeSpec, cubeNorm);
	m_cube->setCubeMaterialValues(my_shader);
	// creates the floor and gives the uniforms a value;
	m_plane = new Plane(64, cubeDiff, cubeSpec, cubeNorm);
	m_plane->setPlaneMaterialValues(my_shader);
}

myScene::~myScene()
{
	delete my_shader;
	delete m_cube;
	delete m_directionalLight;
}


void myScene::update(float dt) {
	m_camera->update(dt);
	render();
	if (m_handler->isKeyPressed(GLFW_KEY_Q)) {
		useNM = !useNM;
	}
}

void myScene::render()
{
	m_model = glm::mat4(1.0f); // identity matrix
	//camera
	m_projection = m_camera->getProjectionMatrix();
	m_view = m_camera->getViewMatrix();
	my_shader->use();
	//set uniforms

	// camera uniforms
	my_shader->setMat4("View", m_view);
	my_shader->setMat4("Projection", m_projection);
	my_shader->setVec3("viewPos", m_camera->getPosition());
	my_shader->setVec3("sDirection", m_camera->getFront());
	my_shader->setInt("useNM", useNM);

	// cube.
	glBindVertexArray(m_cube->getVAO());
	m_cube->resetTranform();
	m_cube->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	// second cube
	m_cube->resetTranform();
	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 90.0f), glm::vec3(2.0f, 0.0f, 2.0f));
	m_cube->setTransform(my_shader);

	//draw call for cube 2.
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTranform();

	// floor
	glBindVertexArray(m_plane->getVAO());
	m_plane->resetTransform();
	m_plane->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0);

}