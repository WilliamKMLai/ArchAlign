/*
 * AbstractAligner.h
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#ifndef ABSTRACTPROGRESSIVEALIGNER_H_
#define ABSTRACTPROGRESSIVEALIGNER_H_
#include <vector>
#include "../../Metrix/AbstractMetrix.h"
#include <string>
#include "../../Node.h"
#include "../../Config.h"

using namespace std;
class AbstractProgressiveAligner {
public:
	AbstractProgressiveAligner();
	virtual ~AbstractProgressiveAligner();
	string bestseedone;
	string bestseedtwo;
	int SlidingWindow;
	bool ReverseControl;
	int Type;
	AbstractMetrix* Correlation;
	string partnerName;
	double bestP;
	int index;
	vector<Node> MasterRegion;
	vector<Node> TransformedRegion;
	double bestCorrelation;
	double bestpair_correlation;
	Config Parameters;
	char* args [];

	/** ALL Aligments must implement Align
	 * @throws FileNotFoundException */
	virtual void Execute() = 0;
	virtual void AlignFinal() = 0;
	// Sets the if it is a forward or reverse strand
	void setReverseControl(bool boolean);
	// Sets the sliding window variable
	void setSlidingWindow(int i);
	// Sets the Type of alignment to be done
	void setType(int type);
	// Sets the metrix type to utilize
	void setCorrelation(AbstractMetrix* corr);
	// Sets the partner seed
	void setPartnerName(string partner);
	// sets the bestP value for best-paired alignments
	void setBestP(double best);
	// sets the index..?
	void setIndex(int i);
	// sets the master region vector
	void setMaster(vector<Node> master);
	// sets transformed region
	void setTransformed(vector<Node>transformed);
	// sets the best correlation value
	void setBestCorrelation(double best);
	//sets the best pair correlation double value
	void setBestPairCorrelation(double bestpairCorrelation);
	// set Config File
	void setConfig(Config params);
	//void setArgs(char* arg);
	void loadarray(vector<Node> & region, double currentregion[], int windowsize,int windowstart, int currentindex, bool reversal);
};

#endif /* ABSTRACTPROGRESSIVEALIGNER_H_ */
