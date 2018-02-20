/*
 * Chosen.cpp
 *
 *  Created on: Jul 16, 2010
 *      Author: jbard
 */

#include "Chosen.h"
#include "../../Align.h"
#include "../../Output.h"
Chosen::Chosen() {
	// TODO Auto-generated constructor stub

}

Chosen::~Chosen() {
	// TODO Auto-generated destructor stub
}

void Chosen::Execute(){
	Align* Chosen = new Align(Parameters);
	Chosen->setFinal(true);
	Chosen->ChosenAlign(Parameters.getSeedOne(), Parameters.getSeedTwo());
	vector<Node> Align = Chosen->getRegion();
	vector<string> Order = Chosen->getOrder();
	double P = Chosen->getProfile();
	Output file(Parameters);

	//TODO: Code this after talking to buck
	//	OutputFactory factory ;
	//	OutputType file = factory.createOutputFile(Parameters.getOutputType());
	//  Changed original to MasterRegion
	//  file->OutputAlignment(P,MasterRegion,Align,Order);
	file.OutputAlignment(P, MasterRegion, Align, Order);
}
void Chosen::AlignFinal(){
}
