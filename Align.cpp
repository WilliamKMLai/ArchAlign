#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Config.h"
#include "Metrix/MetrixFactory.h"
#include "Metrix/AbstractMetrix.h"
#include "Node.h"
#include "Transform.h"

#include "Align.h"

Align::Align(Config input) {
	Parameters = input;
	FINAL_Align = false;
	CorrelationProfile = 0;
	vector<Node> MasterRegion(countlines(input.getInputFile()));
	vector<string> OutputOrder(0);
}

Align::~Align() {
}

void Align::setFinal(bool time) {
	FINAL_Align = time;
}

bool Align::getFinal() {
	return FINAL_Align;
}

vector<Node> Align::getRegion() {
	return MasterRegion;
}

vector<string> Align::getOrder() {
	return OutputOrder;
}

double Align::getProfile() {
	return CorrelationProfile;
}

double Align::ChosenAlign(string seedone, string seedtwo) {
	cout << "Loading Regions\n";
	int loopcontrol = countlines(Parameters.getInputFile());
	int length = loopcontrol;
	loadRegions(Parameters.getInputFile());
	cout << "Regions Loaded\n";

	Transform Data;
	Data.setGenomeSize(Parameters.getGenomeSize());
	Data.setTotalTags(Parameters.getTotalTags());
	MasterRegion = Data.TransformControl(MasterRegion, Parameters.getTransformationType());

	//JB WAZ HERE - Fixed the Instantiation from the old Metrix to the new
	MetrixFactory metrixFactory;
	AbstractMetrix* Correlation = metrixFactory.createMetrix(Parameters.getMetricType());
	//Metrix Correlation(Parameters.getMetricType());


	if (FINAL_Align) {
		OutputOrder.push_back(seedone);
		OutputOrder.push_back(seedtwo);
	}

	double* averageTSS = new double[Parameters.getSlidingWindow()];
	for (int x = 0; x < loopcontrol; x++) { //cout<<"Index:\t"<<x+1<<endl;
		//If x == 0, find seed pair
		if (x == 0) {
			double bestPscore = -100;
			if (Parameters.getMetricType() == 3) {
				bestPscore = 999999999;
			}
			int bestShift = 0, bestOuterShift = 0;
			int primaryseed = -1, secondaryseed = -1;
			bool outerreverse = false, innerreverse = false;
			double* coreTSS = new double[Parameters.getSlidingWindow()];
			for (int y = 0; y < (int)MasterRegion.size(); y++) {
				if (MasterRegion[y].getName().compare(seedone) == 0) {
					primaryseed = y;
				}
				if (MasterRegion[y].getName().compare(seedtwo) == 0) {
					secondaryseed = y;
				}
			}
			if(primaryseed == -1 || secondaryseed == -1)
			{	cout<<"Seeds Not Found...\nExiting Program\n";
				exit(0);
			}
			cout << "Seeds Planted\n";

			//Identify the best shift given a user chosen set of seeds
			for (int outer = 0; outer <= ((int)MasterRegion[x].getSeq().size() - Parameters.getSlidingWindow()); outer++) {
				loadarray(coreTSS, outer, primaryseed, false);
				for (int inner = 0; inner <= ((int)MasterRegion[primaryseed].getSeq().size()
								- Parameters.getSlidingWindow()); inner++) { //Load up TSS:search array with 100 nucleotide positions to compare against
					double* searchTSS = new double[Parameters.getSlidingWindow()];
					loadarray(searchTSS, inner, secondaryseed, false);
					//Pearson correlation here
					double tempP = Correlation->Correlation(coreTSS, searchTSS, Parameters.getSlidingWindow());
					//If correlation is >= best P score, overwrite values with new scores
					if ((tempP >= bestPscore && (Parameters.getMetricType() == 1 || Parameters.getMetricType() == 2))
							|| (tempP <= bestPscore	&& Parameters.getMetricType() == 3)) {
						bestPscore = tempP;
						bestShift = inner;
						bestOuterShift = outer;
						outerreverse = false;
						innerreverse = false;
					}
					if (Parameters.getReversalStatus()) {
						double* rsearchTSS1 = new double[Parameters.getSlidingWindow()];
						loadarray(rsearchTSS1, outer, primaryseed, true);
						tempP = Correlation->Correlation(searchTSS, rsearchTSS1, Parameters.getSlidingWindow());
						//If correlation is >= best P score, overwrite values with new scores
						if ((tempP >= bestPscore && (Parameters.getMetricType() == 1 || Parameters.getMetricType() == 2))
									|| (tempP <= bestPscore && Parameters.getMetricType() == 3)) {
							bestPscore = tempP;
							bestShift = inner;
							bestOuterShift = outer;
							outerreverse = true;
							innerreverse = false;
						}
						double* rsearchTSS2 = new double[Parameters.getSlidingWindow()];
						loadarray(rsearchTSS2, inner, secondaryseed, true);
						tempP = Correlation->Correlation(rsearchTSS2, coreTSS,	Parameters.getSlidingWindow());
						//If correlation is >= best P score, overwrite values with new scores
						if ((tempP >= bestPscore && (Parameters.getMetricType() == 1 || Parameters.getMetricType() == 2))
								|| (tempP <= bestPscore && Parameters.getMetricType() == 3)) {
							bestPscore = tempP;
							bestShift = inner;
							bestOuterShift = outer;
							innerreverse = true;
							outerreverse = false;
						}
						tempP = Correlation->Correlation(rsearchTSS1, rsearchTSS2,	Parameters.getSlidingWindow());
						if ((tempP >= bestPscore && (Parameters.getMetricType() == 1 || Parameters.getMetricType() == 2))
								|| (tempP <= bestPscore && Parameters.getMetricType() == 3)) {
							bestPscore = tempP;
							bestShift = inner;
							bestOuterShift = outer;
							outerreverse = true;
							innerreverse = true;
						}
						delete[] rsearchTSS1;
						delete[] rsearchTSS2;
					}
					delete[] searchTSS;
				}
			}
			//load up averageTSS and output first two seeds at their shifted locations
			double* coreseed = new double[Parameters.getSlidingWindow()];
			loadarray(coreseed, bestOuterShift, primaryseed, outerreverse);
			double* secondseed = new double[Parameters.getSlidingWindow()];
			loadarray(secondseed, bestShift, secondaryseed, innerreverse);
			for (int a = 0; a < Parameters.getSlidingWindow(); a++) {
				averageTSS[a] = (coreseed[a] + secondseed[a]) / 2.0;
			}
			delete[] coreseed;
			delete[] secondseed;

			MasterRegion[primaryseed].setRev(outerreverse);
			MasterRegion[primaryseed].setShift(bestOuterShift);
			MasterRegion[secondaryseed].setRev(innerreverse);
			MasterRegion[secondaryseed].setShift(bestShift);

			//Pop used seeds out of matrix
			Swap(primaryseed, length);
			length--;
			for (int temp = 0; temp < (int)MasterRegion.size(); temp++) {
				if (MasterRegion[temp].getName().compare(seedtwo) == 0) {
					secondaryseed = temp;
				}
			}
			Swap(secondaryseed, length);
			length--;
			//Account for removing two levels at once
			x++;

			delete[] coreTSS;
		} else { //Loop through matrix finding index of next best pearson correlation
			int seedindex = 0, seedshift = 0;
			double bestPscore = -100;
			if (Parameters.getMetricType() == 3) {
				bestPscore = 99999999;
			}
			bool rev = false;
			for (int z = 0; z < length; z++) {
				for (int inner = 0; inner <= ((int)MasterRegion[z].getSeq().size() - Parameters.getSlidingWindow()); inner++) { //Load up TSS:search array with 100 nucleotide positions to compare against
					double* searchTSS = new double[Parameters.getSlidingWindow()];
					loadarray(searchTSS, inner, z, false);
					//Pearson correlation here
					double tempP = Correlation->Correlation(averageTSS, searchTSS, Parameters.getSlidingWindow());
					//If correlation is >= best P score, overwrite values with new scores
					if ((tempP >= bestPscore && Parameters.getMetricType() != 3) || (tempP <= bestPscore && Parameters.getMetricType() == 3)) {
						bestPscore = tempP;
						seedshift = inner;
						seedindex = z;
						rev = false;
					}
					double* rsearchTSS = new double[Parameters.getSlidingWindow()];
					if (Parameters.getReversalStatus()) {
						loadarray(rsearchTSS, inner, z, true);
						tempP = Correlation->Correlation(averageTSS, rsearchTSS, Parameters.getSlidingWindow());
						//If correlation is >= best P score, overwrite values with new scores
						if ((tempP >= bestPscore && Parameters.getMetricType() != 3) || (tempP <= bestPscore && Parameters.getMetricType() == 3)) {
							bestPscore = tempP;
							seedshift = inner;
							seedindex = z;
							rev = true;
						}
					}
					delete[] searchTSS;
					delete[] rsearchTSS;
				}
			}

			//update averageTSS and output new sequence at optimized sequence
			double* coreseed = new double[Parameters.getSlidingWindow()];
			loadarray(coreseed, seedshift, seedindex, rev);

			MasterRegion[seedindex].setRev(rev);
			MasterRegion[seedindex].setShift(seedshift);
			if (FINAL_Align) {
				OutputOrder.push_back(MasterRegion[seedindex].getName());
			}

			//Update Average TSS
			for (int a = 0; a < Parameters.getSlidingWindow(); a++) {
				averageTSS[a] = ((averageTSS[a] * (double) x) + coreseed[a])
						/ ((double) (x + 1));
			}

			delete[] coreseed;

			//Pop off used sequence
			Swap(seedindex, length);
			length--;
		}
	}

	delete[] averageTSS;

	CalculateProfile();
	if (!FINAL_Align) {
		MasterRegion.clear();
	}
	return CorrelationProfile;
}

void Align::CalculateProfile() {

	//JB WAZ HERE - Fixed the Instantiation from the old Metrix to the new
	MetrixFactory metrixFactory;
	AbstractMetrix* Correlation = metrixFactory.createMetrix(Parameters.getMetricType());
	//Metrix Correlation(Parameters.getMetricType());


	//Calculate out MASTER average Pearson profile
	CorrelationProfile = 0;
	double counter = 0;
	for (int x = 0; x < (int)MasterRegion.size(); x++) {
		double* coreRegion = new double[Parameters.getSlidingWindow()];
		loadarray(coreRegion, MasterRegion[x].getShift(), x,
				MasterRegion[x].getRev());
		for (int y = 0; y < (int)MasterRegion.size(); y++) {
			if (x != y && (x - y) >= 1) { //Load up Region:search array with 100 nucleotide positions to compare against
				double* searchRegion = new double[Parameters.getSlidingWindow()];
				loadarray(searchRegion, MasterRegion[y].getShift(), y, MasterRegion[y].getRev());
				//Pearson correlation here
				double tempP = Correlation->Correlation(coreRegion, searchRegion, Parameters.getSlidingWindow());
				CorrelationProfile += tempP;
				counter++;
				delete[] searchRegion;
			}
		}
		delete[] coreRegion;
	}
	CorrelationProfile /= counter;
}

void Align::loadRegions(string name) {
	ifstream master(const_cast<char*>(name.c_str()));
	while (!master.eof()) {
		string temp;
		getline(master, temp);
		char *token = NULL;
		if (!master.eof()) {
			Node tempnode;
			token = strtok(const_cast<char *> (temp.c_str()), "\t");
			tempnode.setName(token);
			token = strtok(NULL, "\t");
			while (token != NULL) {
				double sequence = atof(token);
				tempnode.addSeq(sequence);
				token = strtok(NULL, "\t");
			}
			tempnode.setWeight(1);
			MasterRegion.push_back(tempnode);
		}
	}
	master.close();
}

int Align::countlines(string name) {
	ifstream input(const_cast<char*>(name.c_str()));
	int lines = 0;
	while (!input.eof()) {
		string temp;
		getline(input, temp);
		lines++;
	}
	input.close();
	return (lines - 1);
}

void Align::loadarray(double currentregion[], int windowstart,
		int currentindex, bool reversal) {
	vector<double> tempseq = MasterRegion[currentindex].getSeq();
	if (!reversal) {
		for (int x = windowstart; x < (windowstart + Parameters.getSlidingWindow()); x++) {
			currentregion[x - windowstart] = tempseq[x];
		}
	} else {
		int index = 0;
		for (int x = (windowstart + Parameters.getSlidingWindow() - 1); x >= windowstart; x--) {
			currentregion[index] = tempseq[x];
			index++;
		}
	}
	tempseq.clear();
}

void Align::Swap(int index, int length) {
	int tempWeight = MasterRegion[length - 1].getWeight();
	vector<double> tempSeq(MasterRegion[length - 1].getSeq().size());
	for (int x = 0; x < (int)tempSeq.size(); x++) {
		tempSeq[x] = MasterRegion[length - 1].getSeqIndex(x);
	}
	string tempName(MasterRegion[length - 1].getName());
	int tempShift = MasterRegion[length - 1].getShift();
	bool tempRev = MasterRegion[length - 1].getRev();

	MasterRegion[length - 1].setWeight(MasterRegion[index].getWeight());
	for (int x = 0; x < (int)tempSeq.size(); x++) {
		MasterRegion[length - 1].setSeqIndex(x,
				MasterRegion[index].getSeqIndex(x));
	}
	MasterRegion[length - 1].setName(MasterRegion[index].getName());
	MasterRegion[length - 1].setShift(MasterRegion[index].getShift());
	MasterRegion[length - 1].setRev(MasterRegion[index].getRev());

	MasterRegion[index].setWeight(tempWeight);
	for (int x = 0; x < (int)tempSeq.size(); x++) {
		MasterRegion[index].setSeqIndex(x, tempSeq[x]);
	}
	MasterRegion[index].setName(tempName);
	MasterRegion[index].setShift(tempShift);
	MasterRegion[index].setRev(tempRev);

	tempSeq.clear();
}

