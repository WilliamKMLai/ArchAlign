#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node {
	public:
		Node();
		~Node();
		vector<double> getSeq();
		string getName();
		int getWeight();
		int getShift();
		bool getRev();
		void addSeq(double newSeq);
		void setName(string newName);
		void setWeight(int newWeight);
		void setShift(int newShift);
		void setRev(bool newRev);
		double getSeqIndex(int index);
		void setSeqIndex(int index, double value);
	private:
		vector<double> Seq;
		string Name;
		int Weight;
		int Shift;
		bool Rev;
};

#endif /*NODE_H_*/
