#ifndef DESCENT_H
#define DESCENT_H

#include "StateABC.h"
#include "Landed.h"
/*****************************************************
This class contains the logic for our balloons descent
IT calls the apropriate prediction logic and checks
conditions after each point to see if the balloon is
still in this state.
*****************************************************/
class Descent : public StateABC
{
public:
	Descent( Predictor* );
	~Descent( );
	/*****************************************************
	This calls the prediction algorithms for ascent which
	is just the descent prediction.
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

private:
	bool _ran;
};

#endif
