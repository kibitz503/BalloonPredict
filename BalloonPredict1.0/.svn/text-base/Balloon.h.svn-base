/**************************************************************
*
*	Balloon:
*
*	Functions:
*	void addWind ( WindNode wind )
*		places a new WindNode into the _windTable attribute
*	void addNewPoint ( CurrentNode newpoint )
*		places a new CurrentNode into the _newPoints attribute
*	void addNewPoint ( double lat, double lon, double alt, int time )
*		places a new CurrentNode into the _newPoints attribute
*	void setPrePointList ( list<PredictedNode> & set )
*		overwrites the _predictedPoints attribute
*	void setBurst ( double )
*		sets the _burst attribute
*	void setDragPara ( double )
*		sets the _dragPara attribute
*	void setDragBalloon ( double )
*		sets the _dragBalloon attribute
*	void setArea ( double )
*		sets the _area attribute
*	void setMassBalloon ( double )
*		sets the _massBalloon attribute
*	void setMassPayload ( double )
*		sets the _massPayload attribute
*	void setLand ( double )
*		sets the _land attribute
*	void setDiameter ( double )
*		sets the _diameter attribute
*	void setCallSign ( string )
*		sets the _callSign attribute
*	double getBurst ( )
*		returns the value in the attribute _burst
*	double getDragPara ( )
*		returns the value in the attribute _dragPara
*	double getDragBalloon ( )
*		returns the value in the attribute _dragBalloon
*	double getArea ( )
*		returns the value in the attribute _area
*	double getMassBalloon ( )
*		returns the value in the attribute _massBalloon
*	double getMassPayload ( )
*		returns the value in the attribute _massPayload
*	double getDiameter ( )
*		returns the value in the attribute _diameter
*	double getLand ( )
*		returns the value in the attribute _land
*	string getCallSign ( )
*		returns the value in the attribute _callSign
*	int getPoints ( )
*		returns the value in the attribute _points
*	list<CurrentNode>& getNewPointList ( )
*		returns the list of CurrentNodes in _newPoints
*	list<PredictedNode>& getPrePointList ( )
*		returns the list of PredictedNodes in _predictedPoints
*	list<WindNode>& getWindTable ( )
*		returns the list of WindNodes in _windTable
*	CurrentNode& getLatestPoint ( )
*		returns the last point stored in _newPoints
*	
*	Attributes:
*	list<WindNode>				_windTable
*		list of WindNode elements
*	list<CurrentNode>			_newPoints
*		list of CurrentNode elements
*	list<PredictedNode>			_predictedPoints
*		list of PredictedNode elements
*	double	_area
*		area of the parachute
*	double	_burst
*		burst diamter of balloon
*	double	_diameter
*		starting diameter of balloon
*	double	_dragPara
*		coeficient of drag for the parachute
*	double	_dragBalloon
*		coeficient of drag for the balloon
*	double	_land
*		the landing altitude of the balloon
*	double	_massBalloon
*		the mass of the balloon in KG
*	double	_massPayload
*		the mass of the payload in KG
*	double	_massHelium
*		the mass of the helium in the balloon in KG
*	string	_callSign
*		the callsign of the balloon's radio
*	int		_points
*		the number of current points recieved by the system
*
**************************************************************/

#ifndef BALLOON_H
#define BALLOON_H

#include "windows.h"
#include <string>
#include <list>
using std::list;
using std::string;

#include "WindNode.h"
#include "CurrentNode.h"
#include "PredictedNode.h"

class Balloon
{
public:
	Balloon ( );
	Balloon ( const Balloon & copy );
	~Balloon ( );
	Balloon& operator= ( const Balloon& rhs );

	void addWind ( WindNode wind );

	void addNewPoint ( CurrentNode newpoint );
	void addNewPoint ( double lat, double lon, double alt, int time );

	void setPrePointAscent ( list<PredictedNode> & set );
	void setPrePointDescent ( list<PredictedNode> & set );

	void setBurst ( double );
	void setDragPara ( double );
	void setDragBalloon ( double );
	void setArea ( double );
	void setMassBalloon ( double );
	void setMassPayload ( double );
	void setMassHelium ( double );
	void setLand ( double );
	void setInterval ( double );
	void setDiameter ( double );
	void setLift ( double );
	void setCallSign ( string );

	double getBurst ( );
	double getDragPara ( );
	double getDragBalloon ( );
	double getArea ( );
	double getMassBalloon ( );
	double getMassPayload ( );
	double getMassHelium ( );
	double getDiameter ( );
	double getLand ( );
	double getInterval( );
	double getLift( );
	string getCallSign ( );
	int getPoints ( );

	list<CurrentNode>& getNewPointList ( );
	list<PredictedNode>& getPrePointAscent ( );
	list<PredictedNode>& getPrePointDescent ( );
	list<WindNode>& getWindTable ( );
	CurrentNode& getLatestPoint ( );

private:
	list<WindNode>				_windTable;
	list<CurrentNode>			_newPoints;
	list<PredictedNode>			_predictedAscent;
	list<PredictedNode>			_predictedDescent;

	double	_area;
	double	_burst;
	double	_diameter;
	double	_dragPara;
	double	_dragBalloon;
	double	_land;
	double	_massBalloon;
	double	_massPayload;
	double	_massHelium;
	double	_interval;
	double	_lift;
	string	_callSign;
	int		_points;
};

#endif