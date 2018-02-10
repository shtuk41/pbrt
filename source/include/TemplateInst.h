#pragma once

#include <geometry.h>

namespace pbrt
{

	template class vector2<float>;
	typedef vector2<float> vector2f;
	typedef vector2<int> vector2i;

	template class vector3<float>;
	template class vector3<int>;
	typedef vector3<float> vector3f;
	typedef vector3<int> vector3i;

	template class point2<float>;
	template class point2<int>;
	typedef vector2<float> vector2f;
	typedef vector2<int> vector2i;

	template class point3<float>;
	template class point3<int>;
	typedef point3<float> point3f;
	typedef point3<int> point3i;

	template class normal3<float>;
	typedef normal3<float> normal3f;
}


