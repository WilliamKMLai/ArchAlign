#include <iostream>
#include <string>
#include <fstream>

#include "Config.h"

using namespace std;

Config::Config() {
	AlignmentType = -1;
	InputFile = "";
	SlidingWindow = -1;
	ReversalStatus = false;
	MetricType = -1;
	TransformationType = -1;
	OutputFile = "";
	OutputCoordFile = "";
	OutputType = -1;

	//Optional Variables
	SeedOne = "";
	SeedTwo = "";
	GenomeSize = -1;
	TotalTags = -1;
}

Config::Config(char *input) {
	AlignmentType = -1;
	InputFile = "";
	SlidingWindow = -1;
	ReversalStatus = false;
	MetricType = -1;
	TransformationType = -1;
	OutputFile = "";
	OutputCoordFile = "";
	OutputType = -1;

	//Optional Variables
	SeedOne = "";
	SeedTwo = "";
	GenomeSize = -1;
	TotalTags = -1;
	LoadConfig(input);
}

Config::~Config() {

}

void Config::LoadConfig(char *input) {
	ifstream file(input);
	while (!file.eof()) {
			string temp;
			getline(file, temp);
			if(!temp.compare("Alignment:")) {
				getline(file, temp);
				if(!temp.compare("seed")) {
						cout<<"Alignment Type: Seed Selection\n";
						AlignmentType = 1;
					}
					else if(!temp.compare("bestpair")) {
						cout<<"Alignment Type: BestPair Selection\n";
						AlignmentType = 2;
					}
					else if(!temp.compare("chosen")) {
						cout<<"Alignment Type: Chosen Selection\n";
						AlignmentType = 3;
					}
					else {
						cout<<"Invalid Alignment Type!!!\n";
						exit(0);
					}
			}
			if(!temp.compare("Input File:")) {
				getline(file, InputFile);
				cout<<"File to be Aligned: "<<InputFile<<endl;
			}
			if(!temp.compare("Sliding Window:")) {
				getline(file, temp);
				SlidingWindow = atoi(temp.c_str());
				if(SlidingWindow < 1) {
					cout<<"Invalid Sliding Window!!!\n";
					exit(0);
				}
				cout<<"Window Size: "<<SlidingWindow<<endl;
			}
			if(!temp.compare("Reversal Status:")) {
				getline(file, temp);
				if(!temp.compare("true")) {
					cout<<"Reversal Status: true\n";
					ReversalStatus = true;
				}
				else if(!temp.compare("false")) {
					cout<<"Reversal Status: false\n";
					ReversalStatus = false;
				}
				else {
					cout<<"Invalid Reversal Status!!!\n";
					exit(0);
				}

			}
			if(!temp.compare("Alignment Metric:")) {
				getline(file, temp);
				if(!temp.compare("pearson")) {
					cout<<"Metric Selected: pearson\n";
					MetricType = 1;
				}
				else if(!temp.compare("spearman")) {
					cout<<"Metric Selected: spearman\n";
					MetricType = 2;
				}
				else if(!temp.compare("euclidean")) {
					cout<<"Metric Selected: euclidean\n";
					MetricType = 3;
				}
				else {
					cout<<"Invalid Metric Selected!!!\n";
					exit(0);
				}
			}
			if(!temp.compare("Transformation:")) {
				getline(file, temp);
				if(!temp.compare("none")) {
					cout<<"Transformation Status: none\n";
					TransformationType = 0;
				}
				else if(!temp.compare("poisson")) {
					cout<<"Transformation Status: poisson\n";
					TransformationType = 1;
				}
				else if(!temp.compare("log")) {
					cout<<"Transformation Status: log\n";
					TransformationType = 2;
				}
				else if(!temp.compare("squareroot")) {
					cout<<"Transformation Status: squareroot\n";
					TransformationType = 3;
				}
				else {
					cout<<"Invalid Transformation!!!\n";
					exit(0);
				}
			}
			if(!temp.compare("Alignment File Output:")) {
				getline(file, OutputFile);
				cout<<"Primary Output File: "<<OutputFile<<endl;
			}
			if(!temp.compare("Alignment Coordinates File Output:")) {
				getline(file, OutputCoordFile);
				cout<<"Alignment Coordinate Output File: "<<OutputCoordFile<<endl;
			}
			if(!temp.compare("Genome Size:")) {
				getline(file, temp);
				GenomeSize = atof(temp.c_str());
				cout<<"Genome Size: "<<GenomeSize<<endl;
			}
			if(!temp.compare("Total Tag Count:")) {
				getline(file, temp);
				TotalTags = atof(temp.c_str());
				cout<<"Total Tags: "<<TotalTags<<endl;
			}
			if(!temp.compare("Seed One:")) {
				getline(file, SeedOne);
				cout<<"Primary Seed: "<<SeedOne<<endl;
			}
			if(!temp.compare("Seed Two:")) {
				getline(file, SeedTwo);
				cout<<"Secondary Seed: "<<SeedTwo<<endl;
			}
			if(!temp.compare("Output Type:")) {
				getline(file, temp);
				if(!temp.compare("standard")) {
					cout<<"Output Type: standard\n";
					OutputType = 1;
				}
				else if(!temp.compare("treeview")) {
					cout<<"Output Type: treeview\n";
					OutputType = 2;
				}
				else {
					cout<<"Invalid Output Type!!!\n";
					exit(0);
				}
			}
			if(!file.eof()) {
				getline(file, temp);
			}
	}
	file.close();
	LoadingCheck();
}

void Config::LoadingCheck() {
	if(AlignmentType == -1) {
		cout<<"No Alignment Type Selected!!!\n";
		exit(0);
	}
	if(!InputFile.compare("")) {
		cout<<"No Input File Selected!!!\n";
		exit(0);
	}
	if(SlidingWindow == -1) {
		cout<<"No Window Size Selected!!!\n";
		exit(0);
	}
	if(MetricType == -1) {
			cout<<"No Metric Type Selected!!!\n";
			exit(0);
	}
	if(TransformationType == -1) {
			cout<<"No Transformation Type Selected!!!\n";
			exit(0);
	}
	if(!OutputFile.compare("")) {
		cout<<"No Output File Selected!!!\n";
		exit(0);
	}
	if(!OutputCoordFile.compare("")) {
		cout<<"No Output Coordinate File Selected!!!\n";
		exit(0);
	}
	if(OutputType == -1) {
		cout<<"No Output Type Selected!!!\n";
		exit(0);
	}
	if(TransformationType != 0 && TransformationType != 3 && (GenomeSize < 1 || TotalTags < 1)) {
		cout<<"Genome Size and TotalTag Count are Invalid for Transformation Selected\n";
		exit(0);
	}
	if(AlignmentType == 3 && (!SeedOne.compare("") || !SeedTwo.compare(""))) {
		cout<<"Invalid Seeds Selected for Chosen Seed Alignment!!!\n";
		exit(0);
	}
}

int Config::getAlignmentType() {
	return AlignmentType;
}

string Config::getInputFile() {
	return InputFile;
}

int Config::getSlidingWindow() {
	return SlidingWindow;
}

bool Config::getReversalStatus() {
	return ReversalStatus;
}

int Config::getMetricType() {
	return MetricType;
}

int Config::getTransformationType() {
	return TransformationType;
}

string Config::getOutputFile() {
	return OutputFile;
}

string Config::getOutputCoordFile() {
	return OutputCoordFile;
}

int Config::getOutputType() {
	return OutputType;
}


void Config::setAlignmentType(int type) {
	AlignmentType = type;
}

void Config::setInputFile(string file) {
	InputFile = file;
}

void Config::setSlidingWindow(int window) {
	SlidingWindow = window;
}

void Config::setReversalStatus(bool status) {
	ReversalStatus = status;
}

void Config::setMetricType(int metric) {
	MetricType = metric;
}

void Config::setTransformationType(int transformation) {
	TransformationType = transformation;
}

void Config::setOutputFile(string outfile) {
	OutputFile = outfile;
}

void Config::setOutputCoordFile(string outcoordfile) {
	OutputCoordFile = outcoordfile;
}

void Config::setOutputType(int out) {
	OutputType = out;
}

//Optional Variables
string Config::getSeedOne() {
	return SeedOne;
}

string Config::getSeedTwo() {
	return SeedTwo;
}

double Config::getGenomeSize() {
	return GenomeSize;
}

double Config::getTotalTags() {
	return TotalTags;
}

void Config::setSeedOne(string one) {
	SeedOne = one;
}

void Config::setSeedTwo(string two) {
	SeedTwo = two;
}

void Config::setGenomeSize(double size) {
	GenomeSize = size;
}

void Config::setTotalTags(double tags) {
	TotalTags = tags;
}
