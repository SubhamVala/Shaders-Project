#include "Scene.h"
#include "Shader.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Cube.h"
#include "Lights/SpotLight.h"
#include "Textures/TextureManager.h"
class myScene : public Scene
{

public:
	myScene(GLFWwindow* window, InputHandler* H);
	~myScene();
	void update(float dt) override;

private:
	Cube* m_cube;
	Shader* my_shader;
	DirectionalLight* m_directionalLight;
	PointLight* m_pointLight;
	SpotLight* m_spotLight;

	glm::mat4 m_model, m_view, m_projection;

	const float floorLevel = -2.0f;  // change these to whatever you like
	const float floorSize = 7.0f;

	std::vector<float> floorVertexData = {
		-floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,
		floorSize, floorLevel,  -floorSize,     0.0, 1.0, 0.0,
		floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0,
		-floorSize, floorLevel,   floorSize,     0.0, 1.0, 0.0,
	};
	std::vector<unsigned int> floorIndices = {
		3,2,1,
		3,1,0
	};

	void render();



};
