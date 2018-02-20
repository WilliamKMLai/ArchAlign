#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Config.h"
#include "Node.h"

#include "Output.h"

Output::Output(Config input) {
	Parameters = input;
}

Output::~Output() {

}

void Output::OutputAlignment(double Profile, vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder) {
	if(Parameters.getOutputType() == 1) {
		OutputStandard(Original, Aligned, OutputOrder);
	}
	else if(Parameters.getOutputType() == 2) {
		OutputTree(Original, Aligned, OutputOrder);
	}
	OutputSHIFT(Profile, Aligned, OutputOrder);
}

void Output::OutputStandard(vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder) {
	ofstream ALIGN(Parameters.getOutputFile().c_str());

	cout << "Outputing Final Alignment...\n";
	for (int x = 0; x < (int)Original.size(); x++) {
		for (int z = 0; z < (int)Original.size(); z++) {
			if (Original[z].getName().compare(OutputOrder[x]) == 0) {
				double* Region = new double[Parameters.getSlidingWindow()];
				for(int a = 0; a < (int)Aligned.size(); a++) {
					if (Aligned[a].getName().compare(Original[z].getName()) == 0) {
						loadarray(Original, Region, Aligned[a].getShift(), z, Aligned[a].getRev());
						ALIGN << Original[z].getName()<<"\t";
						for (int y = 0; y < Parameters.getSlidingWindow(); y++) {
								ALIGN << Region[y];
							if (y + 1 == Parameters.getSlidingWindow()) {
								ALIGN << "\n";
							} else {
								ALIGN << "\t";
							}
						}
						delete[] Region;
					}
				}
			}
		}
	}
	cout << "Complete\n";
	ALIGN.close();
}

void Output::OutputTree(vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder) {
	ofstream ALIGN(Parameters.getOutputFile().c_str());

	cout << "Outputing Final Alignment...\n";
	ALIGN<<"YORF\tNAME\tGWEIGHT\t";
	for(int x = 0; x < Parameters.getSlidingWindow(); x++) {
		ALIGN<<x;
		if(x + 1 == Parameters.getSlidingWindow()) { ALIGN<<endl; }
		else { ALIGN<<"\t"; }
	}
	for (int x = 0; x < (int)Original.size(); x++) {
		for (int z = 0; z < (int)Original.size(); z++) {
			if (Original[z].getName().compare(OutputOrder[x]) == 0) {
				double* Region = new double[Parameters.getSlidingWindow()];
				for(int a = 0; a < (int)Aligned.size(); a++) {
					if (Aligned[a].getName().compare(Original[z].getName()) == 0) {
						loadarray(Original, Region, Aligned[a].getShift(), z, Aligned[a].getRev());
						ALIGN << Original[z].getName()<<"\t"<<Original[z].getName()<<"\t"<<1<<"\t";
						for (int y = 0; y < Parameters.getSlidingWindow(); y++) {
								ALIGN << Region[y];
							if (y + 1 == Parameters.getSlidingWindow()) {
								ALIGN << "\n";
							} else {
								ALIGN << "\t";
							}
						}
						delete[] Region;
					}
				}
			}
		}
	}
	cout << "Complete\n";
	ALIGN.close();
}

void Output::OutputSHIFT(double Profile, vector<Node> Aligned, vector<string> OutputOrder) {
	ofstream SHIFT(Parameters.getOutputCoordFile().c_str());

	cout<<"Outputing Shifted Coordinates...\n";
	SHIFT << "Average Pearson Profile:\t" << Profile << "\n";
	for (int x = 0; x < (int)Aligned.size(); x++) {
		for (int y = 0; y < (int)Aligned.size(); y++) {
			if (Aligned[y].getName().compare(OutputOrder[x]) == 0) {
				SHIFT << Aligned[y].getName() <<"\t"<< Aligned[y].getShift() << "\t";
				if (Aligned[y].getRev()) {
					SHIFT << "Rev\n";
				} else {
					SHIFT << "NA\n";
				}
			}
		}
	}
	cout<<"Complete\n";
	SHIFT.close();
}

void Output::loadarray(vector<Node> & Original, double currentregion[], int windowstart, int currentindex, bool reversal) {
	vector<double> tempseq = Original[currentindex].getSeq();
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
