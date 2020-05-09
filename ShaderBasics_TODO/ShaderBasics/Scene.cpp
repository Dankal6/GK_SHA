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
		Zadanie 4a.(0.5pkt) Zamieniæ rzutowanie ortogonalne na pespektywiczne za pomoc¹ funkcji znajduj¹cych siê w komentarzu.
		Zmodyfikowaæ shader wierzcho³ków tak aby przyjmowa³ macierz "view" jako zmienn¹ uniform wejœciow¹.

		*/
	
	//program.addMatrix4x4f(glm::perspective(, "proj");
	//program.addMatrix4x4f(glm::lookAt(), "view");
	program.addMatrix4x4f(glm::ortho(-4.0f, 4.0f,-4.0f, 4.0f, -4.0f, 4.0f), "proj");
}

void Scene::frame(void)
{
	updateTimers();
	

	/*
		Zadanie 4b.(0.5pkt) Dodaæ animacjê kamery (zmiana parametrów funkcji lookAt() w zale¿noœci od czasu).
		 Czas dostêpny jest poprzez zmienne prywatne - dT - od ostatniej klatki, wT - od pocz¹tku.
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
