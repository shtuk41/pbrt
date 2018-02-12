#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <assert.h>
#include <cmath>
#include <cfloat>
#include <point.h>

namespace pbrt
{
	template <typename T>
	point3<T>::point3()
	{
		x = y = z = 0;
	}

	template <typename T>
	point3<T>::point3(T x, T y, T z) : x(x), y(y), z(z)
	{
		assert(!HasNaNs());
	}

	template <typename T>
	bool point3<T>::HasNaNs() const
	{
#if defined (_MSC_VER_)
            return (_isnan(x) | _isnan(y) | _isnan(z)) > 0;
#elif defined(__GNUC__) || defined(__GNUG__) 
            return (std::isnan(x) | std::isnan(y) | std::isnan(z)) > 0;
#else
            return true;
#endif             
        }

	template <typename T>
	point2<T>::point2(const point3<T> &p) : x(p.x), y(p.y)
	{
		assert(!HasNaNs());
	}

	template <typename T>
	bool point2<T>::HasNaNs() const
	{
#if defined (_MSC_VER_)
            return (_isnan(x) | _isnan(y)) > 0;
#elif defined(__GNUC__) || defined(__GNUG__) 
            return (std::isnan(x) | std::isnan(y)) > 0;
#else
            return true;
#endif 
	}

	template <typename T>
	point3<T> point3<T>::operator+(const vector3<T> &v) const
	{
		return point3<T> (x + v.x, y + v.y, z + v.z);
	}

	template <typename T>
	template <typename U>
	point3<T>::point3(const point3<U> &p) : x((T)p.x), y((T)p.y), z((T)p.z)
	{
		assert(!HasNaNs());
	}

	template <typename T>
	point3<T>& point3<T>::operator+=(const vector3<T> &v)
	{
		x += v.x; 
		y += v.y; 
		z += v.z;
		return *this;
	}

	template <typename T>
	vector3<T> point3<T>::operator-(const point3<T> &p) const
	{
		return vector3<T>(x - p.x, y - p.y, z - p.z);
	}

	template <typename T>
	point3<T> point3<T>::operator-(const vector3<T> &v)
	{
		return point3<T>(x - v.x,y - v.y, z - v.z);
	}

	template <typename T>
	point3<T> & point3<T>::operator-=(const vector3<T> &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template <typename T>
	point3<T> point3<T>::operator+(const point3<T> &p) const
	{
		return point3<T>(x + p.x, y + p.y, z + p.z);
	}

	template <typename T>
	point3<T> point3<T>::operator/(T s) const
	{
		assert(s != 0);
		return point3<T>(x / s, y / s, z / s);
	}


	

}









