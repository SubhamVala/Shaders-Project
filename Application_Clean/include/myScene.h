#include "Scene.h"
#include "Shader.h"

class myScene : public Scene
{

public:
	myScene(GLFWwindow* window, InputHandler* H);
	~myScene();
	void update(float dt) override;

private:
	Shader* my_shader;
	unsigned int VBO, VAO;
	float vertexData[18] = { 0.5, 0.5, 0.0, 1.0,0.0,0.0,
						  -0.5, 0.5, 0.0,  0.0,1.0,0.0,
						  -0.5, -0.5, 0.0, 0.0,0.0,1.0};

	

	void MakeVAO();
	void render();



};
