// pbrt.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cstdlib>
#include <iostream>

#include "TemplateInst.h"

int main(int argc, char* argv[])
{
	pbrt::vector3f vec3f(30,40,30);

	float length = vec3f.Length();

	std::cout << length << std::endl;

	pbrt::point3f point(10,10,10);

	pbrt::vector3f somevec = (pbrt::vector3f)point;

	std::cout << somevec.x << std::endl;
	std::cout << somevec.y << std::endl;
	std::cout << somevec.z << std::endl;

	system("pause");

	return 0;
}

