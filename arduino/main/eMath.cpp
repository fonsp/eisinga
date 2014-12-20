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