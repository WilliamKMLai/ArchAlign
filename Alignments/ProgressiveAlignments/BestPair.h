/*
 * BestPair.h
 *
 *  Created on: Jul 19, 2010
 *      Author: jbard
 */

#ifndef BESTPAIR_H_
#define BESTPAIR_H_
#include "../../Align.h"
#include "AbstractProgressiveAligner.h"

class BestPair : public AbstractProgressiveAligner{
public:
	BestPair();
	virtual ~BestPair();
	void Execute();
	void AlignFinal();
};


#endif /* SEED_H_ */
