#pragma once

#include <iostream>
#include <TemplateInst.h>

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

	matrix4x4 Transpose(const matrix4x4 &m);

	class transform
	{
	public:
		transform() {}
		transform(const float mat[4][4]);
		transform(const matrix4x4 &m);
		transform(const matrix4x4 &m, const matrix4x4 &mInv);
		friend transform Inverse(const transform &I);
		friend transform Tranpose(const transform &t);
		transform Translate(const vector3f &delta);
		transform Scale(float x, float y, float z);
		//bool HasScale() const;
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

	private:
		matrix4x4 m;
		matrix4x4 mInv;
	};

	
}