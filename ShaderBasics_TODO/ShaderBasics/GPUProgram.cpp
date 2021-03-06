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

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

	/**Zadanie 2 (1 pkt):
		- stworzy� tablic� wierzcho�k�w - u�y� metody generate generateVertieces()z klasy VertexGenerator
		- stworzy� dwie tablice atrybut�w - dla tr�jwymiarowej pozycji i czterowymiarowego koloru i przypisa�
		  je do VBO i VAO.
	*/
	float* vertices = vGen.generateVertieces();
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//funkcja ��cz�ca utworzony wcze�niej identyfikator bufora VBO z rzeczywistym buforem w pami�cie RAM GPU.

	int n = vGen.Size();					//n - ilo�� wierzcho�k�w (440) * atrybuty (7) = 3080


	glBufferData(GL_ARRAY_BUFFER, n * sizeof(float), vertices, GL_STATIC_DRAW);	//�aduje dane (vertices) do ostatniego z��czonego bufora poleceniem glBindBuffer
	//vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);	//ustalaj�ca gdzie w za�adowanym buforze (ostatnim) znajduj� si� dane dotycz�ce wsp�rz�dnych
	glEnableVertexAttribArray(0);	//aktywuje tablic� o zadanym indeksie (pierwszy parametr glVertexAttribPointer)
	//color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 *sizeof(float)));	//ustalaj�ca gdzie w za�adowanym buforze (ostatnim) znajduj� si� dane dotycz�ce RGBA
	glEnableVertexAttribArray(1);	//aktywuje tablic� o zadanym indeksie (pierwszy parametr glVertexAttribPointer)

	//koniec zadania drugiego.
	glUseProgram(shaderProgram);
	delete[] vertices; 
	return true;
}


void GPUProgram::addMatrix4x4f(glm::mat4 matrix, const GLchar* varName)
{
	/* Zadanie 3a (0.5pkt):
	Napisa� metod� dodaj�c� macierz 4x4f do programu shadera
	*/
	GLuint loc = glGetUniformLocation(shaderProgram,varName);
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GPUProgram::addFloat(GLfloat f, const GLchar * varName)
{
	/* Zadanie 3a (0.5pkt):
	Napisa� metod� dodaj�c� zmienn� typu float do programu shadera
	*/
	GLuint loc = glGetUniformLocation(shaderProgram, varName);
	glUniform1f(loc, f);
}

GPUProgram::~GPUProgram()
{
}
