#include "math.h"
#include "eMath.h"

XYZ::XYZ(double fx, double fy, double fz) {
	x = fx;
	y = fy;
	z = fz;
}

XYZ::XYZ(int fx, int fy, int fz) {
	x = double(fx);
	y = double(fy);
	z = double(fz);
}

XYZ::XYZ() {
	x = y = z = 0.0;
}

XYZ XYZ::Subtract(XYZ a, XYZ b) {
	return XYZ(a.x - b.x, a.y - b.y, a.z - b.z);
}

XYZ FindCenter(XYZ a, XYZ b, XYZ c, XYZ d) {
	XYZ p[4] = {a, b, c, d};
	return FindCenter(p);
}

XYZ FindCenter(XYZ *p) {
	int i;
	XYZ c;
	double r;
	double **a=NULL,m11,m12,m13,m14,m15;
	
	a = (double **) malloc(4*sizeof(double *));
	for(i = 0; i < 4; i++) {
		a[i] = (double *) malloc(4*sizeof(double));
	}
	
	for(i = 0; i < 4; i++) {
		a[i][0] = p[i].x;
		a[i][1] = p[i].y;
		a[i][2] = p[i].z;
		a[i][3] = 1;
	}
	m11 = Determinant(a, 4);
	
	for(i = 0; i < 4; i++) {
		a[i][0] = p[i].x * p[i].x + p[i].y * p[i].y + p[i].z * p[i].z;
		a[i][1] = p[i].y;
		a[i][2] = p[i].z;
		a[i][3] = 1;
	}
	m12 = Determinant(a, 4);
	
	for(i = 0; i < 4; i++) {
		a[i][0] = p[i].x;
		a[i][1] = p[i].x * p[i].x + p[i].y * p[i].y + p[i].z * p[i].z;
		a[i][2] = p[i].z;
		a[i][3] = 1;
	}
	m13 = Determinant(a, 4);
	
	for(i = 0; i < 4; i++) {
		a[i][0] = p[i].x;
		a[i][1] = p[i].y;
		a[i][2] = p[i].x * p[i].x + p[i].y * p[i].y + p[i].z * p[i].z;
		a[i][3] = 1;
	}
	m14 = Determinant(a, 4);
	
	for(i = 0; i < 4; i++) {
		a[i][0] = p[i].x * p[i].x + p[i].y * p[i].y + p[i].z * p[i].z;
		a[i][1] = p[i].x;
		a[i][2] = p[i].y;
		a[i][3] = p[i].z;
	}
	m15 = Determinant(a, 4);
	
	c.x = 0.5 * m12 / m11;
	c.y = 0.5 * m13 / m11;
	c.z = 0.5 * m14 / m11;
	r = sqrt(c.x * c.x + c.y * c.y + c.z * c.z - m15 / m11);
	
	for(i = 0; i < 4; i++) {
		free(a[i]);
	}
	free(a);
	
	return c;
}

double Determinant(double **a, int n) {
	int i,j,j1,j2;
	double det = 0.0;
	double **m = NULL;
	
	if(n < 1) {
		// error
	} else if(n == 1) {
		det = a[0][0];
	} else if(n == 2) {
		det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	} else {
		for(j1=0; j1 < n; j1++) {
			m = (double **) malloc((n - 1) * sizeof(double *));
			for(i = 0; i < n - 1; i++) {
				m[i] = (double *) malloc((n - 1) * sizeof(double));
			}
			for(i = 1; i < n; i++) {
				j2 = 0;
				for(j = 0; j < n; j++) {
					if(j == j1) {
						continue;
					}
					m[i - 1][j2] = a[i][j];
					j2++;
				}
			}
			det += pow(-1.0, 1.0 + j1 + 1.0) * a[0][j1] * Determinant(m, n - 1);
			for(i = 0; i < n - 1; i++) {
				free(m[i]);
			}
			free(m);
		}
	}
	return det;
}

/*
 *  MatrixMath.cpp Library for Matrix Math
 *
 *  Created by Charlie Matlack on 12/18/10.
 *  Modified from code by RobH45345 on Arduino Forums, algorithm from 
 *  NUMERICAL RECIPES: The Art of Scientific Computing.
 */

#define NR_END 1

MatrixMath Matrix;			// Pre-instantiate

// Matrix Printing Routine
// Uses tabs to separate numbers under assumption printed float width won't cause problems
void MatrixMath::Print(float* A, int m, int n, String label){
	// A = input matrix (m x n)
	int i,j;
	Serial.println();
	Serial.println(label);
	for (i=0; i<m; i++){
		for (j=0;j<n;j++){
			Serial.print(A[n*i+j]);
			Serial.print("\t");
		}
		Serial.println();
	}
}

void MatrixMath::Copy(float* A, int n, int m, float* B)
{
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			B[n*i+j] = A[n*i+j];
		}
}

//Matrix Multiplication Routine
// C = A*B
void MatrixMath::Multiply(float* A, float* B, int m, int p, int n, float* C)
{
	// A = input matrix (m x p)
	// B = input matrix (p x n)
	// m = number of rows in A
	// p = number of columns in A = number of rows in B
	// n = number of columns in B
	// C = output matrix = A*B (m x n)
	int i, j, k;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			C[n*i+j]=0;
			for (k=0;k<p;k++)
				C[n*i+j]= C[n*i+j]+A[p*i+k]*B[n*k+j];
		}
}


//Matrix Addition Routine
void MatrixMath::Add(float* A, float* B, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A+B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]+B[n*i+j];
}


//Matrix Subtraction Routine
void MatrixMath::Subtract(float* A, float* B, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// B = input matrix (m x n)
	// m = number of rows in A = number of rows in B
	// n = number of columns in A = number of columns in B
	// C = output matrix = A-B (m x n)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[n*i+j]=A[n*i+j]-B[n*i+j];
}


//Matrix Transpose Routine
void MatrixMath::Transpose(float* A, int m, int n, float* C)
{
	// A = input matrix (m x n)
	// m = number of rows in A
	// n = number of columns in A
	// C = output matrix = the transpose of A (n x m)
	int i, j;
	for (i=0;i<m;i++)
		for(j=0;j<n;j++)
			C[m*j+i]=A[n*i+j];
}

void MatrixMath::Scale(float* A, int m, int n, float k)
{
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			A[n*i+j] = A[n*i+j]*k;
}


//Matrix Inversion Routine
// * This function inverts a matrix based on the Gauss Jordan method.
// * Specifically, it uses partial pivoting to improve numeric stability.
// * The algorithm is drawn from those presented in 
//	 NUMERICAL RECIPES: The Art of Scientific Computing.
// * The function returns 1 on success, 0 on failure.
// * NOTE: The argument is ALSO the result matrix, meaning the input matrix is REPLACED
int MatrixMath::Invert(float* A, int n)
{
	// A = input matrix AND result matrix
	// n = number of rows = number of columns in A (n x n)
	int pivrow;		// keeps track of current pivot row
	int k,i,j;		// k: overall index along diagonal; i: row index; j: col index
	int pivrows[n]; // keeps track of rows swaps to undo at end
	float tmp;		// used for finding max value and making column swaps

	for (k = 0; k < n; k++)
	{
		// find pivot row, the row with biggest entry in current column
		tmp = 0;
		for (i = k; i < n; i++)
		{
			if (abs(A[i*n+k]) >= tmp)	// 'Avoid using other functions inside abs()?'
			{
				tmp = abs(A[i*n+k]);
				pivrow = i;
			}
		}

		// check for singular matrix
		if (A[pivrow*n+k] == 0.0f)
		{
			Serial.println("Inversion failed due to singular matrix");
			return 0;
		}

		// Execute pivot (row swap) if needed
		if (pivrow != k)
		{
			// swap row k with pivrow
			for (j = 0; j < n; j++)
			{
				tmp = A[k*n+j];
				A[k*n+j] = A[pivrow*n+j];
				A[pivrow*n+j] = tmp;
			}
		}
		pivrows[k] = pivrow;	// record row swap (even if no swap happened)

		tmp = 1.0f/A[k*n+k];	// invert pivot element
		A[k*n+k] = 1.0f;		// This element of input matrix becomes result matrix

		// Perform row reduction (divide every element by pivot)
		for (j = 0; j < n; j++)
		{
			A[k*n+j] = A[k*n+j]*tmp;
		}

		// Now eliminate all other entries in this column
		for (i = 0; i < n; i++)
		{
			if (i != k)
			{
				tmp = A[i*n+k];
				A[i*n+k] = 0.0f;  // The other place where in matrix becomes result mat
				for (j = 0; j < n; j++)
				{
					A[i*n+j] = A[i*n+j] - A[k*n+j]*tmp;
				}
			}
		}
	}

	// Done, now need to undo pivot row swaps by doing column swaps in reverse order
	for (k = n-1; k >= 0; k--)
	{
		if (pivrows[k] != k)
		{
			for (i = 0; i < n; i++)
			{
				tmp = A[i*n+k];
				A[i*n+k] = A[i*n+pivrows[k]];
				A[i*n+pivrows[k]] = tmp;
			}
		}
	}
	return 1;
}
