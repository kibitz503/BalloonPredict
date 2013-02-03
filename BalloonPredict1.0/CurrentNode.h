/**************************************************************
*
*	CurrentNode:
*
*	Functions:
*	void setLat ( double lat )
*		sets the _lat attribute
*	void setLon ( double lon )
*		sets the _lon attribute
*	void setAlt ( double alt )
*		sets the _ alt attribute
*	void setTime ( int time )
*		sets the _time attribute
*	double getLat ( )
*		returns the value in the _lat attribute
*	double getLon ( )
*		returns the value in the _lon attribute
*	double getAlt ( )
*		returns the value in the _alt attribute
*	int getTime ( )
*		returns the value in the _time attribute
*	
*	Attributes:
*	double	_lat
*		holds the value of the latitude of the point
*	double	_lon
*		holds the value of the longitude of the point
*	double	_alt
*		holds the value of the altitude of the point
*	int		_time
*		holds te value of the time the point was recieved
*
**************************************************************/

#ifndef CURRENTNODE_H
#define CURRENTNODE_H

class CurrentNode
{
public:
	CurrentNode ( );
	CurrentNode ( double lat, double lon, double alt, int time );
	CurrentNode ( const CurrentNode & copy );
	~CurrentNode ( );
	CurrentNode& operator= ( const CurrentNode& rhs );
	bool operator!= ( const CurrentNode& rhs );
	bool operator< ( const CurrentNode& rhs );
	bool operator> ( const CurrentNode& rhs );

	void setLat ( double lat );
	void setLon ( double lon );
	void setAlt ( double alt );
	void setTime ( int time );
	double getLat ( );
	double getLon ( );
	double getAlt ( );
	int getTime ( );

private:
	double	_lat;
	double	_lon;
	double	_alt;
	int		_time;
};

#endif