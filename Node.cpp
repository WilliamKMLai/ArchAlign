#include <iostream>
#include <string>
#include <vector>

#include "Node.h"

using namespace std;

Node::Node() {
	Seq.resize(0);
	Name = "";
	Weight = 0;
	Shift = 0;
	Rev = false;
}

Node::~Node() { Seq.clear(); }

vector<double> Node::getSeq() {
	return Seq;
}

string Node::getName() {
	return Name;
}

int Node::getWeight() {
	return Weight;
}

int Node::getShift() {
	return Shift;
}

bool Node::getRev() {
	return Rev;
}

void Node::addSeq(double newSeq) {
	Seq.push_back(newSeq);
}

void Node::setName(string newName) {
	Name = newName;
}

void Node::setWeight(int newWeight) {
	Weight = newWeight;
}

void Node::setShift(int newShift) {
	Shift = newShift;
}

void Node::setRev(bool newRev) {
	Rev = newRev;
}

double Node::getSeqIndex(int index) {
	return Seq[index];
}

void Node::setSeqIndex(int index, double value) {
	Seq[index] = value;
}
