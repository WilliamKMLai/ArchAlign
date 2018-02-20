/*
 * Pearson.cpp
 *
 *  Created on: Jul 14, 2010
 *      Author: jbard,wklai2
 */
#include <math.h>
#include "Pearson.h"
/**
 * Concrete implemenatation of this Metrix. MUST TAKE IN THESE VARIABLES, AND RETURN A DOUBLE
 */
	double Pearson::Correlation(const double *x, const double *y, int length) {
		double xmean = 0, ymean = 0, s = 0, xv = 0, yv = 0;
		double t1, t2;
		// Mean
		for (int i = 0; i < length; i++) {
			xmean += x[i];
			ymean += y[i];
		}
		xmean /= length;
		ymean /= length;
		// numerator and denominator
		for (int i = 0; i < length; i++) {
			t1 = x[i] - xmean;
			t2 = y[i] - ymean;
			xv += pow(t1, 2);
			yv += pow(t2, 2);
			s += (t1 * t2);
		}
		if (xv == 0 || yv == 0) {
			return 0;
		} else {
			return (s / (sqrt(xv) * sqrt(yv)));
		}
	}



