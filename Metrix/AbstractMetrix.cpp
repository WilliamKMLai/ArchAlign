/*
 * AbstractMetrix.h
 *
 *  Created on: Jul 14, 2010
 *      Author: jbard , wklai2
 */
#include <math.h>
#include <iostream>
#include "AbstractMetrix.h"
#include "MetrixFactory.h"

	/**
	 * Sets the Correlation type to an integer
	 * 1: Pearson
	 * 2: Spearman
	 * 3: Euclidean
	 */
	void AbstractMetrix::setCorrelation(int type) {
		CorrelationType = type;
	}
	/**
	 * Gets the Correlation Integer
	 */
	int AbstractMetrix::getCorrelation() {
		return CorrelationType;
	}
	/**
	 * Computes a numbers Factorial
	 */
	double AbstractMetrix::Factorial(double number) {
		double newnum = 0;
		if (number <= 1) {
			return 1;
		}
		newnum = number * Factorial(number - 1);
		return newnum;
	}

	/**
	 * do the correlation by calling the execute method on the AbstractMetrix object.
	 */
	double AbstractMetrix::execute(const double *x, const double *y, int length) {
		return Correlation(x, y, length);
	}


//TODO: REMOVE LATER, just for testing purposes
//int main()
//{
//
//MetrixFactory factory;
//AbstractMetrix *array = factory.createMetrix(3);
//
//  double x [] = {3.0 , 2.0 , 1.0};
//  double y [] = {1.0 , 2.0 , 3.0};
//  //{
//   //  &One(), &Two()
//  //};
//  //for (int i = 0; i < 2; i++)
// // {
//    double ret = array->execute(x,y,2);
//    printf("%f \n", ret);
//    return 0;
//};

 // }





