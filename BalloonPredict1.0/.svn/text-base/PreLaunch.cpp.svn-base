#include "PreLaunch.h"

PreLaunch::PreLaunch( Predictor* predictor ) : StateABC ( predictor )
{
	_newState = false;
	_run = false;
}

PreLaunch::~PreLaunch( )
{
}
bool PreLaunch::isNextState( )
{
	//return if its time to switch to the next state
	return _newState;
}
void PreLaunch::stateChangeLogic( )
{
	//get the current ascent rate
	_ascentRate = _predictor->getAscentRateReal();
	//check if the balloon is rising
	if( _ascentRate > 1 )
	{
		_ascentCount++;
	}
	else
	{
		_ascentCount = 0;
	}

	if( _ascentCount >= 2 )
	{
		//if its rising for 3 consecutive points we want to move to ascent
		_newState = true;
	}
}
void PreLaunch::predict( )
{
	//we only want to run the prelaunch prediction once
	if( _run == false )
	{
		_predictor->setup( );
		_predictor->ascent( );
		_predictor->descentPre( );
		_predictor->writeFile( );
		_run = true;
	}
	_predictor->setAscentRatePre( );
}
StateABC* PreLaunch::getNextState( )
{
	//return the next state when its time to switch
    Ascent* state;
	state = new Ascent ( _predictor );
	return state;

}