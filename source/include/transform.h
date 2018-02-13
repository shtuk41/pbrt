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

	private:
		matrix4x4 m;
		matrix4x4 mInv;
	};
}