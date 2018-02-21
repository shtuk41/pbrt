	#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

//#include <normal.h>
#include <interaction.h>

namespace pbrt
{

	interaction::interaction(const point3f &p, const normal3f &n, const vector3f &pError,
						const vector3f &wo, float time, const mediuminterface &mediumInterface)
		:p(p), time(time), pError(pError), wo(wo), n(n), mediumInterface(mediumInterface) {}


	bool interaction::IsSurfaceInteraction() const
	{
		return n != normal3f(vector3f(0,0,0));

	}

	surfaceinteraction::surfaceinteraction(const point3f &p,
		    const vector3f &pError, const point2f &uv, const vector3f &wo,
		    const vector3f &dpdu, const vector3f &dpdv,
		    const normal3f &dndu, const normal3f &dndv,
		    float time, const shape *_shapePtr)
		  		: interaction(p, 
		  				normal3f(Normalize(Cross(dpdu, dpdv))), 
		  				pError, 
		  				wo,
		                time, 
		                mediuminterface()),
		    		uv(uv), 
		    		dpdu(dpdu), 
		    		dpdv(dpdv), 
		    		dndu(dndu), 
		    		dndv(dndv),
		    		shapePtr(_shapePtr)
	{
		// Initialize shading geometry from true geometry 118〉

		shading.n = n;
		shading.dpdu=dpdu;
   		shading.dpdv=dpdv;
   		shading.dndu=dndu;
   		shading.dndv=dndv;

 		//Adjust normal based on orientation and handedness 119〉
 		if (shapePtr && (shapePtr->reverseOrientation ^ shapePtr->transformSwapsHandedness))
 		{
 			n *= -1.0f;
 			shading.n *= -1.0f;
 		}

	}

	void surfaceinteraction::SetShadingGeometry(const vector3f &dpdus,
        const vector3f &dpdvs, const normal3f &dndus,
        const normal3f &dndvs, bool orientationIsAuthoritative)
	{
         //〈Computeshading.nfor SurfaceInteraction 119〉
		shading.n=normal3f(Normalize(Cross(dpdus, dpdvs)));
		
		if (shapePtr && (shapePtr-> reverseOrientation ^
		                       shapePtr->transformSwapsHandedness))
		{
		    shading.n = -shading.n;
		}
		  
		if (orientationIsAuthoritative)
		{
		    n = FaceForward(n, vector3f(shading.n));
		}
		else
		{
		    shading.n = FaceForward(shading.n, vector3f(n));
		}	

         //〈Initialize shading partial derivative values 119〉

		shading.dpdu = dpdus;
		shading.dpdv = dpdvs;
		shading.dndu = dndus;
		shading.dndv = dndvs;
    }
}


