/*
 * Euclidean.cpp
 *This file computes Euclidean distance? Not sure, Will wrote it
 *  Created on: Jul 15, 2010
 *      Author: jbard, wklai2
 */
#include <math.h>
#include "AbstractMetrix.h"
class Euclidean : public AbstractMetrix {
/**
 * Concrete implemenatation of this Metrix. MUST TAKE IN THESE VARIABLES, AND RETURN A DOUBLE
 */
	double Correlation(const double *x, const double *y, int length) {
		double distance = 0;
		for (int i = 0; i < length; i++) {
			distance += pow((x[i] - y[i]), 2);
		}

		return (sqrt(distance));
	}
};

