#include "Scene.h"
#include "Shader.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Cube.h"
#include "Lights/SpotLight.h"
#include "Textures/TextureManager.h"
#include "Plane.h"
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
	Plane* m_plane;
	
	// sets all the inputs false.
	bool useNM = false;
	bool useDL = false;
	bool usePL = false;
	bool useSL = false;


	glm::mat4 m_model, m_view, m_projection;

	void render();
};
