#ifndef ASCENT_H
#define ASCENT_H

#include "StateABC.h"
#include "Descent.h"
/*****************************************************
This class contains the logic for our balloons ascent
IT calls the apropriate prediction logic and checks
conditions after each point to see if the balloon is
still in this state.
*****************************************************/
class Ascent : public StateABC
{
public:
	Ascent( Predictor* );
	~Ascent( );
	/*****************************************************
	This calls the prediction algorithms for ascent which
	are ascent and descent.
	*****************************************************/
	virtual void    predict( );
	/*****************************************************
	This returns if it is time to move to the next state.
	*****************************************************/
	virtual bool	isNextState( );
	/*****************************************************
	This holds the logic for the check to see if it is
	time to move to the next state.  If it is it changes
	the next state bool to true.
	*****************************************************/
	virtual void	stateChangeLogic( );
	/*****************************************************
	Returns the next state to the state controller
	*****************************************************/
	virtual StateABC*   getNextState( );
};

#endif