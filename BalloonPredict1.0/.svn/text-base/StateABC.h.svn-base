#ifndef STATEABC_H
#define STATEABC_H

#include "Predictor.h"

class StateABC
{
public:
	StateABC( Predictor* );
	~StateABC( );
	/*******************************************************
	Have the current state do something with the data.
	*******************************************************/
	void	 execute( );
	/******************************************************
	Call the Predictor algorithm for the current state
	******************************************************/
	virtual void     predict( ) = 0;
	/******************************************************
	Return wheather the state needs to be advanced
	******************************************************/
	virtual bool	 isNextState( ) = 0;
	/******************************************************
	The logic to determine if tthe current state is finished
	******************************************************/
	virtual void	 stateChangeLogic( ) = 0;
	/*****************************************************
	Have the state return the next state to the controller
	*****************************************************/
	virtual StateABC*    getNextState( ) = 0;

protected:
	/*****************************************************
	A variable that the individual states use to flag if 
	the state needs to be changed.
	*****************************************************/
	bool		_newState;
	/*****************************************************
	A variable used to keep track of the number of times
	a state change logic is true
	*****************************************************/
	int			_ascentCount;
	/*****************************************************
	A variable to hold the current ascent rate which is 
	used in state change logic
	*****************************************************/
	double		_ascentRate;
	/*****************************************************
	A pointer to the class holding the prediction logic
	*****************************************************/
	Predictor*	_predictor;
	
};

#endif