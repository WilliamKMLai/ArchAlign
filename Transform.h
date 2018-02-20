#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include <iostream>
#include <vector>
#include <math.h>

#include "Node.h"

class Transform {
	public:
		Transform();
		~Transform();
		double getbpProb();
		void setbpProb(double prob);
		double getGenomeSize();
		void setGenomeSize(double size);
		double getTotalTags();
		void setTotalTags(double tags);

		vector<Node> TransformControl(vector<Node> Original, int type);
		vector<Node> PoissonTransform(vector<Node> Original);
		vector<Node> NullTransform(vector<Node> Original);
		vector<Node> SquareTransform(vector<Node> Original);
		vector<Node> LogTransform(vector<Node> Original);
		double Factorial(double number);
	private:
		double bpProbability;
		double GenomeSize;
		double TotalTags;
};

#endif /* TRANSFORM_H_ */
