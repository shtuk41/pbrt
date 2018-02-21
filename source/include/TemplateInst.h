#pragma once

#include <normal.h>
#include <point.h>
#include <vector.h>
#include <bounds.h>


namespace pbrt
{
	template class normal3<float>;
	typedef normal3<float> normal3f;

	template class vector2<float>;
	typedef vector2<float> vector2f;
	typedef vector2<int> vector2i;

	template class vector3<float>;
	template class vector3<int>;
	typedef vector3<float> vector3f;
	typedef vector3<int> vector3i;

	template class point2<float>;
	typedef point2<float> point2f;

	template class point2<int>;
	typedef vector2<float> vector2f;
	typedef vector2<int> vector2i;

	template class point3<float>;
	template class point3<int>;
	typedef point3<float> point3f;
	typedef point3<int> point3i;

	template class bounds2<float>;
	template class bounds2<int>;
	typedef bounds2<float> bounds2f;
	typedef bounds2<int> bounds2i;

	template class bounds3<float>;
	template class bounds3<int>;
	typedef bounds3<float> bounds3f;
	typedef bounds3<int> bounds3i;

}


