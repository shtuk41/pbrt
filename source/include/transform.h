#pragma once

#include <iostream>
#include <TemplateInst.h>
#include "ray.h"

namespace pbrt
{
	struct matrix4x4
	{
		matrix4x4();
		matrix4x4(float mat[4][4]);
		matrix4x4(float t00, float t01, float t02, float t03,
					float t10, float t11, float t12, float t13,
					float t20, float t21, float t22, float t23,
					float t30, float t31, float t32, float t33);
		static matrix4x4 Mul(const matrix4x4 &m1, const matrix4x4 &m2);
		friend bool Inverse(const matrix4x4 &in, matrix4x4 &invOut);
		void print() const;


		float m[4][4];
	};

	class transform;

	matrix4x4 Transpose(const matrix4x4 &m);
	transform Translate(const vector3f &delta);

	class transform
	{
	public:
		transform() {}
		transform(const float mat[4][4]);
		transform(const matrix4x4 &m);
		transform(const matrix4x4 &m, const matrix4x4 &mInv);
		friend transform Inverse(const transform &I);
		friend transform Tranpose(const transform &t);
		friend transform Translate(const vector3f &delta);
		transform Scale(float x, float y, float z);
		bool HasScale() const;
		transform RotateX(float theta);
		transform RotateY(float theta);
		transform RotateZ(float theta);
		//transform Rotate(float theta, const vector3f &axis);
		transform LookAt(const point3f &pos, const point3f &look, const vector3f &up);

		template <typename T>
		point3<T> operator()(const point3<T> &p) const
		{
			 T x=p.x, y=p.y, z=p.z;
			 T xp=m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z + m.m[0][3];
	         T yp=m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z + m.m[1][3];
	         T zp=m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z + m.m[2][3];
	         T wp=m.m[3][0]*x + m.m[3][1]*y + m.m[3][2]*z + m.m[3][3];
	         
	         if (wp == 1) 
	         {
	         	return point3<T>(xp, yp, zp);
	         }
	         else 
	         {
	         	return point3<T>(xp, yp, zp) / wp;
	         }
		}

		template <class T>
		vector3<T> operator()(const vector3<T> &v) const
		{
			T x=v.x, y=v.y, z=v.z;
	    
	        return vector3<T>(m.m[0][0]*x + m.m[0][1]*y + m.m[0][2]*z,
	                          m.m[1][0]*x + m.m[1][1]*y + m.m[1][2]*z,
	                          m.m[2][0]*x + m.m[2][1]*y + m.m[2][2]*z);
		}

		template <class T>
		normal3<T> operator()(const normal3<T> &n)
		{
			T x=n.x, y=n.y, z=n.z;
         	return normal3<T>(mInv.m[0][0]*x + mInv.m[1][0]*y + mInv.m[2][0]*z,
                                mInv.m[0][1]*x + mInv.m[1][1]*y + mInv.m[2][1]*z,
                                mInv.m[0][2]*x + mInv.m[1][2]*y + mInv.m[2][2]*z);
		}

		pbrt::ray operator()(const ray &r) const;
		bounds3f operator()(const bounds3f &b) const;
		transform operator*(const transform &t2) const;
		bool SwapsHandedness() const;

		friend bool operator!=(const transform &t1, const transform &t2);

		const matrix4x4 & GetMatrix() const { return m;}
		const matrix4x4 & GetInverse() const {return mInv;}

	private:
		matrix4x4 m;
		matrix4x4 mInv;
	};


	inline bool operator!=(const transform &t1, const transform &t2)
	{
		bool eq = true;

		for (int ii = 0; ii < 4; ii++)
		{
			for (int jj = 0; jj < 4; jj++)
			{
				eq &= t1.m.m[ii][jj] == t2.m.m[ii][jj];
			}
		}

		return !eq;
	}

	
}