#include "UserInterface.h"
#include <tchar.h>
#include <windows.h>
#include <list>

const double CONVERT_LBS = 2.2046;

/***************************************************************
*	
*	UserInterface ( )
*	default c'tor for UserInterface
*
***************************************************************/
UserInterface::UserInterface ( ) : _isSerial (true)
{	}

/***************************************************************
*	
*	~UserInterface ( )
*	default d'tor for UserInterface
*
***************************************************************/
UserInterface::~UserInterface ( )
{	}

/***************************************************************
*	
*	UserInterface ( const UserInterface &copy )
*	copy c'tor for UserInterface
*
***************************************************************/
UserInterface::UserInterface ( const UserInterface &copy )
{
	*this = copy;
}


/***************************************************************
*	
*	operator= ( const UserInterface &rhs )
*	operator = for UserInterface
*
***************************************************************/
UserInterface& UserInterface::operator= ( const UserInterface &rhs )
{
	if ( this != &rhs )
	{
		_mapControl = rhs._mapControl;
		_hwnd = rhs._hwnd;
		_isSerial = rhs._isSerial;
		_readingFrom = rhs._readingFrom;
		_windFrom = rhs._windFrom;
		_windOfn = rhs._windOfn;
		_fileOfn = rhs._fileOfn;
	}
	return *this;
}


/***************************************************************
*	
*	InitializeDialogBox ( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
*	dialog box function that is the first thing opened upon starting the program. Handles the
*		creation of a map and what type of input the program is going to be using
*
***************************************************************/
BOOL CALLBACK UserInterface::InitializeDialogBox ( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	static UserInterface* dlgThis;

	switch ( message )
	{
	case WM_INITDIALOG:
		// Set UserInterface pointer equal to the UserInterface pointer passed in
		dlgThis = (UserInterface*) lParam;
		
		// Disable the create map and get map buttons
		EnableWindow (GetDlgItem(hDlg, IDC_CREATEMAPBUTTON), false);
		EnableWindow (GetDlgItem(hDlg, IDC_GETMAPBUTTON), false);

		break;

	case WM_COMMAND:
		switch ( LOWORD ( wParam ) )
		{
			case IDC_SERIALBUTTON:
				// Set serial to true
				dlgThis->setIsSerial (true);
				
				// Enable the create map and get map buttons
				EnableWindow (GetDlgItem(hDlg, IDC_CREATEMAPBUTTON), true);
				EnableWindow (GetDlgItem(hDlg, IDC_GETMAPBUTTON), true);
				
				break;

			case IDC_FILEBUTTON:
				// Set serial to false, we must be reading from file
				dlgThis->setIsSerial (false);
				
				// Call function to get file name
				dlgThis->setReadingFrom(hDlg);
				
				// Enable the create map and get map buttons
				EnableWindow (GetDlgItem(hDlg, IDC_CREATEMAPBUTTON), true);
				EnableWindow (GetDlgItem(hDlg, IDC_GETMAPBUTTON), true);
				
				break;

			case IDC_CREATEMAPBUTTON:
				// Create a new map
				dlgThis->getMapControlPtr()->CreateMap();

				if (dlgThis->getIsSerial())
				{
					// Call serial dialog box
					dlgThis->SerialDialog(dlgThis->getHwnd());
				}
					
				EndDialog (hDlg, TRUE);
				return true;

			case IDC_GETMAPBUTTON:
				// Call the open map function
				dlgThis->getMapControlPtr()->OpenMap( dlgThis->getHwnd() );

				if (dlgThis->getIsSerial())
				{
					// Call serial dialog box
					dlgThis->SerialDialog(dlgThis->getHwnd());
				}

				EndDialog (hDlg, TRUE);
				return true;
			
			case IDCANCEL:
				EndDialog (hDlg, TRUE);
				return true;
		}
	}

	return false;
}


/***************************************************************
*	
*	InitializeDialog ( HWND hwnd )
*	function which calls the InitializeDialogBox function
*
***************************************************************/
void UserInterface::InitializeDialog ( HWND hwnd )
{
	// Open the InitializeDialogBox dialog box
	
	// MODAL
	DialogBoxParam ( (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),
		MAKEINTRESOURCE (IDD_INITIALIZEDIALOGBOX), hwnd, InitializeDialogBox,
		(LPARAM) this );
}


/***************************************************************
*	
*	SerialDialogBox ( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
*	dialog box function which retrieves the COM port being used and the wind data
*		table
*
***************************************************************/
BOOL CALLBACK UserInterface::SerialDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UserInterface* dlgThis;
	static bool com = false, wind = false;
	static list<string> ports;
	static TCHAR comBuffer[7];

	std::list<string>::iterator iter;
	unsigned long chars;
	TCHAR devices[65535];
	TCHAR* ptr;

	switch ( message )
	{
	case WM_INITDIALOG:
		chars = QueryDosDevice (NULL, devices, 65535);
		ptr = devices;

		// Set UserInterface pointer equal to the UserInterface pointer passed in
		dlgThis = (UserInterface*) lParam;
	
		// Disable continuation
		EnableWindow (GetDlgItem(hDlg, IDOK), false);
		EnableWindow (GetDlgItem(hDlg, IDCANCEL), false);

		// Iterator through chars
		while ( chars )
		{
			int port;	// Create temp port

			// If character string COM is found, store it
			if (sscanf (ptr, "COM%d", &port) == 1)
				ports.push_back (ptr);

			TCHAR* temp_ptr = strchr (ptr, 0);

			// Decrease chars by the size of the character string read in
			chars -= (DWORD) ((temp_ptr - ptr) / sizeof(TCHAR) + 1);

			ptr = temp_ptr + 1;
		}

		if ( ports.empty ( ) )
			MessageBox (hDlg, "No COM ports detected.", "No COM ports detected", NULL);

		// Populate the choices of COM ports
		for ( iter = ports.begin(); iter != ports.end(); iter++ )
		{
			SendMessage (GetDlgItem(hDlg, IDC_COMCOMBO), CB_ADDSTRING, 0, LPARAM (iter->c_str()));
		}
		
		break;

	case WM_COMMAND:
		// Check if the COM combo box selection has been changed
		if (LOWORD(wParam) == IDC_COMCOMBO && HIWORD (wParam) == LBN_SELCHANGE)
		{
			com = true;

			if ( wind && com )
			{
				EnableWindow (GetDlgItem(hDlg, IDOK), true);
				EnableWindow (GetDlgItem(hDlg, IDCANCEL), true);
			}

			SendMessage (GetDlgItem(hDlg, IDC_COMCOMBO), CB_GETLBTEXT, (WPARAM) SendMessage
				(GetDlgItem(hDlg, IDC_COMCOMBO), CB_GETCURSEL, 0, 0), (LPARAM) comBuffer);

			dlgThis->setReadingFrom (comBuffer);
		}

		switch (LOWORD(wParam))
		{
			case IDC_GETWINDTABLEBUTTON:
				// Call the function to retrieve wind data table location
				wind = true;
				
				if ( wind && com )
				{
					EnableWindow (GetDlgItem(hDlg, IDOK), true);
					EnableWindow (GetDlgItem(hDlg, IDCANCEL), true);
				}

				dlgThis->setWindFrom ( hDlg );
				break;

			case IDOK:
			case IDCANCEL:
				// Call settings dialog box
				dlgThis->SettingsDialog ( hDlg );
				
				EndDialog (hDlg, TRUE);
				return true;
		}
	}

	return false;
}


/***************************************************************
*	
*	SerialDialog ( HWND hwnd )
*	function which calls the SerialDIalogBox function
*
***************************************************************/
void UserInterface::SerialDialog ( HWND hwnd )
{
	// Open the SerialDialogBox dialog box
	
	// MODAL
	DialogBoxParam ( (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),
		MAKEINTRESOURCE (IDD_SERIALDIALOG), hwnd, SerialDialogBox,
		(LPARAM) this );
}


/***************************************************************
*	
*	SettingsDialogBox ( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
*	dialog box function which retrieves all the attirbutes needed for the prediction
*
***************************************************************/
BOOL CALLBACK UserInterface::SettingsDialogBox (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static UserInterface* dlgThis;
	stringstream ss;
	char tmp_callsign[7], tmp_area[10], tmp_drag_balloon[10], tmp_drag_parachute[10], tmp_mass_balloon[10], 
		tmp_mass_payload[10], tmp_lift[10], tmp_transmission[10], tmp_burst[10];

	switch ( message )
	{
	case WM_INITDIALOG:
		// Set UserInterface pointer equal to the UserInterface pointer passed in
		dlgThis = (UserInterface*) lParam;
		
		break;

	case WM_COMMAND:
		switch ( LOWORD(wParam) )
		{
		case IDC_CALLSIGN_EDIT:
			break;

		case IDC_AREA_OF_PARACHUTE_EDIT:
			break;

		case IDC_COEFFICIENT_OF_DRAG_BALLOON_EDIT:
			break;

		case IDC_COEFFICIENT_OF_DRAG_PARACHUTE_EDIT:
			break;

		case IDC_TOTAL_MASS_BALLOON_EDIT:
			break;

		case IDC_TOTAL_MASS_PAYLOAD_EDIT:
			break;

		case IDC_LIFT_EDIT:
			break;

		case IDC_TRANSMISSION_EDIT:
			break;

		case IDC_BURST_DIAMETER_EDIT:
			break;

		case IDC_VIEWBUTTON:
			// Retrieve the current settings the user has saved
			ss << "ComPort: " << dlgThis->getReadingFrom()
				<< "\nCallsign: " << dlgThis->getMapControlPtr()->getBalloon()->getCallSign()
				<< "\nParachute Area: " << dlgThis->getMapControlPtr()->getBalloon()->getArea()
				<< "\nDrag Coefficient Balloon: " << dlgThis->getMapControlPtr()->getBalloon()->getDragBalloon()
				<< "\nDrag Coefficient Parachute: " << dlgThis->getMapControlPtr()->getBalloon()->getDragPara()
				<< "\nBalloon Mass: " << dlgThis->getMapControlPtr()->getBalloon()->getMassBalloon()
				<< "\nPayload Mass: " << dlgThis->getMapControlPtr()->getBalloon()->getMassPayload()
				<< "\nLift: " << dlgThis->getMapControlPtr()->getBalloon()->getLift()
				<< "\nTransmission Interval: " << dlgThis->getMapControlPtr()->getBalloon()->getInterval()
				<< "\nBurst Diameter: " << dlgThis->getMapControlPtr()->getBalloon()->getBurst();
			
			// Display the current settings the user has saved
			MessageBox (hDlg, ss.str().c_str(), "Current Data", NULL);
			
			break;

		case IDC_SAVEBUTTON:
			// Retrieve the contents of the edit boxes
			GetDlgItemText (hDlg, IDC_CALLSIGN_EDIT, tmp_callsign, 7);
			GetDlgItemText (hDlg, IDC_AREA_OF_PARACHUTE_EDIT, tmp_area, 10);
			GetDlgItemText (hDlg, IDC_COEFFICIENT_OF_DRAG_BALLOON_EDIT, tmp_drag_balloon, 10);
			GetDlgItemText (hDlg, IDC_COEFFICIENT_OF_DRAG_PARACHUTE_EDIT, tmp_drag_parachute, 10);
			GetDlgItemText (hDlg, IDC_TOTAL_MASS_BALLOON_EDIT, tmp_mass_balloon, 10);
			GetDlgItemText (hDlg, IDC_TOTAL_MASS_PAYLOAD_EDIT, tmp_mass_payload, 10);
			GetDlgItemText (hDlg, IDC_LIFT_EDIT, tmp_lift, 10);
			GetDlgItemText (hDlg, IDC_TRANSMISSION_EDIT, tmp_transmission, 10);
			GetDlgItemText (hDlg, IDC_BURST_DIAMETER_EDIT, tmp_burst, 10);

			// Set the members of balloon with what was entered in the edit boxes
			if ( isValidBalloonData(tmp_area, PARACHUTE_AREA, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setArea (atof(tmp_area));
			if ( isValidBalloonData(tmp_drag_balloon, DRAG_COEFFICIENT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setDragBalloon (atof(tmp_drag_balloon));
			if ( isValidBalloonData(tmp_drag_parachute, DRAG_COEFFICIENT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setDragPara (atof(tmp_drag_parachute));
			if ( isValidBalloonData(tmp_mass_balloon, PAYLOAD_WEIGHT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setMassBalloon (atof(tmp_mass_balloon));
			if ( isValidBalloonData(tmp_mass_payload, PAYLOAD_WEIGHT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setMassPayload (atof(tmp_mass_payload));
			if ( isValidBalloonData(tmp_transmission, TRANSMISSION, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setInterval (atof(tmp_transmission));
			if ( isValidBalloonData(tmp_burst, BURST_ALTITUDE, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setBurst (atof(tmp_burst));
			if ( isValidBalloonData(tmp_lift, BURST_ALTITUDE, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setLift (atof(tmp_lift));
			
			// Set the call sign
			dlgThis->getMapControlPtr()->getBalloon()->setCallSign(tmp_callsign);

			break;

		case IDOK:
			// Retrieve the contents of the edit boxes
			GetDlgItemText (hDlg, IDC_CALLSIGN_EDIT, tmp_callsign, 7);
			GetDlgItemText (hDlg, IDC_AREA_OF_PARACHUTE_EDIT, tmp_area, 10);
			GetDlgItemText (hDlg, IDC_COEFFICIENT_OF_DRAG_BALLOON_EDIT, tmp_drag_balloon, 10);
			GetDlgItemText (hDlg, IDC_COEFFICIENT_OF_DRAG_PARACHUTE_EDIT, tmp_drag_parachute, 10);
			GetDlgItemText (hDlg, IDC_TOTAL_MASS_BALLOON_EDIT, tmp_mass_balloon, 10);
			GetDlgItemText (hDlg, IDC_TOTAL_MASS_PAYLOAD_EDIT, tmp_mass_payload, 10);
			GetDlgItemText (hDlg, IDC_LIFT_EDIT, tmp_lift, 10);
			GetDlgItemText (hDlg, IDC_TRANSMISSION_EDIT, tmp_transmission, 10);
			GetDlgItemText (hDlg, IDC_BURST_DIAMETER_EDIT, tmp_burst, 10);

			// Set the members of balloon with what was entered in the edit boxes
			if ( isValidBalloonData(tmp_area, PARACHUTE_AREA, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setArea (atof(tmp_area));
			if ( isValidBalloonData(tmp_drag_balloon, DRAG_COEFFICIENT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setDragBalloon (atof(tmp_drag_balloon));
			if ( isValidBalloonData(tmp_drag_parachute, DRAG_COEFFICIENT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setDragPara (atof(tmp_drag_parachute));
			if ( isValidBalloonData(tmp_mass_balloon, PAYLOAD_WEIGHT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setMassBalloon (atof(tmp_mass_balloon));
			if ( isValidBalloonData(tmp_mass_payload, PAYLOAD_WEIGHT, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setMassPayload (atof(tmp_mass_payload));
			if ( isValidBalloonData(tmp_transmission, TRANSMISSION, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setInterval (atof(tmp_transmission));
			if ( isValidBalloonData(tmp_burst, BURST_ALTITUDE, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setBurst (atof(tmp_burst));
			if ( isValidBalloonData(tmp_lift, BURST_ALTITUDE, hDlg) )
				dlgThis->getMapControlPtr()->getBalloon()->setLift (atof(tmp_lift));

			// Set the call sign
			dlgThis->getMapControlPtr()->getBalloon()->setCallSign(tmp_callsign);

			EndDialog(hDlg, TRUE);
			return true;
			break;

		case IDCANCEL:
			EndDialog (hDlg, TRUE);
			return true;
		}
	}

	return false;
}


/***************************************************************
*	
*	SettingsDialog ( HWND hwnd )
*	function which calls the SettingsDialogBox function
*
***************************************************************/
void UserInterface::SettingsDialog ( HWND hwnd )
{
	DialogBoxParam ( (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE),
		MAKEINTRESOURCE (IDD_SETTINGSDIALOG), hwnd, SettingsDialogBox,
		(LPARAM) this );
}


/***************************************************************
*	
*	setMapControl ( MapControl* mapControl )
*	function which sets the private data member _mapControl equal to the pointer
*		passed in
*
***************************************************************/
void UserInterface::setMapControl ( MapControl* mapControl )
{
	_mapControl = mapControl;
}


/***************************************************************
*	
*	setIsSerial ( bool isSerial )
*	function which sets whether or not the data is being read from serial. If this is
*		false it is assumed we are reading from a file
*
***************************************************************/
void UserInterface::setIsSerial ( bool isSerial )
{
	_isSerial = isSerial;
}


/***************************************************************
*	
*	setHwnd ( HWND hwnd )
*	function which sets the private member _hwnd to the HWND passed in
*
***************************************************************/
void UserInterface::setHwnd ( HWND hwnd )
{
	_hwnd = hwnd;
}


/***************************************************************
*	
*	setReadingFrom ( string readingFrom )
*	sets the com port string of where we are recieving points from
*
***************************************************************/
void UserInterface::setReadingFrom (string readingFrom)
{
	_readingFrom = readingFrom;
}


/***************************************************************
*	
*	setReadingFrom ( HWND hwnd )
*	sets the file name where we are recieving points from. This function calls a 
*		common open dialog box
*
***************************************************************/
void UserInterface::setReadingFrom ( HWND hwnd )
{
	// Call file initialize
	this->fileFileInitialize (hwnd);
		
	static TCHAR fileName[MAX_PATH], titleName[MAX_PATH];

	// Set up the member _fileOfn
	_fileOfn.hwndOwner			= hwnd;
	_fileOfn.lpstrFile			= fileName;
	_fileOfn.lpstrFileTitle		= titleName;
	_fileOfn.Flags				= OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	// Call open common dialog
	if ( GetOpenFileName (&_fileOfn) )
	{
		_readingFrom = _fileOfn.lpstrFile;
	}
}


/***************************************************************
*	
*	setWindFrom ( HWND hwnd )
*	sets the file name where we are getting the wind data table from. This function
*		calls a common open dialog box
*
***************************************************************/
void UserInterface::setWindFrom ( HWND hwnd )
{
	// Call wind initialize
	this->windFileInitialize (hwnd);

	static TCHAR fileName[MAX_PATH], titleName[MAX_PATH];

	// Set up the member _windOfn
	_windOfn.hwndOwner			= hwnd;
	_windOfn.lpstrFile			= fileName;
	_windOfn.lpstrFileTitle		= titleName;
	_windOfn.Flags				= OFN_HIDEREADONLY | OFN_CREATEPROMPT;

	// Call open common dialog
	if ( GetOpenFileName (&_windOfn) )
	{
		_windFrom = _windOfn.lpstrFile;
	}
}


/***************************************************************
*	
*	getMapControlPtr ( )
*	returns private member _mapControl
*
***************************************************************/
MapControl* UserInterface::getMapControlPtr ( )
{
	return _mapControl;
}


/***************************************************************
*	
*	getIsSerial ( )
*	returns private member _isSerial
*
***************************************************************/
bool UserInterface::getIsSerial ( )
{
	return _isSerial;
}


/***************************************************************
*	
*	getHwnd ( )
*	returns private member _hwnd
*
***************************************************************/
HWND UserInterface::getHwnd ( )
{
	return _hwnd;
}


/***************************************************************
*	
*	getReadingFrom ( )
*	returns private member _readingFrom
*
***************************************************************/
string UserInterface::getReadingFrom ( )
{
	return _readingFrom;
}


/***************************************************************
*	
*	getWindFrom ( )
*	returns private member _windFrom;
*
***************************************************************/
string UserInterface::getWindFrom ( )
{
	return _windFrom;
}


/***************************************************************
*	
*	windFileInitialize ( HWND hwnd )
*	initializes the _windOfn member for the common open dialog box
*
***************************************************************/
void UserInterface::windFileInitialize ( HWND hwnd )
{
	static TCHAR filter[] =
		TEXT ("Text Files (*.txt)\0*.txt\0");

	_windOfn.lStructSize		= sizeof (OPENFILENAME);
	_windOfn.hwndOwner			= hwnd;
	_windOfn.hInstance			= NULL;
	_windOfn.lpstrFilter		= filter;
	_windOfn.lpstrCustomFilter	= NULL;
	_windOfn.nMaxCustFilter		= 0;
	_windOfn.nFilterIndex		= 0;
	_windOfn.lpstrFile			= NULL;		// Set in Open and Close functions
	_windOfn.nMaxFile			= MAX_PATH;
	_windOfn.lpstrFileTitle		= NULL;		// Set in Open and Close functions
	_windOfn.nMaxFileTitle		= MAX_PATH;
	_windOfn.lpstrInitialDir	= NULL;
	_windOfn.lpstrTitle			= NULL;
	_windOfn.Flags				= 0;		// Set in Open and Close functions
	_windOfn.nFileOffset		= 0;
	_windOfn.nFileExtension		= 0;
	_windOfn.lpstrDefExt		= TEXT ("txt");
	_windOfn.lCustData			= 0L;
	_windOfn.lpfnHook			= NULL;
	_windOfn.lpTemplateName		= NULL;
}


/***************************************************************
*	
*	fileFileInitialize ( HWND hwnd )
*	initializes the _fileOfn member for the common open dialog box
*
***************************************************************/
void UserInterface::fileFileInitialize ( HWND hwnd )
{
	static TCHAR filter[] =
		TEXT ("Text Files (*.txt)\0*.txt\0");

	_fileOfn.lStructSize		= sizeof (OPENFILENAME);
	_fileOfn.hwndOwner			= hwnd;
	_fileOfn.hInstance			= NULL;
	_fileOfn.lpstrFilter		= filter;
	_fileOfn.lpstrCustomFilter	= NULL;
	_fileOfn.nMaxCustFilter		= 0;
	_fileOfn.nFilterIndex		= 0;
	_fileOfn.lpstrFile			= NULL;		// Set in Open and Close functions
	_fileOfn.nMaxFile			= MAX_PATH;
	_fileOfn.lpstrFileTitle		= NULL;		// Set in Open and Close functions
	_fileOfn.nMaxFileTitle		= MAX_PATH;
	_fileOfn.lpstrInitialDir	= NULL;
	_fileOfn.lpstrTitle			= NULL;
	_fileOfn.Flags				= 0;		// Set in Open and Close functions
	_fileOfn.nFileOffset		= 0;
	_fileOfn.nFileExtension		= 0;
	_fileOfn.lpstrDefExt		= TEXT ("txt");
	_fileOfn.lCustData			= 0L;
	_fileOfn.lpfnHook			= NULL;
	_fileOfn.lpTemplateName		= NULL;
}

/***************************************************************
*	
*	isValidBalloonData ( bool* charptr, balloonDataEnum type, HWND hwnd )
*	returns true if it is valid data
*
***************************************************************/
bool isValidBalloonData ( char* charptr, balloonDataEnum type, HWND hwnd )
{
	int i (0);

	while ( charptr[i] != 0 )
	{
		// Number check
		if ( (charptr[i] >= 48 && charptr[i] <= 57)
			|| charptr[i] == 46 )
			++i;

		else
		{
			switch ( type )
			{
			case PARACHUTE_AREA:
				MessageBox (hwnd, "Error: Parachute Area must be a floating point number.",
					"Parachute Area error.", NULL);
				break;
			case DRAG_COEFFICIENT:
				MessageBox (hwnd, "Error: Drag Coefficient must be a floating point number.",
					"Drag Coefficient error.", NULL);
				break;
			case BURST_ALTITUDE:
				MessageBox (hwnd, "Error: Burst Altitude must be a floating point number.",
					"Burst Altitude error.", NULL);
				break;
			case PAYLOAD_WEIGHT:
				MessageBox (hwnd, "Error: Payload Weight must be a floating point number.",
					"Payload Weight error.", NULL);
				break;
			case DIAMETER:
				MessageBox (hwnd, "Error: Diameter must be a floating point number.",
					"Diameter error.", NULL);
				break;
			case TRANSMISSION:
				MessageBox (hwnd, "Error: Transmission must be a floating point number.",
					"Transmission error.", NULL);
				break;
			default:
				break;
			}

			return false;
		}
	}

	return true;
}