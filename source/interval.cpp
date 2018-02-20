#if defined (_MSC_VER_)
#include "stdafx.h"
#endif

#include <cmath>
#include <interval.h>

interval::interval(float v) : low(v), high(v) {}

interval::interval(float v0, float v1) : low(std::min(v0, v1)), high(std::max(v0, v1)) {}

interval interval::operator+(const interval &i) const
{
	return interval(low + i.low, high + i.high);
}

interval interval::operator-(const interval &i) const
{
	return interval(low - i.low, high - i.high);
}

interval interval::operator*(const interval &i) const
{
	return interval(std::min(std::min(low * i.low, high * i.low),
                        std::min(low * i.high, high * i.high)),
                        std::max(std::max(low * i.low, high * i.low),
                        std::max(low * i.high, high * i.high)));
}



void IntervalFindZeros(float c1, float c2, float c3, float c4,
           float c5, float theta, interval tInterval, float *zeros,
            int *zeroCount, int depth=8) 
{
      //〈Evaluate motion derivative in interval form, return if no zeros 113〉
      
	interval range=interval(c1) +
      (interval(c2) + interval(c3) * tInterval) *
        Cos(interval(2 * theta) * tInterval) +
      (interval(c4) + interval(c5) * tInterval) *
        Sin(interval(2 * theta) * tInterval);
    
    if (range.low> 0. || range.high <0. || range.low == range.high)
      return;


    if (depth> 0) 
    {
        //〈SplittIntervaland check both resulting intervals 114〉
        float mid=(tInterval.low + tInterval.high) * 0.5f;
     	IntervalFindZeros(c1, c2, c3, c4, c5, theta,
        interval(tInterval.low, mid), zeros, zeroCount, depth - 1);
     	IntervalFindZeros(c1, c2, c3, c4, c5, theta,
        interval(mid, tInterval.high), zeros, zeroCount, depth - 1);
         
    } 
    else 
    {
           //〈Use Newton's method to refine zero 114〉
        float tNewton=(tInterval.low + tInterval.high) * 0.5f;
   		for (int i=0; i <4; ++i) {
        
        float fNewton=c1 +
            (c2 + c3 * tNewton) * std::cos(2.f * theta * tNewton) +
            (c4 + c5 * tNewton) * std::sin(2.f * theta * tNewton);
        
        float fPrimeNewton = (c3 + 2 * (c4 + c5 * tNewton) * theta) *
                     		std::cos(2.f * tNewton * theta) +
            				(c5 - 2 * (c2 + c3 * tNewton) * theta) *
                     		std::sin(2.f * tNewton * theta);
        
        if (fNewton == 0 || fPrimeNewton == 0)
           break;

        tNewton=	tNewton - fNewton / fPrimeNewton;
     }
   	
   	zeros[*zeroCount]=tNewton;
     (*zeroCount)++;	

     }
 }