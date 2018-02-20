#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "Config.h"
#include "Node.h"
#include "Metrix/MetrixFactory.h"
#include "Metrix/AbstractMetrix.h"
#include "Transform.h"
#include "Align.h"
#include "Output.h"
#include "Alignments/AlignFactory.h"

using namespace std;

void loadRegions(vector<Node> & Matrix, string name);
int countlines(string name);

int main(int argc, char* argv[]) {
	if(argc != 2) {
		cout<<"Usage:\n./ArchAlign1_5 config.file\n\n";
		exit(0);
	}
	time_t rawtime;
	struct tm * timeinfo;
	time (& rawtime);
	timeinfo = localtime(& rawtime);
	cout<<"Current local time and date: "<<asctime(timeinfo);

	cout<<"\nLoading Config File...\n";
	Config Parameters(argv[1]);
	cout<<"Config File Loaded\n\n";

	int FileLength = countlines(Parameters.getInputFile());
	if(FileLength < 2) {
		cout<<"Invalid File to be Aligned!!!\n";
		exit(0);
	}
	cout<<"Lines in Input File: "<<FileLength<<endl;
	vector<Node> MasterRegion(FileLength);

	cout<<"Loading Regions from Input File...\n";
	loadRegions(MasterRegion, Parameters.getInputFile());
	cout<<"Regions Loaded\n\n";

	cout<<"Transforming Data...\n";
	Transform Data;
	Data.setGenomeSize(Parameters.getGenomeSize());
	Data.setTotalTags(Parameters.getTotalTags());
	vector<Node> newRegion = Data.TransformControl(MasterRegion, Parameters.getTransformationType());
	cout<<"Data Transformed\n\nAlignment Proceeding...\n";

	/**
	* Handles any kind of alignment with any metrix
	* TODO: Eventually we will convert this to just an AbstractAlign class, but for simplicity we will only
	* be implementing the Progressive alignments for now. Want to make sure everything works before we move forward
	*/
	AlignFactory factory;
	AbstractProgressiveAligner* align = factory.createAligner(1,Parameters.getAlignmentType());
	align->setMaster(MasterRegion);
	align->setTransformed(newRegion);
	align->setConfig(Parameters);
	align->Execute();

	time ( &rawtime);
	timeinfo = localtime ( & rawtime);
	printf("Current local time and date: %s", asctime (timeinfo));
	return 0;
}

void loadRegions(vector<Node> & Matrix, string name) {
	ifstream master(const_cast<char*>(name.c_str()));
	int count = 0;
	while (!master.eof()) {
		string temp;
		getline(master, temp);
		char *token = NULL;
		if (!master.eof()) {
			token = strtok(const_cast<char *> (temp.c_str()), "\t");
			Matrix[count].setName(token);
			token = strtok(NULL, "\t");
			while (token != NULL) {
				double sequence = atof(token);
				Matrix[count].addSeq(sequence);
				token = strtok(NULL, "\t");
			}
			Matrix[count].setWeight(1);
		}
		count++;
	}
	master.close();
}

int countlines(string name) {
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
