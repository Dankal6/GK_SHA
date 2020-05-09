#include "pch.h"
#include "VertexGenerator.h"
#include <iostream>
#include <GL\glew.h>


float* VertexGenerator::generateVertieces()
{


	/*
Zadanie 1 (1 pkt):
	- zaimplementowa� metod�, kt�ra polega na stworzeniu regularnej siatki wierzcho�k�w
	  w p�aszczy�nie xz pomi�dzy zadanymi warto�ciami brzegowymi i z zadanym skokiem.
	  y ustawi� na 0. Wierzcho�ek ma mie� dwa atrybuty: pozycj� (3D) i kolor (RGBA).
	  Ustawi� odpowiednie warto�ci: size (ilo�� wierzcho�k�w), dim - wymiarowo�� wierzcho�ka, count - size*dim
*/
	float	minX = -1, maxX = 3, deltaX = 1, 
			minZ = -1, maxZ = 4, deltaZ = 1;
	int p = 0;

	int Nx = (maxX - minX) / deltaX + 1;	//ilo�� wierzcho�k�w na wsp�rz�dnej x
	int Nz = (maxZ - minZ) / deltaZ + 1;	//ilo�� wierzcho�k�w na wsp�rz�dnej z
	int dim = 7;							//dim = 7 ( 3 pozycja, 4 kolor )
	int size = Nx * Nz;						//ilo�� wierzcho�k�w
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
