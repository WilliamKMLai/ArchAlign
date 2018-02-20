#ifndef CONFIG_H_
#define CONFIG_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Config {
	public:
		Config();
		Config(char *input);
		~Config();
		void LoadConfig(char *input);
		void LoadingCheck();

		int getAlignmentType();
		string getInputFile();
		int getSlidingWindow();
		bool getReversalStatus();
		int getMetricType();
		int getTransformationType();
		string getOutputFile();
		string getOutputCoordFile();
		int getOutputType();

		void setAlignmentType(int type);
		void setInputFile(string file);
		void setSlidingWindow(int window);
		void setReversalStatus(bool status);
		void setMetricType(int metric);
		void setTransformationType(int transformation);
		void setOutputFile(string outfile);
		void setOutputCoordFile(string outcoordfile);
		void setOutputType(int out);

		//Optional Variables
		string getSeedOne();
		string getSeedTwo();
		double getGenomeSize();
		double getTotalTags();

		void setSeedOne(string one);
		void setSeedTwo(string two);
		void setGenomeSize(double size);
		void setTotalTags(double tags);

	private:
		int AlignmentType;
		string InputFile;
		int SlidingWindow;
		bool ReversalStatus;
		int MetricType;
		int TransformationType;
		string OutputFile;
		string OutputCoordFile;
		int OutputType;

		//Optional Variables
		string SeedOne;
		string SeedTwo;
		double GenomeSize;
		double TotalTags;
};

#endif /* CONFIG_H_ */
