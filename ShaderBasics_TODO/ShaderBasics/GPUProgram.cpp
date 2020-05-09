#include "pch.h"
#include "GPUProgram.h"
#include <vector>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
bool GPUProgram::programLinkStatus()
{
	{
		GLint status;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> log(length);
			glGetProgramInfoLog(shaderProgram, length, &length, &log[0]);
			std::cout << &log[0];
			return false;
		}
		std::cout << "Shaders linked to the program succesfully :-)";
		return true;
	}
}

GPUProgram::GPUProgram()
{
	
}

bool GPUProgram::addShader(std::shared_ptr<AShader> shader)
{
	shader->initialize();
	if (!shader->Compile())
		return false;
	shaders.push_back(shader);
	return true;
}

bool GPUProgram::linkShaders()
{
	shaderProgram = glCreateProgram();
	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader) {
		glAttachShader(shaderProgram, (*shader)->ShaderGLObj());
	}
	glLinkProgram(shaderProgram);
	return programLinkStatus();
	
}

bool GPUProgram::bindVertieces(VertexGenerator& vGen)
{
	GLuint VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//sam doda³em na podstawie instrukcji
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	/**Zadanie 2 (1 pkt):
		- stworzyæ tablicê wierzcho³ków - u¿yæ metody generate generateVertieces()z klasy VertexGenerator
		- stworzyæ dwie tablice atrybutów - dla trójwymiarowej pozycji i czterowymiarowego koloru i przypisaæ
		  je do VBO i VAO.
	*/
	float* vertices = vGen.generateVertieces();
	int n = vGen.Size();	//n - iloœæ wierzcho³ków


	glBufferData(GL_ARRAY_BUFFER, 7 * n * sizeof(float), vertices, GL_STATIC_DRAW);
	//vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 *sizeof(float)));
	glEnableVertexAttribArray(1);

	//koniec zadania drugiego.
	glUseProgram(shaderProgram);
	delete[] vertices; 
	return true;
}


void GPUProgram::addMatrix4x4f(glm::mat4 matrix, const GLchar* varName)
{
	/* Zadanie 3a (0.5pkt):
	Napisaæ metodê dodaj¹c¹ macierz 4x4f do programu shadera
	*/
	GLuint loc = glGetUniformLocation(shaderProgram,varName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GPUProgram::addFloat(GLfloat f, const GLchar * varName)
{
	/* Zadanie 3a (0.5pkt):
	Napisaæ metodê dodaj¹c¹ zmienn¹ typu float do programu shadera
	*/
	GLuint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform1f(loc, f);
}

GPUProgram::~GPUProgram()
{
}
