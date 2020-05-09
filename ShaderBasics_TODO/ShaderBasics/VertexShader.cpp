#include "pch.h"
#include "VertexShader.h"


std::string VertexShader::Source()
{
	/*
	Zadanie 5: zmodyfikowa� program shadera w taki spos�b, by wy�wietlana by�a pofalowana p�aszczyzna
	- modyfikowa� y za pomoc� funkcji trygonometrycznych zale�nych od pozycji x i y.
	*/
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 aCol;\n"
		"out vec4 col;\n"
		"uniform mat4 proj;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y+aPos.z, aPos.z, 1.0);\n"
		"	col=vec4(1,0.5+aPos.z/12.56, 0,1);\n"
		"}\0";
}	//proj*view*

VertexShader::VertexShader()
{
}


VertexShader::~VertexShader()
{
}
