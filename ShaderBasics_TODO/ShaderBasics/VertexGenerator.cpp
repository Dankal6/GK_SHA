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
	float	minX = -0.8, maxX = -0.6, deltaX = 0.2, 
			minZ = -0.4, maxZ = -0.2, deltaZ = 0.2;
	int p = 0;

	int Nx = (maxX - minX) / deltaX + 1;	//ilo�� wierzcho�k�w na wsp�rz�dnej x
	int Nz = (maxZ - minZ) / deltaZ + 1;	//ilo�� wierzcho�k�w na wsp�rz�dnej z
	int dim = 7;							//dim = 7 ( 3 pozycja, 4 kolor )
	int size = Nx * Nz;						//ilo�� wierzcho�k�w
	int count = size * dim;					//rozmiar tablicy


	float* vertices = new float[112];

	for (float z = minZ; z <= maxZ; z += deltaZ)
	{
		for (float x = minX; x <= maxX; x += deltaX)
		{
			if (x == maxX && z < maxZ)
			{
				//tylko pionowa linia
				vertices[p + 0] = x;
				vertices[p + 1] = 0;
				vertices[p + 2] = z;
				vertices[p + 3] = 1;
				vertices[p + 4] = 1;
				vertices[p + 5] = 1;
				vertices[p + 6] = 1;

				vertices[p + 7] = x;
				vertices[p + 8] = 0;
				vertices[p + 9] = z + deltaZ;
				vertices[p + 10] = 1;
				vertices[p + 11] = 1;
				vertices[p + 12] = 1;
				vertices[p + 13] = 1;

				p += 14;
			}
			else if (z == maxZ /*&& x < maxX*/)
			{
				if (x != maxX)
				{
					//tylko pozioma linia
					vertices[p + 0] = x;
					vertices[p + 1] = 0;
					vertices[p + 2] = z;
					vertices[p + 3] = 1;
					vertices[p + 4] = 1;
					vertices[p + 5] = 1;
					vertices[p + 6] = 1;

					vertices[p + 7] = x + deltaX;
					vertices[p + 8] = 0;
					vertices[p + 9] = z;
					vertices[p + 10] = 1;
					vertices[p + 11] = 1;
					vertices[p + 12] = 1;
					vertices[p + 13] = 1;

					p += 14;
				}
			}
			else
			{
				vertices[p + 0] = x;
				vertices[p + 1] = 0;
				vertices[p + 2] = z;
				vertices[p + 3] = 1;
				vertices[p + 4] = 1;
				vertices[p + 5] = 1;
				vertices[p + 6] = 1;

				vertices[p + 7] = x + deltaX;
				vertices[p + 8] = 0;
				vertices[p + 9] = z;
				vertices[p + 10] = 1;
				vertices[p + 11] = 1;
				vertices[p + 12] = 1;
				vertices[p + 13] = 1;

				vertices[p + 14] = x;
				vertices[p + 15] = 0;
				vertices[p + 16] = z;
				vertices[p + 17] = 1;
				vertices[p + 18] = 1;
				vertices[p + 19] = 1;
				vertices[p + 20] = 1;

				vertices[p + 21] = x;
				vertices[p + 22] = 0;
				vertices[p + 23] = z + deltaZ;
				vertices[p + 24] = 1;
				vertices[p + 25] = 1;
				vertices[p + 26] = 1;
				vertices[p + 27] = 1;

				p += 28;
			}
		}
	}

	this->size = p;
	this->count = count;
	this->dim = dim;

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
