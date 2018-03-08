#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

namespace pbrt
{
	template <typename T>
	bounds3<T>::bounds3()
	{
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = point3<T>(maxNum,maxNum,maxNum);
		pMax = point3<T>(minNum,minNum,minNum);
	}

	template <typename T>
	bounds3<T>::bounds3(const pbrt::point3<T> &p):pMin(p), pMax(p) {}

	template <typename T>
	bounds3<T>::bounds3(const pbrt::point3<T> &p1, const pbrt::point3<T> &p2) 
		: pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z,p2.z)),
		  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z,p2.z)) {}


	template <typename T>
	const point3<T> & bounds3<T>::operator[](int i) const
	{
		assert(i >= 0 && i <= 1);

		if (i == 0)
			return pMin;
		else
			return pMax;
	}

	template <typename T>
	point3<T> & bounds3<T>::operator[](int i)
	{
		assert(i >= 0 && i <= 1);

		if (i == 0)
			return pMin;
		else
			return pMax;

	}

	/*
		Returns the coordinaes of one of the eight corners of the bounding
		box
	*/
	template <typename T>
	point3<T> bounds3<T>::Corner(int corner) const
	{
		return point3<T>((*this)[(corner & 1)].x,
						(*this)[(corner & 2) ? 1 : 0].y,
						(*this)[(corner & 4) ? 1 : 0].z);

	}

	template <typename T>
	vector3<T> bounds3<T>::Diagonal() const
	{
		return (pMax - pMin);
	}

	template <typename T>
	T bounds3<T>::SurfaceArea() const
	{
		vector3<T> d = Diagonal();
		return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
	}

	template <typename T>
	T bounds3<T>::Volume() const
	{
		vector3<T> d = Diagonal();
		return d.x * d.y * d.z;
	}

	/*
		returns the index of which of the three axes is longest
	*/
	template <typename T>
	int bounds3<T>::MaximumExtent() const
	{
		vector3<T> d = Diagonal();

		if (d.x > d.y && d.x > d.z)
			return 0;
		else if (d.y > d.z)
			return 1;
		else
			return 2;
	}

	/*
		linearly interpolates between the corners of the box by the given
		in each dimension
	*/
	template <typename T>
	point3<T> bounds3<T>::Lerp(const point3<float> &t) const
	{
		return point3<T>(	pbrt::Lerp(t.x, pMin.x, pMax.x),
							pbrt::Lerp(t.y, pMin.y, pMax.y),
							pbrt::Lerp(t.z, pMin.z, pMax.z));
	}

	/*
		returns the continous position of a point relative to the corners
		of the box where a point at the minimum corner has offset (0,0,0),
		a point at the maximum corner has offset (1,1,1)
	*/
	template <typename T>
	vector3<T> bounds3<T>::Offset(const point3<T> &p) const
	{
		vector3<T> o = p - pMin;
		if (pMax.x > pMin.x)
		{
			o.x /= (pMax.x - pMin.x);
		}

		if (pMax.y > pMin.y)
		{

			o.y /= (pMax.y - pMin.y);
		}

		if (pMax.z > pMin.z)
		{
			o.z /= (pMax.z - pMin.z);			
		}

		return o;
	}

	/*
		Returns the center and radius of a sphere that bounds the 
		bounding box.  In general, this may give a far looser fit than a sphere
		that bounded the original contents of the bounds3 directly
	*/
	template <typename T>
	void bounds3<T>::BoundingSphere(point3<T> *center, float *radius) const
	{
		*center = (pMin + pMax) / 2;
		*radius= Inside(*center, *this) ? Distance(*center, pMax) : 0;
	}


     template <typename T>
     bool bounds3<T>::IntersectP(const ray &r, float *hitt0, float *hitt1) const
     {
     	float t0 = 0, t1=r.tMax;
     	for (int i = 0; i < 3; ++i)
     	{
     		//〈Update interval forith bounding box slab 128〉
     		float invRayDir=1.0f /  r.d[i];
     		float tNear = (pMin[i] - r.o[i]) * invRayDir;
     		float tFar = (pMax[i] - r.o[i]) * invRayDir; 
     		// Update parametric interval from slab intersection t values 128〉
     		if (tNear > tFar) 
     		{
     			std::swap(tNear, tFar);	
     		}
     		//〈UpdatetFar to ensure robust ray–bounds intersection 221〉
     		t0=tNear > t0 ? tNear : t0;
   			t1=tFar < t1 ? tFar: t1;
   			if (t0 > t1) 
   			{
   				return false;
   			}
     	}
     	
     	if (hitt0)
     		*hitt0 = t0;
     	
     	if (hitt1)
     		*hitt1 = t1;

     	return true;
     }

     template <typename T>
     bool bounds3<T>::IntersectP(const ray &ray, const vector3<float> &invDir, const int dirIsNeg[3]) const
     {
     	const bounds3<T> &bounds = *this;

     	//〈Check for ray intersection against x and y slabs 129〉
     	float tMin = (bounds[ dirIsNeg[0]].x - ray.o.x) * invDir.x;
	    float tMax = (bounds[1-dirIsNeg[0]].x - ray.o.x) * invDir.x;
	   	float tyMin=(bounds[ dirIsNeg[1]].y - ray.o.y) * invDir.y;
	    float tyMax=(bounds[1-dirIsNeg[1]].y - ray.o.y) * invDir.y;
	   //〈UpdatetMaxandtyMaxto ensure robust bounds intersection〉
	   	if (tMin > tyMax || tyMin > tMax)
	         return false;
	   	if (tyMin > tMin) 
	   	{
	   		tMin=tyMin;
	   	}

	   	if (tyMax < tMax) 
	   	{
	   		tMax=tyMax;
	   	}

        //   〈Check for ray intersection against z slab〉
        //  TODO


        return (tMin < ray.tMax) && (tMax > 0);

     }



}