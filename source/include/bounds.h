#pragma once

#include <limits>
#include <point.h>

namespace pbrt
{

	template <typename T>
	class bounds2
	{

	public:

	};

	template <typename T>
	class bounds3
	{
	public:
		bounds3();
		bounds3(const point3<T> &p);
		bounds3(const point3<T> &p1, const point3<T> &p2);

		const point3<T> & operator[](int i) const;
		point3<T> & operator[](int i);

		point3<T> Corner(int corner) const;
		vector3<T> Diagonal() const;
		T SurfaceArea() const;
		T Volume() const;
		int MaximumExtent() const;
		point3<T> Lerp(const point3<float> &t) const;
		vector3<T> Offset(const point3<T> &p) const;
		void BoundingSphere(point3<T> *center, float *radius) const;
		bool IntersectP(const ray &r, float *hitt0, float *hitt1) const;
		bool IntersectP(const Ray &ray, const Vector3f &invDir, const int dirIsNeg[3]) const;


		point3<T>	pMin;
		point3<T>	pMax;
	};

	template <typename T>
	inline bounds3<T> Union(const bounds3<T> &b, const point3<T> &p)
	{
		return bounds3<T>(point3<T>(std::min(b.pMin.x, p.x),
									std::min(b.pMin.y, p.y),
									std::min(b.pMin.z, p.z)),
							point3<T>(std::max(b.pMax.x, p.x),
									std::max(b.pMax.y, p.y),
									std::max(b.pMax.z, p.z)));

	}

	template <typename T>
	inline bounds3<T> Intersect(const bounds3<T> &b1, const bounds3<T> &b2)
	{
		return bounds3<T>(point3<T>(std::max(b1.pMin.x, b2.pMin.x),
									std::max(b1.pMin.y, b2.pMin.y),
									std::max(b1.pMin.z, b2.pMin.z)),
						  point3<T>(std::min(b1.pMax.x, b2.pMax.x),
						  			std::max(b1.pMin.y, b2.pMax.y),
						  			std::max(b1.pMin.z, b2.pMax.z)));

	}

	template <typename T>
    inline bool Overlaps(const bounds3<T> &b1, const bounds3<T> &b2) 
    {
         bool x=(b1.pMax.x>= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
         bool y=(b1.pMax.y>= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
         bool z=(b1.pMax.z>= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
         return (x && y && z);
     }

     template <typename T>
     inline bool Inside(const point3<T> &p, const bounds3<T> &b)
     {
     	return (p.x>= b.pMin.x && p.x <= b.pMax.x &&
                        p.y>= b.pMin.y && p.y <= b.pMax.y &&
                        p.z>= b.pMin.z && p.z <= b.pMax.z);
     }

     template <typename T>
     bool InsideExclusive(const point3<T> &p, const bounds3<T> &b)
     {
     	return (p.x>= b.pMin.x && p.x <b.pMax.x &&
                        p.y>= b.pMin.y && p.y <b.pMax.y &&
                        p.z>= b.pMin.z && p.z <b.pMax.z);
     }

     template <typename T, typename U>
     inline bounds3<T> Expand(bounds3<T> &b, U delta)
     {
     	return bounds3<T>(b.pMin - pbrt::vector3<T>(delta, delta, delta),
     					b.pMax + pbrt::vector3<T>(delta, delta, delta));
     }

}

#include <bounds.cpp>