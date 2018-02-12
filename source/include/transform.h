#pragma once

namespace pbrt
{
	struct matrix4x4
	{
		matrix4x4(float mat[4][4]);
		matrix4x4(float t00, float t01, float t02, float t03,
					float t10, float t11, float t12, float t13,
					float t20, float t21, float t22, float t23,
					float t30, float t31, float t32, float t33);
		static matrix4x4 Mul(const matrix4x4 &m1, const matrix4x4 &m2);
		friend matrix4x4 Inverse(const matrix4x4 &);


		float m[4][4];
	};

	matrix4x4 Transpose(const matrix4x4 &m)
	{
		return matrix4x4(m.m[0][0], m.m[1][0], m.m[2][0],m.m[3][0],
						m.m[0][1], m.m[1][1], m.m[2][1],m.m[3][1],
						m.m[0][2], m.m[1][2], m.m[2][2],m.m[3][2],
						m.m[0][3], m.m[1][3], m.m[2][3],m.m[3][3]);
	}

	class transform
	{
	public:


		Matrix4x4 m;
		Matrix4x4 mInv;
	};
}