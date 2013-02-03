#ifndef PRELAUNCH_H
#define PRELAUNCH_H

#include "StateABC.h"
#include "Ascent.h"
/*****************************************************
This class contains the logic for our balloons prelaunch.
It calls the apropriate prediction logic and checks
conditions after each point to see if the balloon is
still in this state.
*****************************************************/
class PreLaunch : public StateABC
{
public:
	PreLaunch( Predictor* );
	~PreLaunch( );

	/*****************************************************
	This calls the prediction algorithms for prelaunch which
	reads in the NOAA weather data for the date and runs
	ascent and descent one time with that data.
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
	/*****************************************************
	This bool is toggled when the prelaunch prediction
	is run.  We do this to ensure that the prelaunch 
	prediction is only run once.
	*****************************************************/
	bool	_run;
};

#endif
