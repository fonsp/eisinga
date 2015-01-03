#ifndef eMath_h
#define eMath_h

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

/*
 *  MatrixMath.h Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from 
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 */

class MatrixMath
{
public:
	//MatrixMath();
	void Print(float* A, int m, int n, String label);
	void Copy(float* A, int n, int m, float* B);
	void Multiply(float* A, float* B, int m, int p, int n, float* C);
	void Add(float* A, float* B, int m, int n, float* C);
	void Subtract(float* A, float* B, int m, int n, float* C);
	void Transpose(float* A, int m, int n, float* C);
	void Scale(float* A, int m, int n, float k);
	int Invert(float* A, int n);
};

extern MatrixMath Matrix;
#endif
