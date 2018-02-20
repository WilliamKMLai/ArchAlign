/*
 * Seed.h
 *
 *  Created on: Jul 19, 2010
 *      Author: jbard
 */

#ifndef SEED_H_
#define SEED_H_
#include "../../Align.h"
#include "AbstractProgressiveAligner.h"

class Seed : public AbstractProgressiveAligner{
public:
	Seed();
	virtual ~Seed();
	void Execute();
	void AlignFinal();
};


#endif /* SEED_H_ */
