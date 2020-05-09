#include "pch.h"
#include "Scene.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
void Scene::updateTimers()
{
	std::chrono::system_clock::time_point tCurr = std::chrono::system_clock::now();

	if (first)
	{
		t = tCurr;
		tBegin = tCurr;
		first = false;
		return;
	}
	wT = (float)std::chrono::duration_cast<std::chrono::microseconds>(tCurr - tBegin).count() / 1000000;
	dT = (float)std::chrono::duration_cast<std::chrono::microseconds>(tCurr - t).count() / 1000000;
	t = tCurr;
}
void Scene::drawVertieces()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_LINES, 0, vGenerator.Size());
}
void Scene::updateGLState()
{
	glutSwapBuffers();
	glutPostRedisplay();
}
void Scene::init()
{
	GLenum err = glewInit();
	program.addShader(std::static_pointer_cast<AShader>(std::make_shared<FragmentShader>()));
	program.addShader(std::static_pointer_cast<AShader>(std::make_shared<VertexShader>()));
	program.linkShaders();

	program.bindVertieces(vGenerator);
	glm::mat4 modelRot = glm::mat4(1.0f);
	/*
		Zadanie 4a.(0.5pkt) Zamieni� rzutowanie ortogonalne na pespektywiczne za pomoc� funkcji znajduj�cych si� w komentarzu.
		Zmodyfikowa� shader wierzcho�k�w tak aby przyjmowa� macierz "view" jako zmienn� uniform wej�ciow�.

		*/
	
	//program.addMatrix4x4f(glm::perspective(, "proj");
	//program.addMatrix4x4f(glm::lookAt(), "view");
	program.addMatrix4x4f(glm::ortho(-4.0f, 4.0f,-4.0f, 4.0f, -4.0f, 4.0f), "proj");
}

void Scene::frame(void)
{
	updateTimers();
	

	/*
		Zadanie 4b.(0.5pkt) Doda� animacj� kamery (zmiana parametr�w funkcji lookAt() w zale�no�ci od czasu).
		 Czas dost�pny jest poprzez zmienne prywatne - dT - od ostatniej klatki, wT - od pocz�tku.
		 Aktualizacja czasu - metoda updateTimers();
	*/
	drawVertieces();
	updateGLState();
}

Scene::Scene()
{
}


Scene::~Scene()
{
}
