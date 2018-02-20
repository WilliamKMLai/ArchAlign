/*
 * MetrixFactory.h
 *
 *  Created on: Jul 15, 2010
 *      Author: jbard
 */

#ifndef METRIXFACTORY_H_
#define METRIXFACTORY_H_
#include "AbstractMetrix.h"
class MetrixFactory {
public:
	MetrixFactory();
	virtual ~MetrixFactory();
	/**
	 * This is the crucial factory pattern method..pass in an integer, get a concrete AbstractMetrix object
	 * to preform method calls on.
	 */
	AbstractMetrix* createMetrix(int correlationType);
};

#endif /* METRIXFACTORY_H_ */
