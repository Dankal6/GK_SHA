#include "pch.h"
#include "VertexGenerator.h"
#include <iostream>
#include <GL\glew.h>

bool cmpf(float a, float b)
{
	return (fabs(a - b) < 0.000001);
}


float* VertexGenerator::generateVertieces()
{


	/*
Zadanie 1 (1 pkt):
	- zaimplementowaæ metodê, która polega na stworzeniu regularnej siatki wierzcho³ków
	  w p³aszczyŸnie xz pomiêdzy zadanymi wartoœciami brzegowymi i z zadanym skokiem.
	  y ustawiæ na 0. Wierzcho³ek ma mieæ dwa atrybuty: pozycjê (3D) i kolor (RGBA).
	  Ustawiæ odpowiednie wartoœci: size (iloœæ wierzcho³ków), dim - wymiarowoœæ wierzcho³ka, count - size*dim
*/
	float	minX = -1.0f, maxX = 1.0f, deltaX = 0.2f,
			minZ = -1.0f, maxZ = 1.0f, deltaZ = 0.2f;
	int p = 0;

	int Nx = (maxX - minX) / deltaX + 1;	//iloœæ wierzcho³ków na wspó³rzêdnej x
	int Nz = (maxZ - minZ) / deltaZ + 1;	//iloœæ wierzcho³ków na wspó³rzêdnej z
	int dim = 7;							//dim = 7 ( 3 pozycja, 4 kolor )
	int size = Nx * Nz;						//iloœæ wierzcho³ków (prezentacja)
	int count = size * dim;					//rozmiar tablicy (prezentacja)

	/*
		rzeczywisty rozmiar tablicy i liczba wierzcho³ków: 
		(Nx - 1) * (Nz - 1) - liczba kszta³tów "L" w siatce, obejmuj¹ca w sobie 4 punkty (st¹d *4), które posiadaj¹ po 7 w³aœciwoœci (dim), st¹d *28
		(Nx - 1) oraz (Nz - 1) - liczba pojedynczych linii w siatce, poziomych lub pionowych, które obejmuj¹ w sobie po 2 punkty (st¹d *2), ka¿dy z nich po 7 w³aœciwoœci (dim), st¹d * 14
	*/
	int tabSize = (Nx - 1) * (Nz - 1) * 28 + ((Nx - 1) * 14 + (Nz - 1) * 14);	//rzeczywisty rozmiar tablicy
	int newCount = (Nx - 1) * (Nz - 1) * 4 + ((Nx - 1) * 2 + (Nz - 1) * 2);		//iloœæ wierzcho³ków do narysowania
	float* vertices = new float[tabSize];

	for (float z = minZ; z <= maxZ; z += deltaZ)
	{
		for (float x = minX; x <= maxX; x += deltaX)
		{
			if (cmpf(x, maxX) && !cmpf(z, maxZ))
			{
				//tylko pionowa linia
				vertices[p + 0] = x;
				vertices[p + 1] = 0.0f;
				vertices[p + 2] = z;
				vertices[p + 3] = 1.0f;
				vertices[p + 4] = 1.0f;
				vertices[p + 5] = 0.0f;
				vertices[p + 6] = 1.0f;

				vertices[p + 7] = x;
				vertices[p + 8] = 0.0f;
				vertices[p + 9] = z + deltaZ;
				vertices[p + 10] = 1.0f;
				vertices[p + 11] = 0.0f;
				vertices[p + 12] = 0.0f;
				vertices[p + 13] = 1.0f;

				p += 14;
			}
			else if (cmpf(z, maxZ) && !cmpf(x, maxX))
			{
				//tylko pozioma linia
				vertices[p + 0] = x;
				vertices[p + 1] = 0.0f;
				vertices[p + 2] = z;
				vertices[p + 3] = 0.0f;
				vertices[p + 4] = 1.0f;
				vertices[p + 5] = 0.0f;
				vertices[p + 6] = 1.0f;

				vertices[p + 7] = x + deltaX;
				vertices[p + 8] = 0.0f;
				vertices[p + 9] = z;
				vertices[p + 10] = 0.0f;
				vertices[p + 11] = 1.0f;
				vertices[p + 12] = 1.0f;
				vertices[p + 13] = 1.0f;

				p += 14;
			}
			else if (!cmpf(z, maxZ) && !cmpf(x, maxX))
			{
				//kszta³t "L"
				vertices[p + 0] = x;
				vertices[p + 1] = 0.0f;
				vertices[p + 2] = z;
				vertices[p + 3] = 1.0f;
				vertices[p + 4] = 0.0f;
				vertices[p + 5] = 1.0f;
				vertices[p + 6] = 1.0f;

				vertices[p + 7] = x + deltaX;
				vertices[p + 8] = 0.0f;
				vertices[p + 9] = z;
				vertices[p + 10] = 0.0f;
				vertices[p + 11] = 0.0f;
				vertices[p + 12] = 1.0f;
				vertices[p + 13] = 1.0f;

				vertices[p + 14] = x;
				vertices[p + 15] = 0.0f;
				vertices[p + 16] = z;
				vertices[p + 17] = 0.0f;
				vertices[p + 18] = 1.0f;
				vertices[p + 19] = 1.0f;
				vertices[p + 20] = 1.0f;

				vertices[p + 21] = x;
				vertices[p + 22] = 0.0f;
				vertices[p + 23] = z + deltaZ;
				vertices[p + 24] = 0.0f;
				vertices[p + 25] = 0.0f;
				vertices[p + 26] = 1.0f;
				vertices[p + 27] = 1.0f;

				p += 28;
			}
		}
	}

	this->size = tabSize;
	this->count = newCount;
	this->dim = dim;

	/* DEBUG
	for (int i = 0; i < tabSize; i+=7)
	{
		if (vertices[i] > (-0.000001f) && vertices[i] < (0.000001f))
		{
			vertices[i] = 0.0f;
		}
		std::cout << std::endl << vertices[i] << "\t" << vertices[i + 1] << "\t" << vertices[i+2];
	}*/
	return vertices;
}

VertexGenerator::VertexGenerator()
{


}


VertexGenerator::~VertexGenerator()
{
}
