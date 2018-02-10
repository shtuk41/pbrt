#include "stdafx.h"
#include <assert.h>
#include <cmath>
#include <cfloat>
#include "TemplateInst.h"

namespace pbrt
{

	template <typename T>
	vector3<T>::vector3(T x, T y, T z) : x(x), y(y), z(z)
	{
		assert(!HasNaNs());
	}

	template <typename T>
	vector3<T>::vector3(const normal3<T> &n) : x(n.x), y(n.y), z(n.z) 
	{
         assert(!n.HasNaNs());
	}

	template <typename T>
	T	vector3<T>::operator[] (int i) const
	{
		assert(i >= 0 && i <= 2);
		if (i == 0)
			return x;

		if (i == 1)
			return y;

		return z;
	}

	template <typename T>
	vector3<T> vector3<T>::operator+(const vector3<T> &v) const
	{
		return vector3(x + v.x, y + v.y, z + v.z);
	}

	template <typename T>
	vector3<T> & vector3<T>::operator +=(const vector3<T> &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template <typename T>
	vector3<T> vector3<T>::operator-(const vector3<T> &v) const
	{
		return vector3(x - v.x, y - v.y, z - v.z);
	}

	template <typename T>
	vector3<T> & vector3<T>::operator-=(const vector3<T> &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template <typename T>
	vector3<T> vector3<T>::operator*(T s) const
	{
		return vector3(x * s, y  * s, z  * s);
	}

	template <typename T>
	vector3<T> & vector3<T>::operator*=(T s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	template <typename T>
	vector3<T> vector3<T>::operator/(T f) const
	{
		assert( f != 0);
		float inv = 1.0f /f;
		return vector3(static_cast<T>(x * inv), static_cast<T>(y * inv), static_cast<T>(z * inv));
	}

	template <typename T>
	vector3<T> & vector3<T>::operator/=(T f)
	{
		assert( f != 0);
		float inv = 1.0f /f;
		x = static_cast<T>(x * inv);
		y = static_cast<T>(y * inv);
		z = static_cast<T>(z * inv);
		return *this;
	}

	template <typename T>
	vector3<T> vector3<T>::operator-() const
	{
		return vector3(-x,-y,-z);
	}

	template <typename T>
	bool vector3<T>::HasNaNs() const
	{
		return (_isnan(x) | _isnan(y) | _isnan(z)) > 0;
	}

	template <typename T>
	float vector3<T>::LengthSquared() const 
	{ 
		return static_cast<float>(x * x + y * y + z * z); 
	}

	template <typename T>
	float vector3<T>::Length() const 
	{ 
		return std::sqrt(LengthSquared());
	}

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
		return (_isnan(x) | _isnan(y) | _isnan(z)) > 0;
	}

	template <typename T>
	point2<T>::point2(const point3<T> &p) : x(p.x), y(p.y)
	{
		assert(!HasNaNs());
	}

	template <typename T>
	bool point2<T>::HasNaNs() const
	{
		return (_isnan(x) | _isnan(y)) > 0;
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
	normal3<T>::normal3(const vector3<T> &v) : x(v.x), y(v.y), z(v.z)
	{
		assert(!v.HasNaNs());
	}

	template <typename T>
	bool normal3<T>::HasNaNs() const
	{
		return (_isnan(x) | _isnan(y) | _isnan(z)) > 0;
	}

}









