/*
 * MetrixFactory.cpp
 * This class is responsible for generating a particular implementation of AbstractMetrix. Simply
 * pass in an integer corresponding to the metrix you would like to use, and it will return an object
 * of AbstractMetrix which you can call methods on. It hides the concrete implementation of the Metrix
 * from the user, allowing interchangeable parts.
 *
 *  Created on: Jul 15, 2010
 *      Author: jbard
 */

//TODO: Every time we add a new Metrix, we need to #include it, and add it to the if/else statement
#include "MetrixFactory.h"
#include "Spearman.cpp"
#include "Pearson.h"
#include "Euclidean.cpp"

using namespace std;

// Default constructor.. do nothing
MetrixFactory::MetrixFactory() {
	// TODO Auto-generated constructor stub
}
// Default deconstructor.. i dont even know what a deconstructor is
MetrixFactory::~MetrixFactory() {
	// TODO Auto-generated destructor stub
}

/**
 * This method return an AbstractMetrix object, hiding the type of Metrix we are utilizing.
 * All Metrix implementations are responsible for implementing a method:
 * Correlation(const *double , const *double, int length)
 */
AbstractMetrix* MetrixFactory::createMetrix(int correlationType) {
	if (correlationType == 1) {
		return new Pearson();
	} else if (correlationType == 2) {
		return new Spearman();
	} else if (correlationType == 3) {
		return new Euclidean();
	} else {
		cout<<"Invalid Correlation Selected!!!\n";
		exit(0);
	}
}
