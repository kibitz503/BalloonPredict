#include "MapControl.h"

const double METERSTOFEET = 3.2808399;
const double MINUTES = 60;

/***************************************************************
*	
*	MapControl ( HWND hwnd )
*	default c'tor for MapControl
*
***************************************************************/
MapControl::MapControl ( HWND hwnd ) : _appPtrMapPoint(NULL), _mapPtr(NULL),
	_follow(false),	_updateFrequency(1), _hwnd(hwnd), _ascentRateEnum(FEETPERSECOND)
{
	CoInitialize (NULL);

	// create MapPoint application instance
	_appPtrMapPoint.CreateInstance ("MapPoint.Application");

	// put current apps toolbars in toolbars pointer
	_appPtrMapPoint->get_Toolbars(&_toolbarsPtr);
}

/***************************************************************
*	
*	~MapControl ( )
*	default d'tor for MapControl
*
***************************************************************/
MapControl::~MapControl ( )
{
	// release MapPtr
	if (_mapPtr != NULL)
	{
		_mapPtr.Release ( );
	}
	
	// release ToolbarsPtr
	if (_toolbarsPtr != NULL)
	{
		_toolbarsPtr.Release ( );
	}

	// release AppPtrMapPoint
	if (_appPtrMapPoint != NULL)
	{
		_appPtrMapPoint->Quit ( );
		_appPtrMapPoint.Release ( );
	}

	// Release ShapePtr
	if (_ascentShapePtr != NULL)
	{
		_ascentShapePtr.Release ( );
	}

	// Release ShapePtr
	if (_descentShapePtr != NULL)
	{
		_descentShapePtr.Release ( );
	}

	CoUninitialize ( );
}


/***************************************************************
*	
*	MapControl ( const MapControl &copy )
*	copy c'tor for MapControl
*
***************************************************************/
MapControl::MapControl (const MapControl &copy)
{
	*this = copy;
}

/***************************************************************
*	
*	operator= ( const MapControl &rhs )
*	Sets left hand side MapControl equal to right hand side
*
***************************************************************/
MapControl& MapControl::operator= ( const MapControl &rhs )
{
	if (this != &rhs)
	{
		_appPtrMapPoint = rhs._appPtrMapPoint;
		_mapPtr = rhs._mapPtr;
		_toolbarsPtr = rhs._toolbarsPtr;
		_balloon = rhs._balloon;
		_hwnd = rhs._hwnd;
		_follow = rhs._follow;
		_updateFrequency = rhs._updateFrequency;
		_mapOfn = rhs._mapOfn;
		_ascentShapePtr = rhs._ascentShapePtr;
		_descentShapePtr = rhs._descentShapePtr;
		_ascentRateEnum = rhs._ascentRateEnum;
	}
	return *this;
}

/***************************************************************
*	
*	CreateMap ( ):
*	creates a default MapPoint Map
*
***************************************************************/
void MapControl::CreateMap ( )
{
	VARIANT var;
	var.vt = VT_INT;
	long toolbars_num(0);
	MapPoint::ToolbarPtr _toolbarPtr;
	
	// Make MapPoint visible
	_appPtrMapPoint->Visible = true;
	
	// Set MapPoint window state to normal
	_appPtrMapPoint->PutWindowState (MapPoint::geoWindowStateNormal);
	
	// Make it the active map
	_mapPtr = _appPtrMapPoint->ActiveMap;

	// Return how many toolbars are active
	toolbars_num = _toolbarsPtr->GetCount();

	// Close all toolbars
	for (int i(1); i <= toolbars_num; ++i)
	{
		var.intVal = i;
		_toolbarPtr = _toolbarsPtr->GetItem(&var);
		_toolbarPtr->PutVisible (false);
	}
}

/***************************************************************
*	
*	OpenMap ( HWND hwnd ):
*	opens a previously created map using a common dialog box
*
***************************************************************/
void MapControl::OpenMap ( HWND hwnd )
{
	VARIANT var;
	static TCHAR fileName[MAX_PATH], titleName[MAX_PATH];
	var.vt = VT_INT;
	MapPoint::ToolbarPtr _toolbarPtr;
	long toolbars_num(0);

	// Set up map open file name
	_mapOfn.hwndOwner			= hwnd;
	_mapOfn.lpstrFile			= fileName;
	_mapOfn.lpstrFileTitle		= titleName;
	_mapOfn.Flags				= OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	// Call open dialog box for map open file name
	if ( GetOpenFileName (&_mapOfn) )
	{
		// Open the map
		_appPtrMapPoint->OpenMap (_mapOfn.lpstrFile, false);
		
		// Make it visible
		_appPtrMapPoint->Visible = true;
		
		// Set window state to normal
		_appPtrMapPoint->PutWindowState (MapPoint::geoWindowStateNormal);
		
		// Make it the active map
		_mapPtr = _appPtrMapPoint->ActiveMap;
		
		// Return number of open toolbars
		toolbars_num = _toolbarsPtr->GetCount();

		// Close all toolbars
		for (int i(1); i <= toolbars_num; ++i)
		{
			var.intVal = i;
			_toolbarPtr = _toolbarsPtr->GetItem(&var);
			_toolbarPtr->PutVisible (false);
		}
	}
}


/***************************************************************
*	
*	RecievePoint ( )
*	displays the most recent point on the MapPoint Map
*
***************************************************************/
void MapControl::RecievePoint ( )
{
	// Check to see if the point is valid depending upon the update interval
	if ( ( _balloon->getPoints() % _updateFrequency) == 0 || _balloon->getLatestPoint().getAlt() < 2000 )
	{
		int min = _balloon->getLatestPoint().getTime() / 60;
		int sec = _balloon->getLatestPoint().getTime() % 60;
		char buffer[10];
		char point_string[20] = "Point # ";
		stringstream ss;													//Create string stream
		string pinNote;														//Create string to hold push pins note
		ss.precision (8);

		// Buffer string stream with location information
		ss << "Latitute: " << _balloon->getLatestPoint().getLat()
			<< "\nLongitude: " << _balloon->getLatestPoint().getLon()
			<< "\nAltitude: " << _balloon->getLatestPoint().getAlt() << " m"
			<< "\nTime: " <<min << " min " <<sec <<" sec";

		// Insert string stream buffer into push pins note holder
		pinNote = ss.str ( );

		_itoa(_balloon->getPoints(), buffer, 10);

		// Add push pin to Map, create pointer to created object
		PushpinPtr pushpin = _mapPtr->AddPushpin (_mapPtr->GetLocation
			(_balloon->getLatestPoint().getLat(),
			_balloon->getLatestPoint().getLon(), _balloon->getLatestPoint().getAlt()), strcat(point_string, buffer));	
		
		// Insert push pins note into created push pin
		pushpin->PutNote (pinNote.c_str ( ));								
		pushpin->BalloonState = geoDisplayName;

		// If follow is true, center the map on the point recieved
		if ( _follow )
			_mapPtr->GoToLatLong ( _balloon->getLatestPoint().getLat(), _balloon->getLatestPoint().getLon(), _mapPtr->Altitude);

		// Release pushpin
		pushpin.Release ( );
	}
}


/***************************************************************
*	
*	DrawPredictedPath ( )
*	draw the predicted path using the predicted point list
*
***************************************************************/
void MapControl::DrawPredictedPath (list<PredictedNode> predictedList, bool ascent)
{
	// Create iterator for predicted point list
	std::list<PredictedNode>::iterator iter = predictedList.begin();

	VARIANT vcoords;
	VariantInit ( &vcoords );
	V_VT (&vcoords) = VT_DISPATCH + VT_ARRAY;

	// Set up safe array with proper amount of elements
	SAFEARRAYBOUND saBound [ 1 ];
	saBound[ 0 ].cElements = predictedList.size();
	saBound[ 0 ].lLbound = 0;
	SAFEARRAY FAR* coords = SafeArrayCreate ( VT_DISPATCH, 1, saBound );
	V_ARRAY(&vcoords) = coords;

	long idx[ 1 ];

	// Iterate through predicted point list
	for (int i(0); iter != predictedList.end(); iter++, i++ )
	{
		// Add predicted points to safe array
		MapPoint::LocationPtr loc = _mapPtr->GetLocation ((*iter).getLatPre(), (*iter).getLonPre(), (*iter).getAltPre());
		idx[ 0 ] = i;
		SafeArrayPutElement ( coords, idx, loc );
		loc.Release ( );
	}

	// Draw line with the contents of variant
	if ( ascent )
	{
		
		_ascentShapePtr = _mapPtr->Shapes->AddPolyline ( vcoords );
		Shape* shape = (Shape*) _ascentShapePtr;
		shape->Line->ForeColor = ( 0x00 + 0xFF * 256 + 0x00 * 65536 );
	}

	else
	{
		
		_descentShapePtr = _mapPtr->Shapes->AddPolyline ( vcoords );
		Shape* shape = (Shape*) _descentShapePtr;
		shape->Line->ForeColor = ( 0x00 + 0x00 * 256 + 0xFF * 65536 );
	}
}


/***************************************************************
*	
*	DrawPredictedLandingLocation ( )
*	draw a circle that estimates the area of where the balloon
*	could land
*
***************************************************************/
void MapControl::DrawPredictedLandingLocation ( )
{
	// Awaiting implementation
}


/***************************************************************
*	
*	ShowMap ( )
*	hide or show the MapPoint Map
*
***************************************************************/
void MapControl::ShowMap ( )
{
	if ( _appPtrMapPoint->Visible == false )
		_appPtrMapPoint->Visible = true;
	else
		_appPtrMapPoint->Visible = false;
}


/***************************************************************
*	
*	SwitchFollow ( )
*	function which sets the map to follow or not follow the most
*	recent inserted points
*
***************************************************************/
void MapControl::SwitchFollow ( )
{
	if ( _follow )
		_follow = false;
	else
		_follow = true;
}


/***************************************************************
*	
*	getLatestPoint ( )
*	returns a string which contains the information of the most
*	recently added point
*
***************************************************************/
string MapControl::getLatestPoint ( )
{
	stringstream ss;														//Create string stream
	ss.precision (8);
	double ar(0);
	list<PredictedNode>::iterator land;

	if ( !_balloon->getNewPointList().empty() )
	{
		if ( _balloon->getNewPointList().size() > 1 )
		{
			ar = getAscentRate();	
		}

		ss << "Lat: " << _balloon->getLatestPoint().getLat()
			<<"\nLon: " << _balloon->getLatestPoint().getLon();

		if ( _ascentRateEnum == FEETPERSECOND )
		{
			ss << "\nAlt: " << _balloon->getLatestPoint().getAlt() * METERSTOFEET << " f"
			   << "\nAscent Rate: " <<ar << " f/s";
		}

		else if ( _ascentRateEnum == FEETPERMINUTE )
		{
			ss << "\nAlt: " << _balloon->getLatestPoint().getAlt() * METERSTOFEET << " f"
			   << "\nAscent Rate: " <<ar << " f/m";
		}

		else if ( _ascentRateEnum == METERPERSECOND )
		{
			ss << "\nAlt: " << _balloon->getLatestPoint().getAlt() << " m"
			   << "\nAscent Rate: " <<ar << " m/s";
		}

		ss << "\n\nPredicted Landing Location";

		if ( _balloon->getPrePointDescent().size() > 1 )
		{
			land = _balloon->getPrePointDescent().end();
			--land;
			ss	<< "\nLat: " << (*land).getLatPre()
				<< "\nLon: " << (*land).getLonPre();
		}
		else
			ss <<"\nNo Predicted Data";
	}
	else
		ss << "No new point.";

	return ss.str();
}


/***************************************************************
*	
*	update ( )
*	inherited function from ObserverABC which gets called when
*	a new point is decoded. Calls RecievePoint ( ) and 
*	DrawPredictedPath ( )
*
***************************************************************/
void MapControl::update ( )
{
	// Call Recieve Point function
	MapControl::RecievePoint ( );

	// Release current ShapePtr if it has contents
	if ( _ascentShapePtr != 0 )
	{
		_ascentShapePtr->Delete ( );
		_ascentShapePtr.Release ( );
	}

	if ( _descentShapePtr != 0 )
	{
		_descentShapePtr->Delete ( );
		_descentShapePtr.Release ( );
	}
	
	// If predicted point list has contents
	if ( _balloon->getPrePointAscent().size() > 1 )
	{
		MapControl::DrawPredictedPath( _balloon->getPrePointAscent(), true );
	}

	if ( _balloon->getPrePointDescent().size() > 1 )
	{
		MapControl::DrawPredictedPath( _balloon->getPrePointDescent(), false );
	}
}


/***************************************************************
*	
*	setData ( )
*	sets the private member _balloon equal to data
*
***************************************************************/
void MapControl::setData (Balloon* data)
{
	_balloon = data;
}


/***************************************************************
*	
*	setUpdateFrequency ( )
*	sets the private member _updateFrequency equal to updateFrequency
*
***************************************************************/
void MapControl::setUpdateFrequency (int updateFrequency)
{
	_updateFrequency = updateFrequency;
}

void MapControl::setAscentRateEnum ( ascentRate ascentRateEnum )
{
	_ascentRateEnum = ascentRateEnum;
}

/***************************************************************
*	
*	getBalloon ( )
*	returns the private member _balloon
*
***************************************************************/
Balloon* MapControl::getBalloon ( )
{
	return _balloon;
}


/***************************************************************
*	
*	getMapPtr ( )
*	returns the private member _mapPtr
*
***************************************************************/
MapPoint::_MapPtr MapControl::getMapPtr ( )
{
	return _mapPtr;
}


/***************************************************************
*	
*	getUpdateFrequency( )
*	returns the private member _updateFrequency
*
***************************************************************/
int MapControl::getUpdateFrequency ( )
{
	return _updateFrequency;
}


/***************************************************************
*	
*	getApplicationPtr( )
*	returns the private member _appPtrMapPoint
*
***************************************************************/
MapPoint::_ApplicationPtr MapControl::getApplicationPtr ( )
{
	return _appPtrMapPoint;
}


/***************************************************************
*	
*	getToolbarsPtr( )
*	returns the private member _toolbarsPtr
*
***************************************************************/
MapPoint::ToolbarsPtr MapControl::getToolbarsPtr ( )
{
	return _toolbarsPtr;
}


/***************************************************************
*	
*	mapFileInitialize( )
*	initializes the _mapOfn file for the common dialog box
*
***************************************************************/
void MapControl::mapFileInitialize ( HWND hwnd )
{
	static TCHAR filter[] =
		TEXT ("MapPoint Files (*.PTM)\0*.ptm\0");

	_mapOfn.lStructSize			= sizeof (OPENFILENAME);
	_mapOfn.hwndOwner			= hwnd;
	_mapOfn.hInstance			= NULL;
	_mapOfn.lpstrFilter			= filter;
	_mapOfn.lpstrCustomFilter	= NULL;
	_mapOfn.nMaxCustFilter		= 0;
	_mapOfn.nFilterIndex		= 0;
	_mapOfn.lpstrFile			= NULL;		// Set in Open and Close functions
	_mapOfn.nMaxFile			= MAX_PATH;
	_mapOfn.lpstrFileTitle		= NULL;		// Set in Open and Close functions
	_mapOfn.nMaxFileTitle		= MAX_PATH;
	_mapOfn.lpstrInitialDir		= NULL;
	_mapOfn.lpstrTitle			= NULL;
	_mapOfn.Flags				= 0;		// Set in Open and Close functions
	_mapOfn.nFileOffset			= 0;
	_mapOfn.nFileExtension		= 0;
	_mapOfn.lpstrDefExt			= TEXT ("ptm");
	_mapOfn.lCustData			= 0L;
	_mapOfn.lpfnHook			= NULL;
	_mapOfn.lpTemplateName		= NULL;
}

double MapControl::getAscentRate ( )
{
	double ar(0.0), alt(0.0), time(0.0);
	if ( _balloon->getNewPointList().size() > 1 )
	{
		list<CurrentNode>::iterator test = _balloon->getNewPointList().end();
		--test;
		--test;

		if ( _balloon->getLatestPoint().getAlt() - (*test).getAlt() < -20 )
		{
			ar = ( _balloon->getLatestPoint().getAlt() - (*test).getAlt() ) / ( _balloon->getLatestPoint().getTime() - (*test).getTime() );
			alt = (*test).getAlt();
			time = (*test).getTime();
			--test;
			ar  += ( alt - (*test).getAlt() ) / ( time - (*test).getTime() );
			ar /= 2;
		}
		else
		{
			list<CurrentNode>::iterator move = _balloon->getNewPointList().begin();
			alt = (*move).getAlt();
			while ( move != _balloon->getNewPointList().end() &&
				(*move).getAlt() < alt + 20 )
				++move;

			if ( move == _balloon->getNewPointList().end() )
				ar = 0.0;
			else
				ar = ( _balloon->getLatestPoint().getAlt() - (*move).getAlt() ) / ( _balloon->getLatestPoint().getTime() - (*move).getTime() );
		}

		if ( _ascentRateEnum == FEETPERSECOND)
		{
			ar *= METERSTOFEET;
		}

		else if ( _ascentRateEnum == FEETPERMINUTE )
		{
			ar *= METERSTOFEET;
			ar *= MINUTES;
		}
	}
	return ar;
}