#pragma once

#include <algorithm> 
#include <cmath>

class interval
{
public:
	interval(float v);
	interval(float v0, float v1);
	interval operator+(const interval &i) const;
	interval operator-(const interval &i) const;
	interval operator*(const interval &i) const;


	float low;
	float high;
};

inline interval Sin(const interval &i) 
{
    float sinLow=std::sin(i.low), sinHigh=std::sin(i.high);
    if (sinLow> sinHigh)
      std::swap(sinLow, sinHigh);
    if (i.low <M_PI / 2 && i.high> M_PI / 2)
       sinHigh=1.;
    if (i.low <(3.f / 2.f) * M_PI && i.high> (3.f / 2.f) * M_PI)
       sinLow=-1.;
    return interval(sinLow, sinHigh);
}


inline interval Cos(const interval &i) 
{
    float cosLow=std::cos(i.low), cosHigh=std::cos(i.high);
    if (cosLow> cosHigh)
      std::swap(cosLow, cosHigh);
    if (i.low < 0 && i.high> 0)
       cosHigh=1.;
    if (i.low < M_PI && i.high>  M_PI)
       cosLow=-1.;
    return interval(cosLow, cosHigh);
}

void IntervalFindZeros(float c1, float c2, float c3, float c4,
           float c5, float theta, interval tInterval, float *zeros,
            int *zeroCount, int depth); 
