#ifndef ALIGN_H_
#define ALIGN_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Config.h"
#include "Metrix/AbstractMetrix.h"
#include "Node.h"
#include "Transform.h"

class Align {
	public:
	   // constructor
		Align(Config input);
		~Align();
		void setFinal(bool time);
		bool getFinal();
		vector<Node> getRegion();
		vector<string> getOrder();
		double getProfile();
		double ChosenAlign(string seedone, string seedtwo);
	private:
		Config Parameters;
		vector<Node> MasterRegion;
		vector<string> OutputOrder;
		double CorrelationProfile;
		bool FINAL_Align;
		void CalculateProfile();
		void loadRegions(string name);
		int countlines(string name);
		void loadarray(double currentregion[], int windowstart, int currentindex, bool reversal);
		void Swap(int index, int length);
};

#endif /*ALIGN_H_*/
