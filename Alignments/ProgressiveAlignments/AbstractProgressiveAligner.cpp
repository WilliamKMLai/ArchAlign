/*
 * AbstractAligner.cpp
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#include "AbstractProgressiveAligner.h"
#include <vector>
#include <string>
#include "../../Metrix/AbstractMetrix.h"

AbstractProgressiveAligner::AbstractProgressiveAligner() {
	// TODO Auto-generated constructor stub

}

AbstractProgressiveAligner::~AbstractProgressiveAligner() {
	// TODO Auto-generated destructor stub
}

void AbstractProgressiveAligner::setReverseControl(bool boolean) {
	ReverseControl = boolean;
}
void AbstractProgressiveAligner::setSlidingWindow(int i) {
	SlidingWindow = i;
}
void AbstractProgressiveAligner::setType(int type) {
	Type = type;
}

void AbstractProgressiveAligner::setCorrelation(AbstractMetrix* corr) {
	Correlation = corr;
}

void AbstractProgressiveAligner::setPartnerName(string partner) {
	partnerName = partner;
}
void AbstractProgressiveAligner::setBestP(double best) {
	bestP = best;
}
void AbstractProgressiveAligner::setIndex(int i) {
	index = i;
}
void AbstractProgressiveAligner::setMaster(vector<Node> master) {
	MasterRegion = master;
}
void AbstractProgressiveAligner::setTransformed(vector<Node>transformed){
	TransformedRegion = transformed;
}
void AbstractProgressiveAligner::setConfig(Config params){
	Parameters = params;
}
void AbstractProgressiveAligner::setBestCorrelation(double best) {
	bestCorrelation = best;

}
void AbstractProgressiveAligner::setBestPairCorrelation(
		double bestpairCorrelation) {
	bestpair_correlation = bestpairCorrelation;
}


void AbstractProgressiveAligner::loadarray(vector<Node> & region, double currentregion[], int windowsize,int windowstart, int currentindex, bool reversal) {
	vector<double> tempseq = region[currentindex].getSeq();
	if (!reversal) {
		for (int x = windowstart; x < (windowstart + windowsize); x++) {
			currentregion[x - windowstart] = tempseq[x];
		}
	} else {
		int index = 0;
		for (int x = (windowstart + windowsize - 1); x >= windowstart; x--) {
			currentregion[index] = tempseq[x];
			index++;
		}
	}
}
//void AbstractProgressiveAligner::setArgs(char* arg){
//		args = arg;
//	}
