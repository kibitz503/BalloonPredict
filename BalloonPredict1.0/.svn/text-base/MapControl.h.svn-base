/***************************************************************
*
*	MapControl.h:
*
*	Functions:
*	MapControl ( HWND hwnd )
*		default c'tor for MapControl
*	~MapControl ( )
*		default d'tor for MapControl
*	MapControl ( const MapControl &copy )
*		copy c'tor for MapControl
*	MapControl& operator= ( const MapControl &rhs )
*		overloaded operator = for MapControl
*	void CreateMap ( )
*		creates a default MapPoint Map
*	void OpenMap ( HWND hwnd )
*		opens a previously created map using a common dialog box
*	void RecievePoint ( )
*		displays the most recent point on the MapPoint Map
*	void DrawPredictedPath ( )
*		draw the predicted path using the predicted point list
*	void DrawPredictedLandingLocation ( )
*		draw a circle that estimates the area of where the balloon
*		could land
*	void ShowMap ( )
*		hide or show the MapPoint map
*	void SwitchFollow ( )
*		function which sets the map to follow or not follow the
*		most recent inserted points
*	string getLatestPoint ( )
*		returns a string which contains the information of the most
*		recently added point
*	void update ( )
*		inherited function from ObserverABC which gets called when
*		a new point is decoded. Calls RecievePoint ( ) and 
*		DrawPredictedPath ( )
*	void setData ( Balloon* data )
*		sets the private member _balloon equal to data
*	void setUpdateFrequency ( int updateFrequency )
*		sets the private member _updateFrequency equal to updateFrequency
*	Balloon* getBalloon ( )
*		returns the private member _balloon
*	int getUpdateFrequency ( )
*		returns the private member _updateFrequency
*	MapPoint::_MapPtr getMapPtr ( )
*		returns the private member _mapPtr
*	MapPoint::_ApplicationPtr getApplicationPtr ( )
*		returns the private member _appPtrMapPoint
*	MapPoint::ToolbarsPtr getToolbarsPtr ( )
*		returns the private member _toolbarsPtr
*	void mapFileInitialize ( HWND hwnd )
*		initializes the _mapOfn file for the common dialog box
*
*
*	Attributes:
*	MapPoint::_ApplicationPtr _appPtrMapPoint
*		contains a pointer to the MapPoint application
*	MapPoint::_MapPtr _mapPtr
*		contains a pointer to the pointer pointing to the MapPoint Application
*	MapPoint::ToolbarsPtr _toolbarsPtr
*		contains a pointer to all toolbars on the MapPoint Map
*	MapPoint::ShapePtr _shapePtr
*		contains a pointer to a single shape on the MapPoint Map
*	Balloon* _balloon
*		contains a pointer to the UDT Balloon
*	HWND _hwnd
*		contains a handle to the main UI window
*	bool _follow
*		bool which determins whether or not the MapPoint Map is following
*		incoming points
*	int _updateFrequency
*		integer which determins the interval of when points are displayed
*		to the MapPoint map
*	OPENFILENAME _mapOfn
*		attribute used for the commoon open dialog which will contain
*		the file name of the map to be opened
*
***************************************************************/
#ifndef MAPCONTROL_H
#define MAPCONTROL_H

#include "windows.h"
#include <commdlg.h>
#include <string>
#include <sstream>
using namespace std;

#include "CommunicationInterface.h"
using namespace MapPoint;

#include "ObserverABC.h"

enum ascentRate { FEETPERSECOND, METERPERSECOND, FEETPERMINUTE };

class MapControl : public ObserverABC
{
public:
	MapControl ( HWND hwnd );
	~MapControl ( );
	MapControl ( const MapControl &copy );
	MapControl& operator= ( const MapControl &rhs );
	void CreateMap ( );
	void OpenMap ( HWND hwnd );
	void RecievePoint ( );
	void DrawPredictedPath (list<PredictedNode> predictedList, bool ascent);
	void DrawPredictedLandingLocation ( );
	void ShowMap ( );
	void SwitchFollow ( );
	string getLatestPoint ( );
	void update ( );
	void setData ( Balloon* data );
	void setUpdateFrequency ( int updateFrequency );
	void setAscentRateEnum ( ascentRate ascentRateEnum );
	Balloon* getBalloon ( );
	int getUpdateFrequency ( );
	double getAscentRate ( );
	MapPoint::_MapPtr getMapPtr ( );
	MapPoint::_ApplicationPtr getApplicationPtr ( );
	MapPoint::ToolbarsPtr getToolbarsPtr ( );
	void mapFileInitialize ( HWND hwnd );

private:
	MapPoint::_ApplicationPtr	_appPtrMapPoint;
	MapPoint::_MapPtr			_mapPtr;
	MapPoint::ToolbarsPtr		_toolbarsPtr;
	MapPoint::ShapePtr			_ascentShapePtr;
	MapPoint::ShapePtr			_descentShapePtr;
	Balloon*					_balloon;
	HWND						_hwnd;
	bool						_follow;
	int							_updateFrequency;
	ascentRate					_ascentRateEnum;
	OPENFILENAME				_mapOfn;
};

#endif