#ifndef LANDED_H
#define LANDED_H

#include "StateABC.h"
/*****************************************************
This class contains the logic for our balloons landed
state.
*****************************************************/
class Landed : public StateABC
{
public:
	Landed( Predictor* );
	~Landed( );

	virtual void    predict( );
	/*****************************************************
	This returns if it is time to move to the next state.
	NOTE: this is the final state so it never transitions
	out of this state.
	*****************************************************/
	virtual bool	isNextState( );
	/*****************************************************
	This holds the logic for the check to see if it is
	time to move to the next state.  If it is it changes
	the next state bool to true.
	NOTE: this is the final state so it never transitions
	out of this state.
	*****************************************************/
	virtual void	stateChangeLogic( );
	/*****************************************************
	Returns the next state to the state controller
	*****************************************************/
	virtual StateABC*   getNextState( );
};

#endif