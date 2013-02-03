#include "PredictedNode.h"

/**********************************************************************
*
*	PredictedNode:
*	The default constructor that sets all the values in PredictedNode to 0
*
**********************************************************************/
PredictedNode::PredictedNode ( ): 
_latPredict(0.0f), _lonPredict(0.0f), _altPredict(0.0f), _timePredict(0)
{	}

/**********************************************************************
*
*	PredictedNode:
*	A constructor of PredictedNode that stores the valuse passed in into 
*	the correct attributes
*
**********************************************************************/
PredictedNode::PredictedNode ( double lat, double lon, double alt, int time ):
_latPredict(lat), _lonPredict(lon), _altPredict(alt), _timePredict(time)
{	}

/**********************************************************************
*
*	PredictedNode:
*	The copy constructor copies all the values of the old PredictedNode
*	into the new one
*
**********************************************************************/
PredictedNode::PredictedNode ( const PredictedNode & copy )
{	
	*this = copy;
}

/**********************************************************************
*
*	~PredictedNode:
*	The destructor of the PredictedNode
*
**********************************************************************/
PredictedNode::~PredictedNode ( )
{	}

/**********************************************************************
*
*	operator=:
*	The operator= copies all the values of the old PredictedNode
*	into the new one
*
**********************************************************************/
PredictedNode& PredictedNode::operator= ( const PredictedNode& rhs )
{	
	if ( this != &rhs )
	{
		_latPredict = rhs._latPredict;
		_lonPredict = rhs._lonPredict;
		_altPredict = rhs._altPredict;
		_timePredict = rhs._timePredict;
	}
	return *this;
}

/**********************************************************************
*
*	operator!=:
*	The operator!= returns false if the PredictedNodes altitude are the same
*
**********************************************************************/
bool PredictedNode::operator!= ( const PredictedNode& rhs )
{	
	return ( _altPredict != rhs._altPredict ? true : false );
}

/**********************************************************************
*
*	operator<:
*	The operator< returns false if the PredictedNode's altitude is greater 
*	than the value passed in
*
**********************************************************************/
bool PredictedNode::operator< ( const PredictedNode& rhs )
{	
	return ( _altPredict < rhs._altPredict ? true : false );
}

/**********************************************************************
*
*	operator>:
*	The operator> returns false if the PredictedNode's altitude is less
*	than the value passed in
*
**********************************************************************/
bool PredictedNode::operator> ( const PredictedNode& rhs )
{	
	return ( _altPredict > rhs._altPredict ? true : false );
}

/**********************************************************************
*
*	getLatPre:
*	returns the value stored in the attribute _latPredict
*
**********************************************************************/
double PredictedNode::getLatPre ( )
{	
	return _latPredict;
}

/**********************************************************************
*
*	getLonPre:
*	returns the value stored in the attribute _lonPredict
*
**********************************************************************/
double PredictedNode::getLonPre ( )
{	
	return _lonPredict;
}

/**********************************************************************
*
*	getAltPre:
*	returns the value stored in the attribute _altPredict
*
**********************************************************************/
double PredictedNode::getAltPre ( )
{	
	return _altPredict;
}

/**********************************************************************
*
*	getTimePre:
*	returns the value stored in the attribute _timePredict
*
**********************************************************************/
int PredictedNode::getTimePre ( )
{	
	return _timePredict;
}

/**********************************************************************
*
*	setLatPre:
*	sets the value of the attribute _latPredict
*
**********************************************************************/
void PredictedNode::setLatPre ( double latpre )
{	
	_latPredict = latpre;	
}

/**********************************************************************
*
*	setLonPre:
*	sets the value of the attribute _lonPredict
*
**********************************************************************/
void PredictedNode::setLonPre ( double lonpre )
{	
	_lonPredict = lonpre;	
}

/**********************************************************************
*
*	setAltPre:
*	sets the value of the attribute _altPredict
*
**********************************************************************/
void PredictedNode::setAltPre ( double altpre )
{	
	_altPredict = altpre;
}

/**********************************************************************
*
*	setTimePre:
*	sets the value of the attribute _timePredict
*
**********************************************************************/
void PredictedNode::setTimePre ( int time )
{	
	_timePredict = time;	
}