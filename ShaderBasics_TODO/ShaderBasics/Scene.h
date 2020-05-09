#pragma once
#include <gl/glew.h>

#include <ctime>
#include <chrono>
#include "FragmentShader.h"
#include "VertexShader.h"
#include "GPUProgram.h"
class Scene
{
private:
	std::chrono::system_clock::time_point t;
	std::chrono::system_clock::time_point tBegin;
	bool first = true;
	float dT;
	float wT;

	float sceneAngle = 45.0f;
	float modelAngle = 45.0f;

	GPUProgram program;
	VertexGenerator vGenerator;
	void updateTimers();
	void drawVertieces();
	void updateGLState();
public:
	void init();
	void frame(void);

	Scene();
	~Scene();
};

