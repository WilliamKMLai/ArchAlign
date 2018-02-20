/*
 * AbstractMetrix.h
 *
 *  Created on: Jul 14, 2010
 *      Author: jbard
 */

#ifndef ABSTRACTMETRIX_H_
#define ABSTRACTMETRIX_H_

#include <math.h>
#include <iostream>

class AbstractMetrix {
public:
	AbstractMetrix *array;
	int CorrelationType;
	double x [];
	double y [];
	AbstractMetrix(){
	}

// Removed Non-Virtual Destructor from Virtual Class
	~AbstractMetrix(){

	}
	void setCorrelation(int type);
	int getCorrelation();
	double Factorial(double number);
	virtual double Correlation(const double *x, const double *y, int length) = 0;
	double execute(const double *x, const double *y, int length);
private:

};

#endif /*METRIX_H_*/

