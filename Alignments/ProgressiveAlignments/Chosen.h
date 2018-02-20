/*
 * Chosen.h
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#ifndef CHOSEN_H_
#define CHOSEN_H_
#include "../../Align.h"
#include "AbstractProgressiveAligner.h"

class Chosen : public AbstractProgressiveAligner{
public:
	Chosen();
	virtual ~Chosen();
	void Execute();
	void AlignFinal();
};

#endif /* CHOSEN_H_ */
