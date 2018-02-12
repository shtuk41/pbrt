// pbrt.cpp : Defines the entry point for the console application.

#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

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

	pbrt::normal3f norm3f(somevec);

	std::cout << somevec.x << std::endl;
	std::cout << somevec.y << std::endl;
	std::cout << somevec.z << std::endl;

	pbrt::bounds3f b3;

	std::cout << b3.pMin.x << std::endl;
	std::cout << b3.pMin.y << std::endl;
	std::cout << b3.pMin.z << std::endl;
	std::cout << b3.pMax.x << std::endl;
	std::cout << b3.pMax.y << std::endl;
	std::cout << b3.pMax.z << std::endl;

	std::cout << b3[0].x << std::endl;
	std::cout << b3[0].y << std::endl;
	std::cout << b3[0].z << std::endl;

	pbrt::bounds3f b4 = pbrt::Expand(b3, 1.0f);


#if defined (_MSC_VER)        
	system("pause");
#endif        

	return 0;
}

