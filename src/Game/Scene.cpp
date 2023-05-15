#include "Scene.h"
#include "Cube.h"
#include <AssetManager.h>

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();

        float vertices[] = {-0.5, -1, 0.0, 0.0, 1.0,
                            0.5, -1, 0.0, 0.0, 1.0,
                            -0.5, 0.5, 0.0, 1.0, 0.0,
                            0.5, 0.5, 1.0, 0.0, 0.0,
                            -1, 0.5, 0.0, 1.0, 0.0,
                            1, 0.5, 0.7, 0.2, 0.0,
                            -1, 1, 0.0, 0.1, 0.4,
                            1, 1, 0.1, 0.1, 0.6};

        int indices[] = {0, 1, 3,
                         0, 2, 3,
                         4, 5, 6,
                         5, 6, 7};

        // setup VAO
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        // setup VBO
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12);
        glEnableVertexAttribArray(1);

        // setup IBO
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        //2.2
        //T1 = new Transform;

        // globale Rotation um Y-Achse, wird jeden Frame gesetzt
        alle = new Transform;

        // Einmalige Skalierung von allen
        alle1 = new Transform;
        alle1->scale(glm::vec3(0.1f, 0.1f, 0.1f));

        // Einmalige Skalierung des Rumpfes
        rumpf = new Transform;
        rumpf->scale(glm::vec3(2.0f, 3.5f, 2.1f));

        // fixe Translation des Kopfes
        kopf = new Transform;
        kopf->translate(glm::vec3(0, 2.5f, 0));

        // Verarbeitung des linken Beins
        linkBein = new Transform;
        linkBein->scale(glm::vec3(0.5f, 2.5f, 0.6f));
        linkBein->translate(glm::vec3(0.7f, -3.2f, 0));

        // Verarbeitung des rechten Beins
        rechtBein = new Transform;
        rechtBein->scale(glm::vec3(0.5f, 2.5f, 0.6f));
        rechtBein->translate(glm::vec3(-0.7f, -3.2f, 0));

        // Verarbeitung des linken Oberarm
        linkOberarm = new Transform;
        linkOberarm->scale(glm::vec3(0.6f, 1.5f, 0.6f));
        linkOberarm->translate(glm::vec3(-1.5f, 0.6f, 0.0f));

        // Verarbeitung der Unterarme
        linkUnterarm = new Transform;
        linkUnterarm->rotateAroundPoint(glm::vec3(0, -0.5, -0.2), glm::vec3(-0.7, 0, 0));
        linkUnterarm->scale(glm::vec3(0.6f, 1.5f, 0.6f));
        linkUnterarm->translate(glm::vec3(-1.5f, -1.15f, 0.0f));

        linkArm = new Transform;
        rechtArm = new Transform;

        rechtUnterarm = new Transform;
        rechtUnterarm->rotateAroundPoint(glm::vec3(0, -0.5, -0.2), glm::vec3(-0.7, 0, 0));
        rechtUnterarm->scale(glm::vec3(0.6f, 1.5f, 0.6f));
        rechtUnterarm->translate(glm::vec3(1.5f, -1.15f, 0.0f));

        // Verarbeitung des rechten Oberarm
        rechtOberarm = new Transform;
        rechtOberarm->scale(glm::vec3(0.6f, 1.5f, 0.6f));
        rechtOberarm->translate(glm::vec3(1.5f, 0.6f, 0.0f));


        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        // Set Background clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glClearDepth(0.0);

        std::cout << "Scene initialization done\n";
        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}


}

void Scene::render(float dt)
{
    // Clear background color and depth buffer for depth test
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vaoID);

    // 2.2
    //T1->rotate(glm::vec3(0.2 * dt, 0.2 * dt, 0.2 * dt));
    //m_shader->setUniform("mm", T1->getTransformMatrix(), false);

    static float time = 2;
    static bool rightMove = true;
    time += dt;
    if (time > 4) {
        time = 0;
        rightMove = !rightMove;
    }

    // Rotiere Robot um 0.2 rad pro Sekunde

    alle->rotate(glm::vec3(0, 0.2 * dt, 0));

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * kopf->getTransformMatrix(), false);
    glm::vec3 colorAdjustment = glm::vec3(0.3f, -0.7f, 0.2f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);


    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * rumpf->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(-0.2f, -0.4f, -0.2f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    if (rightMove) {
        linkArm->rotateAroundPoint(glm::vec3(0, 0.3, 0), glm::vec3(-0.2 * dt, 0, 0));
    }
    else {
        linkArm->rotateAroundPoint(glm::vec3(0, 0.3, 0), glm::vec3(0.2 * dt, 0, 0));
    }

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * linkArm->getTransformMatrix() * linkOberarm->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(0.7f, 0.7f, -0.4f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * linkArm->getTransformMatrix() * linkUnterarm->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(-0.4f, -0.4f, 0.7f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    if (rightMove) {
        rechtArm->rotateAroundPoint(glm::vec3(0, 0.3, 0), glm::vec3(0.2 * dt, 0, 0));
    } else {
        rechtArm->rotateAroundPoint(glm::vec3(0, 0.3, 0), glm::vec3(-0.2 * dt, 0, 0));
    }

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * rechtArm->getTransformMatrix() * rechtUnterarm->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(0.7f, 0.7f, -0.4f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * rechtArm->getTransformMatrix() * rechtOberarm->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(-0.4f, -0.4f, 0.7f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    if (rightMove) {
        linkBein->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.1 * dt, 0, 0));
    } else {
        linkBein->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.1 * dt, 0, 0));
    }

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * linkBein->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(0.7f, 0.7f, -0.4f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);

    if (rightMove) {
        rechtBein->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(0.1 * dt, 0, 0));
    } else {
        rechtBein->rotateAroundPoint(glm::vec3(0, -0.3, 0), glm::vec3(-0.1 * dt, 0, 0));
    }

    m_shader->setUniform("mm", alle->getTransformMatrix() * alle1->getTransformMatrix() * rechtBein->getTransformMatrix(), false);
    colorAdjustment = glm::vec3(-0.4f, -0.4f, 0.7f);
    m_shader->setUniform("colorAdjustment", colorAdjustment);
    glDrawElements(GL_TRIANGLES, sizeof(cubeInd), GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
}

void Scene::update(float dt)
{

}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}

