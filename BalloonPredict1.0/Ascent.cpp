#include "Ascent.h"

Ascent::Ascent( Predictor* predictor ) : StateABC ( predictor )
{
}

Ascent::~Ascent( )
{
}
bool Ascent::isNextState( )
{
	//this holds if its time to move to the next state
	return _newState;
}
void Ascent::stateChangeLogic( )
{
	//get the ascent rate
	_ascentRate = _predictor->getAscentRateReal();
	//check to see if the balloon is going down
	if( _ascentRate < 0 )
	{
		_ascentCount++;
	}
	else
	{
		_ascentCount = 0;
	}
	//if the balloon is going down for 3 consecutive points
	if( _ascentCount >= 2 )
	{
		//its time to switch states
		_newState = true;
	}
}
void Ascent::predict( )
{
	//call the appropriate predicitons
	_predictor->ascent( );
	_predictor->descentPre( );
}
StateABC* Ascent::getNextState( )
{
	//return the next state to switch to
    Descent* state;
	state = new Descent ( _predictor );
	return state;

}