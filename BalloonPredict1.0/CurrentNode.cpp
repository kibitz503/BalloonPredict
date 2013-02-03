#include "CurrentNode.h"

/**********************************************************************
*
*	CurrentNode:
*	The default constructor sets all attributes to null
*
**********************************************************************/
CurrentNode::CurrentNode ( ) : _lat(0.0), _lon(0.0), _alt(0.0), _time(0)
{	}

/**********************************************************************
*
*	CurrentNode:
*	Constructor that takes in a latitude, longitude, altitude, and time
*
**********************************************************************/
CurrentNode::CurrentNode ( double lat, double lon, double alt, 
				int time ) : _lat(lat), _lon(lon), _alt(alt), _time(time)
{	}

/**********************************************************************
*
*	CurrentNode:
*	Default copy constructor
*
**********************************************************************/
CurrentNode::CurrentNode ( const CurrentNode & copy )
{	
	*this = copy;	
}

/**********************************************************************
*
*	~CurrentNode:
*	Default destructor
*
**********************************************************************/
CurrentNode::~CurrentNode ( )
{	}

/**********************************************************************
*
*	operator=:
*	overloaded operator= function that sets the attributes located in
*	one CurrentNode to the other
*
**********************************************************************/
CurrentNode& CurrentNode::operator= ( const CurrentNode& rhs )
{	
	if ( this != &rhs )
	{
		_lat = rhs._lat;
		_lon = rhs._lon;
		_alt = rhs._alt;
		_time = rhs._time;
	}
	return *this;
}

/**********************************************************************
*
*	operator!=:
*	overloaded != operator to check the altitude of the CurrentNodes are not
*	equal
*
**********************************************************************/
bool CurrentNode::operator!= ( const CurrentNode& rhs )
{	
	return ( _alt != rhs._alt ? true : false );	
}

/**********************************************************************
*
*	operator<:
*	overloaded < operator that returns true if the altitude of the CurrentNode
*	is less than the altitude of another CurrentNode
*
**********************************************************************/
bool CurrentNode::operator< ( const CurrentNode& rhs )
{	
	return ( _alt < rhs._alt ? true : false );	
}

/**********************************************************************
*
*	operator>:
*	overloaded > operator that returns true if the altitude of the CurrentNode
*	is greater than the altitude of another CurrentNode
*
**********************************************************************/
bool CurrentNode::operator> ( const CurrentNode& rhs )
{	
	return ( _alt > rhs._alt ? true : false );	
}

/**********************************************************************
*
*	setLat:
*	sets the attribute _lat
*
**********************************************************************/
void CurrentNode::setLat ( double lat )
{	
	_lat = lat;	
}

/**********************************************************************
*
*	setLon:
*	sets the attribute _lon
*
**********************************************************************/
void CurrentNode::setLon ( double lon )
{	
	_lon = lon;
}

/**********************************************************************
*
*	setAlt:
*	sets the attribute _alt
*
**********************************************************************/
void CurrentNode::setAlt ( double alt )
{	
	_alt = alt;	
}

/**********************************************************************
*
*	setTime:
*	sets the attribute _time
*
**********************************************************************/
void CurrentNode::setTime ( int time )
{	
	_time = time;	
}

/**********************************************************************
*
*	getLat:
*	returns the value in attribute _lat
*
**********************************************************************/
double CurrentNode::getLat ( )
{	
	return _lat;	
}

/**********************************************************************
*
*	getLon:
*	returns the value in attribute _lon
*
**********************************************************************/
double CurrentNode::getLon ( )
{	
	return _lon;
}

/**********************************************************************
*
*	getAlt:
*	returns the value in attribute _alt
*
**********************************************************************/
double CurrentNode::getAlt ( )
{	
	return _alt;	
}

/**********************************************************************
*
*	getTime:
*	returns the value in attribute _time
*
**********************************************************************/
int CurrentNode::getTime ( )
{	
	return _time;
}