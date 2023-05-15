#pragma once

#include "OpenGLWindow.h"
#include "Transform.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>

class Scene
{
public:
	Scene(OpenGLWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	OpenGLWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	OpenGLWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID;
    GLuint  iboID;

    Transform *kopf, *rumpf, *rechtOberarm, *linkOberarm, *rechtUnterarm, *linkUnterarm, *rechtArm, *linkArm, *rechtBein, *linkBein, *alle, *alle1;
};

