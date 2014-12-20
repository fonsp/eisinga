#include "math.h"

#define TWOPI 6.283185307179586476925287
#define PID2 1.570796326794896619231322

struct XYZ {
	double x,y,z;
	
	XYZ(double fx, double fy, double fz);
	XYZ(int fx, int fy, int fz);
	XYZ();
	
	static XYZ Subtract(XYZ a, XYZ b);
};

double Determinant(double **, int);

XYZ FindCenter(XYZ a, XYZ b, XYZ c, XYZ d);
XYZ FindCenter(XYZ *p);
