/*
 * Pearson.h
 *This file was required because other metrix rely upon this metrix, and for forward declarations we need a header file
 *  Created on: Jul 15, 2010
 *      Author: jbard
 */

#ifndef PEARSON_H_
#define PEARSON_H_
#include <math.h>
#include "AbstractMetrix.h"
class Pearson : public AbstractMetrix {
public:
	double Correlation(const double *x, const double *y, int length);
};
	#endif /* PEARSON_H_ */
