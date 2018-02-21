#pragma once

#include <TemplateInst.h>


namespace pbrt
{
	class shape
	{
	public:
		bool reverseOrientation;
		bool transformSwapsHandedness;
	};

	class mediuminterface
	{

	};

	struct interaction
	{
		interaction(const point3f &p, 
					const normal3f &n, 
					const vector3f &pError,
					const vector3f &wo, 
					float time, 
					const mediuminterface &mediumInterface);

		point3f p;
		float time;
		vector3f pError;
		vector3f wo;
		normal3f n;
		bool IsSurfaceInteraction() const;
		mediuminterface mediumInterface;

	};

	struct _shading
	{
		_shading() :n(vector3f(0,0,0)),
					dndu(vector3f(0,0,0)),
					dndv(vector3f(0,0,0)) {}
		normal3f n;
		vector3f dpdu, dpdv;
		normal3f dndu, dndv;
	};

	

	class surfaceinteraction : public interaction
	{
		public:
			surfaceinteraction(const point3f &p,
		    const vector3f &pError, const point2f &uv, const vector3f &wo,
		    const vector3f &dpdu, const vector3f &dpdv,
		    const normal3f &dndu, const normal3f &dndv,
		    float time, const shape *_shapePtr);

		    void SetShadingGeometry(const vector3f &dpdus,
        							const vector3f &dpdvs, 
        							const normal3f &dndus,
        							const normal3f &dndvs, 
        							bool orientationIsAuthoritative); 



			point2f uv;
			vector3f dpdu, dpdv;
			normal3f dndu, dndv;
			const shape* shapePtr;
			_shading shading;
			
	};

}