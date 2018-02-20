#include "Seed.h"
#include "../../Align.h"
#include "../../Output.h"
#include "../../Metrix/MetrixFactory.h"
#include "../../Metrix/AbstractMetrix.h"
Seed::Seed() {
	// TODO Auto-generated constructor stub

}

Seed::~Seed() {
	// TODO Auto-generated destructor stub
}

void Seed::Execute(){
	//JB WAZ HERE - Fixed the Instantiation from the old Metrix to the new
		MetrixFactory metrixFactory;
		AbstractMetrix* Correlation = metrixFactory.createMetrix(Parameters.getMetricType());
	//	Metrix Correlation(Parameters.getMetricType());
		string bestPrimarySeed = "";
		string bestSecondarySeed = "";
		double bestCorrelation = -100;
		if (Parameters.getMetricType() == 3) {
			bestCorrelation = 999999999;
		}
		for (int index = 0; index < (int)TransformedRegion.size(); index++) {
			double bestP = -100;
			if (Parameters.getMetricType() == 3) {
				bestP = 999999999;
			}
			string partnerName = "";
			vector<double> indexSeq = TransformedRegion[index].getSeq();
			cout << "Index: " << index << endl;
			for (int partner = 0; partner < (int)TransformedRegion.size(); partner++) {
				if (index != partner) {
					vector<double> partnerSeq = TransformedRegion[partner].getSeq();
					double* coreRegion = new double[Parameters.getSlidingWindow()];
					double* partnerRegion = new double[Parameters.getSlidingWindow()];
					for (int outer = 0; outer <= ((int)indexSeq.size()- Parameters.getSlidingWindow()); outer++) {
						loadarray(TransformedRegion, coreRegion, Parameters.getSlidingWindow(),outer, index, false);
						for (int inner = 0; inner <= ((int)partnerSeq.size()- Parameters.getSlidingWindow()); inner++) {
							loadarray(TransformedRegion, partnerRegion, Parameters.getSlidingWindow(), inner, partner, false);
							double tempP = Correlation->Correlation(coreRegion, partnerRegion, Parameters.getSlidingWindow());
							if ((tempP > bestP && Parameters.getMetricType() != 3) || (tempP < bestP && Parameters.getMetricType() == 3)) {
								partnerName = TransformedRegion[partner].getName();
								bestP = tempP;
							}
							if(Parameters.getReversalStatus()) {
								double* rsearchTSS1 = new double[Parameters.getSlidingWindow()];
								loadarray(TransformedRegion, rsearchTSS1, Parameters.getSlidingWindow(), outer, index, true);
								tempP = Correlation->Correlation(rsearchTSS1, partnerRegion, Parameters.getSlidingWindow());
								//If correlation is >= best P score, overwrite values with new scores
								if ((tempP >= bestP && Parameters.getMetricType() != 3) || (tempP <= bestP && Parameters.getMetricType() == 3)) {
									partnerName = TransformedRegion[partner].getName();
									bestP = tempP;
								}
								double* rsearchTSS2 = new double[Parameters.getSlidingWindow()];
								loadarray(TransformedRegion, rsearchTSS2, Parameters.getSlidingWindow(), inner, partner, true);
								tempP = Correlation->Correlation(rsearchTSS2, coreRegion, Parameters.getSlidingWindow());
								//If correlation is >= best P score, overwrite values with new scores
								if ((tempP >= bestP && Parameters.getMetricType() != 3) || (tempP <= bestP && Parameters.getMetricType() == 3)) {
									partnerName = TransformedRegion[partner].getName();
									bestP = tempP;
								}
								tempP = Correlation->Correlation(rsearchTSS1, rsearchTSS2,	Parameters.getSlidingWindow());
								if ((tempP >= bestP && Parameters.getMetricType() != 3) || (tempP <= bestP && Parameters.getMetricType() == 3)) {
									partnerName = TransformedRegion[partner].getName();
									bestP = tempP;
								}
								delete[] rsearchTSS1;
								delete[] rsearchTSS2;
							}
						}
					}
					delete[] coreRegion;
					delete[] partnerRegion;
				}
			}
			cout << TransformedRegion[index].getName() << "\t" << partnerName << "\t" << bestP << endl;
			Align BestPair(Parameters);
			double Profile = BestPair.ChosenAlign(TransformedRegion[index].getName(), partnerName);
			cout << "Alignment Profile: " << Profile <<endl;
			if (Profile > bestCorrelation && Parameters.getMetricType() != 3) {
				bestCorrelation = Profile;
				bestPrimarySeed = TransformedRegion[index].getName();
				bestSecondarySeed = partnerName;
			} else if (Profile < bestCorrelation && Parameters.getMetricType() == 3) {
				bestCorrelation = Profile;
				bestPrimarySeed = TransformedRegion[index].getName();
				bestSecondarySeed = partnerName;
			}
		}
		cout << "Seed Sampling Complete\nOptimal Seeds:\t" << bestPrimarySeed << "\t" << bestSecondarySeed << "\nAligning by Optimal Seed Pairs...\n";
		Align Final_BestPair(Parameters);
		Final_BestPair.setFinal(true);
		Final_BestPair.ChosenAlign(bestPrimarySeed, bestSecondarySeed);
		vector<Node> Align = Final_BestPair.getRegion();
		vector<string> Order = Final_BestPair.getOrder();
		double P = Final_BestPair.getProfile();
		Output file(Parameters);
		file.OutputAlignment(P, MasterRegion, Align, Order);
}
void Seed::AlignFinal(){
}
