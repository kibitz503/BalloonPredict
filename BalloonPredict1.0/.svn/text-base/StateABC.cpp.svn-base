#include "StateABC.h"

StateABC::StateABC( Predictor* predictor ) : _newState(false), _ascentCount(0), _ascentRate(0.0), _predictor(predictor)
{	}

StateABC::~StateABC( )
{	}
void StateABC::execute( )
{
	//when the control state calls execute fire off the predict for the state
	predict( );
	//fire off the state change logic fo the state
	stateChangeLogic( );
}
