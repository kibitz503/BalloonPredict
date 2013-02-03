/***************************************************************
*
*	UserInterface.h:
*
*	Functions:
*	UserInterface ( )
* 		default c'tor for UserInterface
*	~UserInterface ( )
*		default d'tor for UserInterface
*	UserInterface ( const UserInterface &copy )
*		copy c'tor for UserInterface
*	UserInterface& operator= ( const UserInterface &rhs )
*		operator = for UserInterface
*
*	static BOOL CALLBACK InitializeDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
*		dialog box function that is the first thing opened upon starting the program. Handles the
*		creation of a map and what type of input the program is going to be using
*	void InitializeDialog ( HWND hwnd )
*		function which calls the InitializeDialogBox function
*
*	static BOOL CALLBACK SerialDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
*		dialog box function which retrieves the COM port being used and the wind data
*		table
*	void SerialDialog ( HWND hwnd )
*		function which calls the SerialDIalogBox function
*
*	static BOOL CALLBACK SettingsDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
*		dialog box function which retrieves all the attirbutes needed for the prediction
*	void SettingsDialog ( HWND hwnd );
*		function which calls the SettingsDialogBox function
*
*	void setMapControl ( MapControl* mapControl )
*		function which sets the private data member _mapControl equal to the pointer
*		passed in
*	void setIsSerial ( bool isSerial )
*		function which sets whether or not the data is being read from serial. If this is
*		false it is assumed we are reading from a file
*	void setHwnd ( HWND hwnd )
*		function which sets the private member _hwnd to the HWND passed in
*	void setReadingFrom ( string readingFrom )
*		sets the com port string of where we are recieving points from
*	void setReadingFrom ( HWND hwnd )
*		sets the file name where we are recieving points from. This function calls a 
*		common open dialog box
*	void setWindFrom ( HWND hwnd )
*		sets the file name where we are getting the wind data table from. This function
*		calls a common open dialog box
*	MapControl* getMapControlPtr ( )
*		returns private member _mapControl
*	bool getIsSerial ( )
*		returns private member _isSerial
*	HWND getHwnd ( )
*		returns private member _hwnd
*	string getReadingFrom ( )
*		returns private member _readingFrom
*	string getWindFrom ( )
*		returns private member _windFrom;
*	void windFileInitialize ( HWND hwnd )
*		initializes the _windOfn member for the common open dialog box
*	void fileFileInitialize ( HWND hwnd )
*		initializes the _fileOfn member for the common open dialog box
*
*
*	Attributes:
*	MapControl* _mapControl
*		contains a pointer to the MapControl instance being used
*	HWND _hwnd;
*		contains a pointer to the HWND of the main UI window
*	bool _isSerial
*		contains a bool representing whether or not we are reading from serial
*	string _readingFrom
*		contains the name of the COM port we are reading from
*	string _windFrom
*		contains the name of the file which holds the wind data table we will
*		need to populate our own wind data table
*	OPENFILENAME _windOfn
*		contains the OPENFILENAME object which will be used to open a wind table
*		text file
*	OPENFILENAME _fileOfn
*		contains the OPENFILENAME object which will be used to open the file which
*		holds APRS data points from previous launches
*
***************************************************************/
#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "MapControl.h"
#include "resource.h"

enum balloonDataEnum { COM_PORT, PARACHUTE_AREA, DRAG_COEFFICIENT, \
	BURST_ALTITUDE, PAYLOAD_WEIGHT, DIAMETER, TRANSMISSION };

// Helper function
bool isValidBalloonData ( char* charptr, balloonDataEnum type, HWND hwnd );

class UserInterface
{
public:
	UserInterface ( );
	~UserInterface ( );
	UserInterface ( const UserInterface &copy );
	UserInterface& operator= ( const UserInterface &rhs );

	static BOOL CALLBACK InitializeDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void InitializeDialog ( HWND hwnd );

	static BOOL CALLBACK SerialDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void SerialDialog ( HWND hwnd );

	static BOOL CALLBACK SettingsDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void SettingsDialog ( HWND hwnd );

	void setMapControl ( MapControl* mapControl );
	void setIsSerial ( bool isSerial );
	void setHwnd ( HWND hwnd );
	void setReadingFrom ( string readingFrom );
	void setReadingFrom ( HWND hwnd );
	void setWindFrom ( HWND hwnd );
	MapControl* getMapControlPtr ( );
	bool getIsSerial ( );
	HWND getHwnd ( );
	string getReadingFrom ( );
	string getWindFrom ( );
	void windFileInitialize ( HWND hwnd );
	void fileFileInitialize ( HWND hwnd );

private:
	MapControl*		_mapControl;
	HWND			_hwnd;
	bool			_isSerial;
	string			_readingFrom;
	string			_windFrom;
	OPENFILENAME	_windOfn;
	OPENFILENAME	_fileOfn;
};

#endif