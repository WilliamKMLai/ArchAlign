#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Config.h"
#include "Node.h"

using namespace std;

class Output {
	public:
		Output(Config input);
		~Output();
		void OutputAlignment(double Profile, vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder);
		void OutputStandard(vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder);
		void OutputTree(vector<Node> Original, vector<Node> Aligned, vector<string> OutputOrder);
		void OutputSHIFT(double Profile, vector<Node> Aligned, vector<string> OutputOrder);
	private:
		Config Parameters;
		void loadarray(vector<Node> & Original, double currentregion[], int windowstart, int currentindex, bool reversal);
};

#endif /* OUTPUT_H_ */
