/*
 * AlignFactory.h
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#ifndef ALIGNFACTORY_H_
#define ALIGNFACTORY_H_
#include "ProgressiveAlignments/AbstractProgressiveAligner.h"
class AlignFactory {
public:
	AlignFactory();
	virtual ~AlignFactory();
	/**
		 * This is the crucial factory pattern method..pass in an integer, get a concrete AbstractMetrix object
		 * to preform method calls on.
		 */
		AbstractProgressiveAligner* createAligner(int method, int type);
};

#endif /* ALIGNFACTORY_H_ */
