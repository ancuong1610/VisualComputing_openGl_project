#include "OpenGLWindow.h"
#include <iomanip>

OpenGLWindow* OpenGLWindow::windowHandlerInstance;

OpenGLWindow::OpenGLWindow(const GLint sizex, const GLint sizey, bool fullscreen, bool vsync, const GLint cvmaj, const GLint cvmin, const std::string& title, const GLint msaasamples, const GLboolean uselatestglver, const GLdouble updatefrequency)
{
	this->windowWidth = sizex;
	this->windowHeight = sizey;
	this->m_uselatestglcontext = uselatestglver;
	this->m_cvmaj = cvmaj;
	this->m_cvmin = cvmin;
	this->title = title;
	this->m_samples = msaasamples;
	this->fullscreen = fullscreen;
	this->vsync = vsync;
	this->m_updatefrequency = updatefrequency;
#ifdef LOG_PERF
	m_perlog.reserve(NUM_RESERVED_PERF_RECORDS);
#endif
	if (!this->initialize())
		throw std::invalid_argument("Error: Window initialization failed.");
}


OpenGLWindow::~OpenGLWindow()
{
	if(m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
}

Input & OpenGLWindow::getInput()
{
	return *input;
}

double OpenGLWindow::getCurrentTime()
{
	return m_currentTime - m_startTime;
}

void OpenGLWindow::setCursorVisible(bool visible)
{
	glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

GLboolean OpenGLWindow::initialize()
{
	//glfwSetErrorCallback({})
	m_currentTime = 0.0f;
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW\n";
		//getchar();
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, m_samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->m_cvmaj);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->m_cvmin);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	this->m_window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), (fullscreen ? glfwGetPrimaryMonitor() : NULL), NULL);
	if (this->m_window == NULL){
		std::cerr << "Failed to open GLFW window. OpenGL Version " << m_cvmaj << "." << m_cvmin << " is not supported on your system.\n";
		//getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(this->m_window);

	glewExperimental = GL_TRUE;
	// Initialize GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW\n";
		std::cerr << "Error: " << glewGetErrorString(err) << "\n";
		//getchar();
		glfwTerminate();
		return false;
	}

	err = glGetError(); //dummy readout
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\nOpenGL Version " << m_cvmaj << "." << m_cvmin << " context successfully created.\nExtensions successfully loaded.\n";

	//Setup input instance
	input.reset(new Input(m_window));
	input->setHandlerInstance(input.get());
	input->addInputHandler(this);

	//Setup window/framebuffer resize callback
	OpenGLWindow::windowHandlerInstance = this;
	glfwSetFramebufferSizeCallback(m_window, &OpenGLWindow::frz_callback);
	glfwSetWindowSizeCallback(m_window, &OpenGLWindow::wrz_callback);

	glfwSwapInterval((vsync ? 1 : 0));
	if (m_samples > 0)
	{
		glEnable(GL_MULTISAMPLE);
		if (checkglerror())
		{
			return false;
		}
	}

	glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);
	glfwGetWindowSize(m_window, &windowWidth, &windowHeight);

	return true;
}

double OpenGLWindow::movingAvg(double mn, size_t n, double ne)
{
	return mn + (1.0 / static_cast<double>(n)) * (ne - mn);
}

GLvoid OpenGLWindow::run()
{
	if(m_window == nullptr)
		throw std::logic_error("Run failed. OpenGLWindow is not initialized.\n");
	init();
	GLdouble timeDelta = 1.0f / m_updatefrequency;

	//accumulator simulation time lag
	GLdouble timeAccumulator = 0.0;

#ifdef SHOW_PERF
	GLdouble statprintaccum = 0.0f;
	double avgframetime = 0.0f;
	double maxframetime = 0.0f;
	size_t ftindex = 1;
#endif

	GLdouble frameTime;
	GLdouble newTime;
	m_startTime = glfwGetTime();
	m_currentTime = m_startTime;
	while (!glfwWindowShouldClose(this->m_window))
	{
		newTime = glfwGetTime();
		frameTime = newTime - m_currentTime;
		m_currentTime = newTime;
		timeAccumulator += frameTime;

#ifdef SHOW_PERF
		statprintaccum += frameTime;
		maxframetime = glm::max(maxframetime, frameTime);
		avgframetime = movingAvg(avgframetime, ftindex++, frameTime);
		if (statprintaccum > PERF_INTERVAL)
		{
			double aft = avgframetime * 1000.0;
			double mft = maxframetime * 1000.0;
			double afps = 1.0 / avgframetime;
			double mfps = 1.0 / maxframetime;
			std::cout << "Frametime: avg: " << std::setprecision(5) << aft << "ms max: " << mft << 
				"ms\nFPS: avg: " << std::setprecision(3) << afps << " min: " << mfps << "\n\n";
			avgframetime = 0.0;
			ftindex = 1;
			statprintaccum = 0.0;
			maxframetime = 0.0;
#ifdef LOG_PERF
			m_perlog.push_back(PerfRecord{ aft, mft, afps, mfps });
#endif
		}
#endif

		glfwPollEvents();
		//cap max simulation steps if application runs too slowly
		if (timeAccumulator > (1.0 / 30.0))
		{
			std::cout << "\n\n--- simulation speed critical ---\n\n";
			timeAccumulator = 1.0 / 30.0;
		}
		while (timeAccumulator >= timeDelta)
		{
			update(timeDelta);			
			timeAccumulator -= timeDelta;
		}

		render(frameTime);
		glfwSwapBuffers(m_window);				
	}
	shutdown();

#ifdef LOG_PERF
	std::ofstream fstr("perflog.csv", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if (fstr.is_open())
	{
		for (const auto& e : m_perlog)
		{
			fstr << e.avgframetime << "," << e.maxframetime << "," << e.avgfps << "," << e.minfps << "\n";
		}
	}
#endif
}

GLvoid OpenGLWindow::quit()
{
	if(m_window != nullptr)
		glfwSetWindowShouldClose(m_window, GL_TRUE);
}
