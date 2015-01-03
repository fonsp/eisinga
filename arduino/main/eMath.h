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
	void Print(double* A, int m, int n, String label);
	void Copy(double* A, int n, int m, double* B);
	void Multiply(double* A, double* B, int m, int p, int n, double* C);
	void Add(double* A, double* B, int m, int n, double* C);
	void Subtract(double* A, double* B, int m, int n, double* C);
	void Transpose(double* A, int m, int n, double* C);
	void Scale(double* A, int m, int n, double k);
	int Invert(double* A, int n);
};

extern MatrixMath Matrix;
#endif
