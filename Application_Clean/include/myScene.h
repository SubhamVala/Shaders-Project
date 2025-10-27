#include "Scene.h"
#include "Shader.h"

class myScene : public Scene
{

public:
	myScene(GLFWwindow* window, InputHandler* H);
	~myScene();
	void update(float dt) override;

private:

	unsigned int VBO, VAO;
	float vertexData[9] = {0.5, 0.5, 0.0
					  -0.5, 0.5, 0.0
					 -0.5, -0.5, 0.0};

	void MakeVAO();
	void render();



};
