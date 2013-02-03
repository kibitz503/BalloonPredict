#ifndef CONTROLSTATE_H
#define CONTROLSTATE_H

#include "ObserverABC.h"
#include "Predictor.h"
#include "StateABC.h"
#include "PreLaunch.h"
#include "Ascent.h"
#include "Descent.h"
#include "Landed.h"

using namespace std;

class ControlState : public ObserverABC
{
public:
	ControlState( Predictor* );
	virtual ~ControlState( );
	/***************************************
	This function is called when the parser
	gets new data form the GPS... It calls
	the execute logic for each state.
	***************************************/
	virtual void update ( );
	/***************************************
	If the state decideds that it is finished
	this is function holds the logic to switch 
	states.
	***************************************/
	void setState( );

private:
	//pointer to the current state
	StateABC*	_state;
	//pointer to the predictor class
	Predictor*	_predictor;
};

#endif