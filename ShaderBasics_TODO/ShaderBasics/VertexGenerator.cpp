#include "pch.h"
#include "VertexGenerator.h"
#include <iostream>
#include <GL\glew.h>


float* VertexGenerator::generateVertieces()
{


	/*
Zadanie 1 (1 pkt):
	- zaimplementowaæ metodê, która polega na stworzeniu regularnej siatki wierzcho³ków
	  w p³aszczyŸnie xz pomiêdzy zadanymi wartoœciami brzegowymi i z zadanym skokiem.
	  y ustawiæ na 0. Wierzcho³ek ma mieæ dwa atrybuty: pozycjê (3D) i kolor (RGBA).
	  Ustawiæ odpowiednie wartoœci: size (iloœæ wierzcho³ków), dim - wymiarowoœæ wierzcho³ka, count - size*dim
*/
	float	minX = -1, maxX = 3, deltaX = 1, 
			minZ = -1, maxZ = 4, deltaZ = 1;
	int p = 0;

	int Nx = (maxX - minX) / deltaX + 1;	//iloœæ wierzcho³ków na wspó³rzêdnej x
	int Nz = (maxZ - minZ) / deltaZ + 1;	//iloœæ wierzcho³ków na wspó³rzêdnej z
	int dim = 7;							//dim = 7 ( 3 pozycja, 4 kolor )
	int size = Nx * Nz;						//iloœæ wierzcho³ków
	int count = size * dim;					//rozmiar tablicy

	this->size = size;
	this->count = count;
	this->dim = dim;

	float* vertices = new float[count];

	for (float z = minZ; z <= maxZ; z += deltaZ)
	{
		for (float x = minX; x <= maxX; x += deltaX)
		{
			{
				vertices[p + 0] = x;
				vertices[p + 1] = 0;
				vertices[p + 2] = z;
				vertices[p + 3] = 1;
				vertices[p + 4] = 0;
				vertices[p + 5] = 0;
				vertices[p + 6] = 1;

				p += 7;
			}
		}
	}

	//glDrawArrays(GL_LINES)
	//glBufferData();
	/*for (int i = 0; i < 84; i++)
	{
		std::cout << vertices[i] << std::endl;
	}*/
	return vertices;
}

VertexGenerator::VertexGenerator()
{


}


VertexGenerator::~VertexGenerator()
{
}
