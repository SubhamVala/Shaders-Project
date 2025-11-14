#pragma once
#include "myScene.h";

// Q - Toggling normal mapping
// E - Toggling Directional Light
// R - Toggling Spot Light
// T - Toggling PointLight

// constructor which initilises the windows and inputHandler
myScene::myScene(GLFWwindow* window, InputHandler* H) : Scene(window, H) {
	// creates the camera and attaches the input handler
	m_camera = new FirstPersonCamera();
	m_camera->attachHandler(m_window, m_handler);
	// takes the vertex and fragment shader and compiles
	my_shader = new Shader("..\\Shaders\\vertexshader.glsl", "..\\Shaders\\fragmentshader.glsl");
	// takes normal textures of the cube and floor then compiles it inside fragment shader.
	unsigned int cubeNorm = TextureManager::loadTexture("..\\Resources\\normalCube.jpg");
	unsigned int floorNorm = TextureManager::loadTexture("..\\Resources\\normalFloor.jpg");
	// takes texture of cube and compiles inside fragment shader.
	unsigned int cubeDiff = TextureManager::loadTexture("..\\Resources\\diffuseCube.jpg");
	unsigned int cubeSpec = TextureManager::loadTexture("..\\Resources\\specularCube.jpg");
	// takes textures of floor and compiles inside fragment shader.
	unsigned int floorDiff = TextureManager::loadTexture("..\\Resources\\diffuseFloor.jpg");
	unsigned int floorSpec = TextureManager::loadTexture("..\\Resources\\specularFloor.jpg");
	// creates the directional lights and gives the uniforms a value
	m_directionalLight = new DirectionalLight(glm::vec3(1.0), glm::vec3(-2.0f, -1.0f, 0.0f));
	m_directionalLight->setLightUniforms(my_shader);
	// creates the pointlight and gives the uniforms a value
	m_pointLight = new PointLight(glm::vec3(1.0, 0.0, 0.0), glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	m_pointLight->setLightUniforms(my_shader);
	// creates the spotlight and gives the uniforms a value
	m_spotLight = new SpotLight(glm::vec3(0.5, 1.0, 0.0), glm::vec3(0.0, 7.0, 0.0), glm::vec3(1.0, 0.027, 0.0028), m_camera->getFront(), glm::vec2(glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))));
	m_spotLight->setLightUniforms(my_shader);
	// creates the cube and gives the uniforms a value.
	m_cube = new Cube(64, cubeDiff, cubeSpec, cubeNorm);
	m_cube->setCubeMaterialValues(my_shader);
	// creates the floor and gives the uniforms a value;
	m_plane = new Plane(64, floorDiff, floorSpec, floorNorm);
		
}

myScene::~myScene()
{
	// prevents deleting myScene and memory leaks.
	delete my_shader;
	delete m_cube;
	delete m_directionalLight;
	delete m_plane;
	delete m_pointLight;
	delete m_spotLight;
}


void myScene::update(float dt) {
	m_camera->update(dt);
	render();
	if (m_handler->isKeyPressed(GLFW_KEY_Q)) {    // attaches inputhandler, key Q, for normal mapping.
		useNM = !useNM;
	}
	if (m_handler->isKeyPressed(GLFW_KEY_E)) {    // attaches inputhandler, key E, for Directional Light.
		useDL = !useDL;
	}
	if (m_handler->isKeyPressed(GLFW_KEY_R)) {    // attaches inputhandler, key R, for Point Light.
		usePL = !usePL;
	}

	if (m_handler->isKeyPressed(GLFW_KEY_T)) {    // attaches inputhandler, key T, for Spot Light.
		useSL = !useSL;
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

	//uniforms for the toggle of lights.
	my_shader->setInt("useNM", useNM);
	my_shader->setInt("useDL", useDL);
	my_shader->setInt("useSL", useSL);
	my_shader->setInt("usePL", usePL);

	// cube.
	glBindVertexArray(m_cube->getVAO());
	m_cube->setCubeMaterialValues(my_shader);
	m_cube->resetTranform();
	m_cube->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);

	// second cube
	m_cube->resetTranform();
	m_cube->setCubeMaterialValues(my_shader);
	m_cube->translate(glm::vec3(5.0, 0.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 90.0f), glm::vec3(2.0f, 0.0f, 2.0f));
	m_cube->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTranform();

	// third cube
	m_cube->setCubeMaterialValues(my_shader);
	m_cube->translate(glm::vec3(-2.0, 1.0, -1.0));
	m_cube->rotate((float)(glfwGetTime() * 90.0f), glm::vec3(2.0f, 2.0f, 0.0f));
	m_cube->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTranform();
	
	// fourth cube
	m_cube->setCubeMaterialValues(my_shader);
	m_cube->translate(glm::vec3(2.5, 2.0, 0.0));
	m_cube->rotate((float)(glfwGetTime() * 90.0f), glm::vec3(0.0f, 2.0f, 2.0f));
	m_cube->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_cube->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_cube->resetTranform();

	// floor
	glBindVertexArray(m_plane->getVAO());
	m_plane->setPlaneMaterialValues(my_shader);
	m_plane->resetTransform();
	m_plane->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0);
	m_plane->resetTransform();

	// Right Wall.
	glBindVertexArray(m_plane->getVAO());
	m_plane->setPlaneMaterialValues(my_shader);
	m_plane->resetTransform();
	m_plane->translate(glm::vec3(5.0, 3.6, 0.0));
	m_plane->rotate(90, glm::vec3(0.0, 0.0, 1.0));
	m_plane->scale(1.0, glm::vec3(0.8, 1.0, 1.0));
	m_plane->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0);

	// Wall opposite to camera.
	glBindVertexArray(m_plane->getVAO());
	m_plane->setPlaneMaterialValues(my_shader);
	m_plane->resetTransform();
	m_plane->translate(glm::vec3(0.0, 3.6, -5.0));
	m_plane->rotate(90, glm::vec3(1.0, 0.0, 0.0));
	m_plane->scale(1.0, glm::vec3(1.0, 1.0, 0.8));
	m_plane->setTransform(my_shader);
	glDrawElements(GL_TRIANGLES, m_plane->getIndicesCount(), GL_UNSIGNED_INT, 0);
}