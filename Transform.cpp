#include <iostream>
#include <vector>
#include <math.h>

#include "Transform.h"
#include "Node.h"

Transform::Transform() {
	bpProbability = 0;
	GenomeSize = 0;
	TotalTags = 0;
}

Transform::~Transform() {

}

double Transform::getbpProb() {
	return bpProbability;
}

void Transform::setbpProb(double prob) {
	bpProbability = prob;
}

double Transform::getGenomeSize() {
	return GenomeSize;
}

void Transform::setGenomeSize(double size) {
	GenomeSize = size;
	bpProbability = TotalTags / GenomeSize;
}

double Transform::getTotalTags() {
	return TotalTags;
}

void Transform::setTotalTags(double tags) {
	TotalTags = tags;
	bpProbability = TotalTags / GenomeSize;
}

vector<Node> Transform::TransformControl(vector<Node> Original, int type) {
	if(type == 1) {
		return PoissonTransform(Original);
	}
	else if(type == 2) {
		return LogTransform(Original);
	}
	else if(type == 3) {
		return SquareTransform(Original);
	}
	else {
		return NullTransform(Original);
	}
}

vector<Node> Transform::PoissonTransform(vector<Node> Original) {
	//f(n, l) = (l^n)(e^-l)/(n!) for every number 0 to n
	vector<Node> New(Original.size());
	for(int i = 0; i < (int)Original.size(); i++) {
		New[i].setName(Original[i].getName());
		New[i].setWeight(Original[i].getWeight());
		New[i].setShift(Original[i].getShift());
		New[i].setRev(Original[i].getRev());
		for(int xi = 0; xi < (int)Original[i].getSeq().size(); xi++) {
				double temp = 0;
				for(int x = 0; x < Original[i].getSeqIndex(xi); x++) {
					temp += (pow(bpProbability, x) * pow(exp(1), (-1 * bpProbability)))/ Factorial((double) x);
				}
				if(isnan(temp)) { temp = 1; }
				New[i].addSeq(temp);
		}
	}
	return New;
}

vector<Node> Transform::NullTransform(vector<Node> Original) {
	vector<Node> New(Original.size());
	for(int i = 0; i < (int)Original.size(); i++) {
		New[i].setName(Original[i].getName());
		New[i].setWeight(Original[i].getWeight());
		New[i].setShift(Original[i].getShift());
		New[i].setRev(Original[i].getRev());
		for(int y = 0; y < (int)Original[i].getSeq().size(); y++) {
			New[i].addSeq(Original[i].getSeqIndex(y));
		}
	}
	return New;
}

vector<Node> Transform::SquareTransform(vector<Node> Original) {
	vector<Node> New(Original.size());
	for(int i = 0; i < (int)Original.size(); i++) {
		New[i].setName(Original[i].getName());
		New[i].setWeight(Original[i].getWeight());
		New[i].setShift(Original[i].getShift());
		New[i].setRev(Original[i].getRev());
		for(int y = 0; y < (int)Original[i].getSeq().size(); y++) {
			if(Original[i].getSeqIndex(y) < 0) {
				cout<<"Cannot Take Square Root of Negative Number!!!\n";
				exit(0);
			}
			double temp = sqrt(Original[i].getSeqIndex(y));
			New[i].addSeq(temp);
		}
	}
	return New;
}

vector<Node> Transform::LogTransform(vector<Node> Original) {
	vector<Node> New(Original.size());
	for(int i = 0; i < (int)Original.size(); i++) {
		New[i].setName(Original[i].getName());
        New[i].setWeight(Original[i].getWeight());
        New[i].setShift(Original[i].getShift());
        New[i].setRev(Original[i].getRev());
        for(int y = 0; y < (int)Original[i].getSeq().size(); y++) {
        	double temp = 0;
            if(Original[i].getSeqIndex(y) == 0) {
            	temp = log(1 / (((double)TotalTags + 1) / (double)GenomeSize)) / log(2);
            }
            else {
            	temp = log(Original[i].getSeqIndex(y) / bpProbability) / log(2);
            }
            New[i].addSeq(temp);
        }
	}
    return New;
}

double Transform::Factorial(double number) {
	double newnum = 0;
	if (number <= 1) {
		return 1;
	}
	newnum = number * Factorial(number - 1);
	return newnum;
}
