/*
 * AlignFactory.cpp
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#include "AlignFactory.h"
#include "ProgressiveAlignments/Chosen.h"
#include "ProgressiveAlignments/Seed.h"
#include "ProgressiveAlignments/BestPair.h"
#include "ProgressiveAlignments/AbstractProgressiveAligner.h"
AlignFactory::AlignFactory() {
	// TODO Auto-generated constructor stub

}

AlignFactory::~AlignFactory() {
	// TODO Auto-generated destructor stub
}

AbstractProgressiveAligner* AlignFactory::createAligner(int method, int type) {
	// if progressive alignment
	if (method == 1) {
		// if type of alignment is seed
		if (type == 1) {
			return new Seed();
		// if type is chosen etc.
		} else if (type == 2) {
			return new BestPair();
		} else if (type == 3) {
			return new Chosen();
		}
	} else if (method == 2) {
		//TODO IMPLEMENT NON PROGRESSIVE alignments
	}
	else {
		cout<<"Invalid Alignment Selected!!!\n";
		exit(0);
	}
}
