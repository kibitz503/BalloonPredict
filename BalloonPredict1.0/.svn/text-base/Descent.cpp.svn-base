#include "Descent.h"

Descent::Descent( Predictor* predictor ) : StateABC ( predictor )
{
	_predictor->clear();
	_ran = false;
}
Descent::~Descent( )
{
}
bool Descent::isNextState( )
{
	//return whether its time to switch states
	return _newState;
}
void Descent::stateChangeLogic( )
{
	//get the current ascent rate
	_ascentRate = _predictor->getAscentRateReal();
	//if the balloon is at virual "zero"
	//NOTE: the GPS can be up to 20 meters off so we can't use 0
	if( _ascentRate > -.02 && _ascentRate < .02 )
	{
		_ascentCount++;
	}
	else
	{
		_ascentCount = 0;
	}
	//if the balloon dosen't move for 3 consecutive points
	if( _ascentCount >= 2 )
	{
		//its time to switch state
		_newState = true;
	}
}
void Descent::predict( )
{
	//call the appropriate predictions for this state
	_predictor->descent( );
	_predictor->setAscentRate();
	if ( _ran == false )
	{
		_predictor->writeFileDesc();
		_ran = true;
	}
}
StateABC* Descent::getNextState( )
{
	//return the next state
    Landed* state;
	state = new Landed ( _predictor );
	return state;

}