#include "ControlState.h"

ControlState::ControlState( Predictor* predictor )
{
	_predictor = predictor;
	_state = new PreLaunch (_predictor );
}

ControlState::~ControlState( )
{
	//delete the current state when program closes
	delete _state;
}

void ControlState::update( )
{
	//When the observer notifies us that a new point has been sent fire execute
	_state->execute( );
	//if its time to change states 
	if( _state->isNextState( ) )
	{
		setState( );
	}
}
void ControlState::setState()
{
	//get the next state
	StateABC* newState;
	newState = _state->getNextState( );
	//delete the current state
	delete _state;
	//advance to the next state
	_state = newState;
	newState = NULL;
}