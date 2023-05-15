#include "Window.h"


Window::Window() :
        OpenGLWindow(1280,				//width
			1280,				//height
			false,				//fullscreen
			false,				//vsync
			4,					//OpenGL Version Major
			0,					//OpenGL Version Minor	=> Here the OpenGL Version is 3.3
			"Visual Computing Praktikum",			//Window title
			4,					//MSAA samples for default framebuffer
			false,				//use latest available OpenGL version (instead of the one specified above)
			120.0)				//Update frequency
{}

Window::~Window()
{

}

//Initialization here. (i.e. load a scene, load textures ...)
void Window::init()
{
	m_scene = std::unique_ptr<Scene>(new Scene(this));
	m_scene->init();
	setCursorVisible(true);
}

//cleanup. Free resources here.
void Window::shutdown()
{
	m_scene->shutdown();
}

//Update Window Logic here
void Window::update(GLdouble dtime)
{
	m_scene->update(static_cast<float>(dtime));
}

//Render a frame
void Window::render(GLdouble dtime)
{
	m_scene->render(static_cast<float>(dtime));
}

//Keyboard events
void Window::onKey(Key key, Action action, Modifier modifier)
{
	if (key == Key::Escape && action == Action::Down)
		quit();		
	m_scene->onKey(key, action, modifier);
}

//Mouse move events
void Window::onMouseMove(MousePosition mouseposition)
{
	m_scene->onMouseMove(mouseposition);
}

//Mouse Button events
void Window::onMouseButton(MouseButton button, Action action, Modifier modifier)
{
	m_scene->onMouseButton(button, action, modifier);
}

//Mouse scroll events
void Window::onMouseScroll(double xscroll, double yscroll)
{
	m_scene->onMouseScroll(xscroll, yscroll);
}

//Window resize events
void Window::onFrameBufferResize(int width, int height)
{
	m_scene->onFrameBufferResize(width, height);
}
