#include "WindNode.h"

/**********************************************************************
*
*	WindNode:
*	Default constructor
*
**********************************************************************/
WindNode::WindNode ( ): _alt(0.0), _latVel(0.0), _lonVel(0.0), _noaa(true), _atmosPres(0.0), _temp(0.0)
{	}

/**********************************************************************
*
*	WindNode:
*	Constructor that sets all the attributes in WindNode
*
**********************************************************************/
WindNode::WindNode ( double alt, double lat, double lon, double pres, double temp, bool noaa ): 
	_alt(alt), _latVel(lat), _lonVel(lon), _noaa(noaa), _atmosPres(pres), _temp(temp)
{	}

/**********************************************************************
*
*	WindNode:
*	Default copy constructor
*
**********************************************************************/
WindNode::WindNode ( const WindNode & copy )
{	
	*this = copy;
}

/**********************************************************************
*
*	~WindNode:
*	Default destructor
*
**********************************************************************/
WindNode::~WindNode ( )
{	}

/**********************************************************************
*
*	operator=:
*	overloaded operator= function that sets the attributes located in
*	one WindNode to the other
*
**********************************************************************/
WindNode& WindNode::operator= ( const WindNode& rhs )
{
	if ( this != &rhs )
	{
		_alt = rhs._alt;
		_latVel = rhs._latVel;
		_lonVel = rhs._lonVel;
		_temp = rhs._temp;
		_atmosPres = rhs._atmosPres;
		_noaa = rhs._noaa;
	}
	return *this;
}

/**********************************************************************
*
*	operator!=:
*	overloaded != operator to check the altitude of the WindNodes are not
*	equal
*
**********************************************************************/
bool WindNode::operator!= ( const WindNode& rhs )
{	
	return ( _alt != rhs._alt ? true : false );
}

/**********************************************************************
*
*	operator<:
*	overloaded < operator that returns true if the altitude of the WindNode
*	is less than the altitude of another WindNode
*
**********************************************************************/
bool WindNode::operator< ( const WindNode& rhs )
{	
	return (_alt < rhs._alt ? true : false);
}

/**********************************************************************
*
*	operator>:
*	overloaded > operator that returns true if the altitude of the WindNode
*	is greater than the altitude of another WindNode
*
**********************************************************************/
bool WindNode::operator> ( const WindNode& rhs )
{	
	return (_alt > rhs._alt ? true : false);
}

/**********************************************************************
*
*	setAlt:
*	sets the attribute _alt
*
**********************************************************************/
void WindNode::setAlt ( double alt )
{	
	_alt = alt;
}

/**********************************************************************
*
*	setLatVelocity:
*	sets the attribute _latVel
*
**********************************************************************/
void WindNode::setLatVelocity ( double latvel)
{	
	_latVel = latvel;
}

/**********************************************************************
*
*	setLonVelocity:
*	sets the attribute _lonVel
*
**********************************************************************/
void WindNode::setLonVelocity ( double lonvel)
{	
	_lonVel = lonvel;
}

/**********************************************************************
*
*	setAtmosPres:
*	sets the attribute _atmosPres
*
**********************************************************************/
void WindNode::setAtmosPres ( double atmos )
{	
	_atmosPres = atmos;	
}

/**********************************************************************
*
*	setTemp:
*	sets the attribute _temp
*
**********************************************************************/
void WindNode::setTemp ( double temp )
{	
	_temp = temp;
}

/**********************************************************************
*
*	setNoaa:
*	sets the attribute _noaa
*
**********************************************************************/
void WindNode::setNoaa ( bool noaa )
{	
	_noaa = noaa;	
}

/**********************************************************************
*
*	getNoaa:
*	returns the value in attribute _noaa
*
**********************************************************************/
bool WindNode::getNoaa ( )
{	
	return _noaa;
}

/**********************************************************************
*
*	getAlt:
*	returns the value in attribute _alt
*
**********************************************************************/
double WindNode::getAlt ( )
{	
	return _alt;	
}

/**********************************************************************
*
*	getLatVelocity:
*	returns the value in attribute _latVel
*
**********************************************************************/
double WindNode::getLatVelocity ( )
{
	return _latVel;
}

/**********************************************************************
*
*	getLonVelocity:
*	returns the value in attribute _lonVel
*
**********************************************************************/
double WindNode::getLonVelocity ( )
{	
	return _lonVel;	
}

/**********************************************************************
*
*	getAtmosPres:
*	returns the value in attribute _atmosPres
*
**********************************************************************/
double WindNode::getAtmosPres ( )
{	
	return _atmosPres;
}

/**********************************************************************
*
*	getTemp:
*	returns the value in attribute _temp
*
**********************************************************************/
double WindNode::getTemp ( )
{	
	return _temp;	
}
