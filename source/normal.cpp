#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <cmath>
#include <normal.h>

namespace pbrt
{
	template <typename T>
	normal3<T>::normal3(const pbrt::vector3<T> &v) : x(v.x), y(v.y), z(v.z)
	{
		assert(!v.HasNaNs());
	}


	template <typename T>
	bool normal3<T>::HasNaNs() const
	{
#if defined (_MSC_VER_)
        return (_isnan(x) | _isnan(y) | _isnan(z)) > 0;
#elif defined(__GNUC__) || defined(__GNUG__) 
        return (std::isnan(x) | std::isnan(y) | std::isnan(z)) > 0;
#else
        return true;
#endif   
	}
}
