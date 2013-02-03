#include "Balloon.h"

/**********************************************************************
*
*	Balloon:
*	The default constructor of Balloon, sets all attributes to 0
*
**********************************************************************/
Balloon::Balloon ( )
{
	_burst = 0;
	_dragPara = 0;
	_dragBalloon = 0;
	_area = 0;
	_massBalloon = 0;
	_massPayload = 0;
	_massHelium = 0;
	_points = 0;
}

/**********************************************************************
*
*	Balloon:
*	The copy constructor of Balloon, sets all attributes to the same as 
*	the Balloon being passed in
*
**********************************************************************/
Balloon::Balloon ( const Balloon & copy )
{	
	*this = copy;
}

/**********************************************************************
*
*	~Balloon:
*	The destructor of the Ballon, clears the three lists stored inside
*
**********************************************************************/
Balloon::~Balloon ( )
{	
	_predictedAscent.clear();
	_predictedDescent.clear();
	_newPoints.clear();
	_windTable.clear();
}

/**********************************************************************
*
*	operator=:
*	sets all the values in the Balloon to those passed in
*
**********************************************************************/
Balloon& Balloon::operator= ( const Balloon& rhs )
{
	if ( this != &rhs )
	{
		_windTable = rhs._windTable;
		_newPoints = rhs._newPoints;
		_predictedAscent = rhs._predictedAscent;
		_predictedDescent = rhs._predictedDescent;
		_burst = rhs._burst;
		_dragPara = rhs._dragPara;
		_dragBalloon = rhs._dragBalloon;
		_area = rhs._area;
		_massBalloon = rhs._massBalloon;
		_massPayload = rhs._massPayload;
		_massHelium = rhs._massHelium;
		_points = rhs._points;
		_diameter = rhs._diameter;
		_land = rhs._land;
		_callSign = rhs._callSign;
	}
	return *this;
}

/**********************************************************************
*
*	getNewPointList:
*	returns the list of CurrentNodes in _newPoints
*
**********************************************************************/
list<CurrentNode>& Balloon::getNewPointList ( )
{
	return _newPoints;
}

/**********************************************************************
*
*	getPrePointList:
*	returns the list of PredictedNodes in _predictedPoints
*
**********************************************************************/
list<PredictedNode>& Balloon::getPrePointAscent ( )
{	
	return _predictedAscent;	
}

/**********************************************************************
*
*	getPrePointList:
*	returns the list of PredictedNodes in _predictedPoints
*
**********************************************************************/
list<PredictedNode>& Balloon::getPrePointDescent ( )
{	
	return _predictedDescent;	
}

/**********************************************************************
*
*	getWindTable:
*	returns the list of WindNodes in _windTable
*
**********************************************************************/
list<WindNode>& Balloon::getWindTable ( )
{	
	return _windTable;
}

/**********************************************************************
*
*	addWind:
*	places a new WindNode into the _windTable attribute
*
**********************************************************************/
void Balloon::addWind ( WindNode wind )
{	
	_windTable.push_back( wind );
}

/**********************************************************************
*
*	addNewPoint:
*	places a new CurrentNode into the _newPoints attribute
*
**********************************************************************/
void Balloon::addNewPoint ( CurrentNode newpoint )
{	
	_newPoints.push_back( newpoint );	
}

/**********************************************************************
*
*	addNewPoint:
*	places a new CurrentNode into the _newPoints attribute
*
**********************************************************************/
void Balloon::addNewPoint ( double lat, double lon, double alt, int time )
{
	CurrentNode temp ( lat, lon, alt, time );
	_newPoints.push_back ( temp );
	_points++;
}

/**********************************************************************
*
*	getLatestPoint:
*	returns the last point stored in _newPoints
*
**********************************************************************/
CurrentNode& Balloon::getLatestPoint ( )
{
	list<CurrentNode>::iterator last = _newPoints.end();
	--last;
	return (*last);
}

/**********************************************************************
*
*	setPrePointList:
*	overwrites the _predictedPoints attribute
*
**********************************************************************/
void Balloon::setPrePointAscent ( list<PredictedNode> & set )
{	
	_predictedAscent = set;
}

/**********************************************************************
*
*	setPrePointList:
*	overwrites the _predictedPoints attribute
*
**********************************************************************/
void Balloon::setPrePointDescent ( list<PredictedNode> & set )
{	
	_predictedDescent = set;
}

/**********************************************************************
*
*	setBurst:
*	sets the _burst attribute
*
**********************************************************************/
void Balloon::setBurst ( double burst )
{	
	_burst = burst;
}

/**********************************************************************
*
*	setDragPara:
*	sets the _dragPara attribute
*
**********************************************************************/
void Balloon::setDragPara ( double drag )
{	
	_dragPara = drag;	
}

/**********************************************************************
*
*	setDragBalloon:
*	sets the _dragBalloon attribute
*
**********************************************************************/
void Balloon::setDragBalloon ( double drag )
{	
	_dragBalloon = drag;
}

/**********************************************************************
*
*	setArea:
*	sets the _area attribute
*
**********************************************************************/
void Balloon::setArea ( double area )
{	
	_area = area;	
}

/**********************************************************************
*
*	setMassBalloon:
*	sets the _massBalloon attribute
*
**********************************************************************/
void Balloon::setMassBalloon ( double weight )
{	
	_massBalloon = weight;
}

/**********************************************************************
*
*	setMassPayload:
*	sets the _massPayload attribute
*
**********************************************************************/
void Balloon::setMassPayload ( double weight )
{	
	_massPayload = weight;	
}

/**********************************************************************
*
*	setMassHelium:
*	sets the _massHelium attribute
*
**********************************************************************/
void Balloon::setMassHelium ( double weight )
{	
	_massHelium = weight;
}

/**********************************************************************
*
*	setInterval:
*	sets the _interval attribute
*
**********************************************************************/
void Balloon::setInterval ( double interval )
{	
	_interval = interval;	
}

/**********************************************************************
*
*	setCallSign:
*	sets the _callSign attribute
*
**********************************************************************/
void Balloon::setCallSign ( string callSign )
{
	_callSign = callSign;
}

/**********************************************************************
*
*	setLand:
*	sets the _land attribute
*
**********************************************************************/
void Balloon::setLand ( double land )
{	
	_land = land;
}

/**********************************************************************
*
*	setLift:
*	sets the _lift attribute
*
**********************************************************************/
void Balloon::setLift ( double lift )
{	
	_lift = lift;
}

/**********************************************************************
*
*	setDiameter:
*	sets the _diameter attribute
*
**********************************************************************/
void Balloon::setDiameter ( double dia )
{	
	_diameter = dia;
}

/**********************************************************************
*
*	getBurst:
*	returns the value in the attribute _burst
*
**********************************************************************/
double Balloon::getBurst ( )
{	
	return _burst;
}

/**********************************************************************
*
*	getDragPara:
*	returns the value in the attribute _dragPara
*
**********************************************************************/
double Balloon::getDragPara ( )
{	
	return _dragPara;
}

/**********************************************************************
*
*	getDragBalloon:
*	returns the value in the attribute _dragBalloon
*
**********************************************************************/
double Balloon::getDragBalloon ( )
{	
	return _dragBalloon;
}

/**********************************************************************
*
*	getArea:
*	returns the value in the attribute _area
*
**********************************************************************/
double Balloon::getArea ( )
{	
	return _area;	
}

/**********************************************************************
*
*	getMassBalloon:
*	returns the value in the attribute _massBalloon
*
**********************************************************************/
double Balloon::getMassBalloon ( )
{	
	return _massBalloon;
}

/**********************************************************************
*
*	getMassPayload:
*	returns the value in the attribute _massPayload
*
**********************************************************************/
double Balloon::getMassPayload ( )
{	
	return _massPayload;
}

/**********************************************************************
*
*	getMassHelium:
*	returns the value in the attribute _massHelium
*
**********************************************************************/
double Balloon::getMassHelium ( )
{	
	return _massHelium;
}

/**********************************************************************
*
*	getInterval:
*	returns the value in the attribute _interval
*
**********************************************************************/
double Balloon::getInterval ( )
{	
	return _interval;
}

/**********************************************************************
*
*	getCallSign:
*	returns the value in the attribute _callSign
*
**********************************************************************/
string Balloon::getCallSign ( )
{	
	return _callSign;
}

/**********************************************************************
*
*	getPoints:
*	returns the value in the attribute _points
*
**********************************************************************/
int Balloon::getPoints ( )
{	
	return _points;
}

/**********************************************************************
*
*	getDiameter:
*	returns the value in the attribute _diameter
*
**********************************************************************/
double Balloon::getDiameter( )
{	
	return _diameter;
}

/**********************************************************************
*
*	getLand:
*	returns the value in the attribute _land
*
**********************************************************************/
double Balloon::getLand( )
{	
	return _land;
}

/**********************************************************************
*
*	getLift:
*	returns the value in the attribute _lift
*
**********************************************************************/
double Balloon::getLift( )
{	
	return _lift;	
}