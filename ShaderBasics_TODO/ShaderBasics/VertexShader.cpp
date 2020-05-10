#include "pch.h"
#include "VertexShader.h"


std::string VertexShader::Source()
{
	/*
	Zadanie 5: zmodyfikowaæ program shadera w taki sposób, by wyœwietlana by³a pofalowana p³aszczyzna
	- modyfikowaæ y za pomoc¹ funkcji trygonometrycznych zale¿nych od pozycji x i y.
	*/
	return
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 aCol;\n"
		"out vec4 col;\n"
		"uniform mat4 proj;\n"
		"uniform mat4 view;\n"
		"uniform float colorChange;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = proj*view*vec4( aPos.x ,  aPos.y+aPos.z *2*cos(aPos.z) * sin(aPos.x) + cos(aPos.y) ,  aPos.z * 2 * sin(aPos.z) * sin(aPos.x)  ,  1.0);\n" 
		"	col= vec4(colorChange, aCol.x * colorChange, 0.4 + (aCol.y * aCol.x * colorChange) , 1.0);\n"
		"}\0";
}	
	//dziwne cos - gl_Position = proj*view*vec4( aPos.x ,  aPos.y+aPos.z *2*cos(aPos.z) * sin(aPos.x) ,  aPos.z * 2 * sin(aPos.z) * sin(aPos.x)  ,  1.0);\n" 
	//wyjsciowa siatka - gl_Position = proj*view*vec4(aPos.x, aPos.y+aPos.z, aPos.z, 1.0);\n"

VertexShader::VertexShader()
{
}


VertexShader::~VertexShader()
{
}
