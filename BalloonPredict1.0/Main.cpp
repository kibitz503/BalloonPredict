#include "windows.h"
#define COMBO 10001
#define STATIC 10002
#define QUIT 10003
#define FOLLOW 10004
#define MPERS 10005
#define FPERS 10006
#define FPERM 10007

#define X_LEN 186
#define Y_LEN 784

#include "resource.h"
#include "ControlState.h"
#include "Balloon.h"
#include "WindDataReader.h"
#include "FileParser.h"
#include "SerialParser.h"
#include "Predictor.h"
#include "MapControl.h"
#include "UserInterface.h"
LRESULT CALLBACK WndProc ( HWND, UINT, WPARAM, LPARAM );

CSerialWnd serial;	// Global serial

/************************************************************************
*
*	WinMain (HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR
*		lptszCmdLine, int nCmdShow)
*	This function is the entry point of the program.
*
************************************************************************/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hInstPrev, LPTSTR lptszCmdLine, int nCmdShow)
{
	static TCHAR AppName[] = TEXT ("BalloonPredict");	// Name of the program
	MSG msg;											// Var to hold message
	WNDCLASSEX wndclass;								// Var to define window
	HWND hwnd;											// Handle to the window

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = AppName;
	wndclass.hIconSm = NULL;

	// Register the window class
    RegisterClassEx (&wndclass);

	hwnd = CreateWindow (AppName,						// The windows class name
		TEXT ("BallonPredict"),							// The window caption	
		NULL,											// The window style
		0,												// Initial x pos
		0,												// Initial y pos
		X_LEN,											// Initial x size
		Y_LEN,											// Initial y size
		NULL,											// Parent window handle
		NULL,											// Window mwnu handle
		hInstance,										// Program instance handle
		NULL);											// Creation params

	// Show the window we just created
	ShowWindow (hwnd, nCmdShow);

	// Update the window we just created	
	UpdateWindow (hwnd);

	// Message loop
	while (GetMessage (&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

/************************************************************************
*
*	WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
*	Function recieves windows messages and handles them.	
*
*************************************************************************/
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static Balloon balloon;										// Var to hold balloon data
	static ParserABC* parser;									// Pointer to abstract parser
	static MapControl mapControl (hwnd);						// Create MapControl
	static UserInterface userInterface;							// Create UserInterface
	static WindDataReader windDataReader;						// Create WindDataReader
	static Predictor predictor;									// Create predictor
	
	// Set the predictors private data member to reference of balloon
	predictor.setBalloon(&balloon);
	static ControlState controlState(&predictor);				// Create control state and pass reference of predictor
	static HWND hwndCombo, hwndStatic, hwndQuit, hwndFollow, 
		hwndFpers, hwndFperm, hwndMpers;						// Create handles for buttons on WndProcs UI
	string buffer;												// Buffer to display on the UI the most recent point
	HDC	hdc;													// Device context for painting
	PAINTSTRUCT	ps;												// Structure for painting
	RECT rect;													// RECT for representing the UI dimensions

	// Checks to see if a serial message occurs
	if (message == CSerialWnd::mg_nDefaultComMsg)
	{
		// Create serial event
		const CSerialWnd::EEvent eEvent = CSerialWnd::EEvent(LOWORD(wParam));
		
		// Switch to see what type of event
		switch (eEvent)
		{
	    case CSerialWnd::EEventRecv:	// EVENT RECIEVED
			// Read in the point recieved
			parser->readIn();

			buffer.resize (150);

			// TODO: FIX THIS CRASHING
			buffer = mapControl.getLatestPoint();

			SetWindowText (hwndStatic, buffer.c_str());

	        break;
		}
	}

	// Switch to see what message was sent
	switch (message)
	{
	case WM_CREATE:	// WINDOW CREATION
		// Create child controls
		hwndStatic = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE |
			SS_LEFT, 10, 10, 160, 300, hwnd, (HMENU) STATIC,
			(HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

		hwndCombo = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE
			| LBS_STANDARD, 10, 330, 60 + 100, 60 + 200, hwnd, (HMENU) COMBO,
			(HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
			
		hwndFollow = CreateWindow(TEXT("button"), TEXT("Follow"), WS_CHILD |
			WS_VISIBLE | BS_CHECKBOX, 10, 400, 160, 40, hwnd, (HMENU) FOLLOW, 
			(HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

		hwndQuit = CreateWindow(TEXT("button"), TEXT("Quit"), WS_CHILD 
			| WS_VISIBLE | BS_PUSHBUTTON, 100, 600, 70, 70, hwnd, (HMENU) QUIT, 
			(HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

		// Create child control radio buttons
		hwndFpers = CreateWindow(TEXT("button"), TEXT("f/s"), 
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 470, 60, 20, hwnd,
			(HMENU) FPERS, (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

		hwndFperm = CreateWindow(TEXT("button"), TEXT("f/m"), 
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 490, 60, 20, hwnd,
			(HMENU) FPERM, (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);

		hwndMpers = CreateWindow(TEXT("button"), TEXT("m/s"), 
			WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON, 10, 510, 60, 20, hwnd,
			(HMENU) MPERS, (HINSTANCE) GetWindowLong (hwnd, GWL_HINSTANCE), NULL);
			
		// Fill combo box with intervals
		SendMessage (hwndCombo, CB_ADDSTRING, 0, (LPARAM) "1 Point Interval");
		SendMessage (hwndCombo, CB_ADDSTRING, 1, (LPARAM) "3 Point Interval");
		SendMessage (hwndCombo, CB_ADDSTRING, 2, (LPARAM) "6 Point Interval");

		// Set default radio button
		SendMessage (hwndFpers, BM_SETCHECK, 1, 0);

		// Set userInterface private member _hwnd to WndProcs hwnd
		userInterface.setHwnd (hwnd);
		
		// Set mapControls private member _balloon to balloon
		mapControl.setData (&balloon);
		
		// Set windDataReaders private member _balloon to balloon
		windDataReader.setBalloon (&balloon);
		
		// Set userInterfaces private member _mapControl to mapControl
		userInterface.setMapControl (&mapControl);

		// Set up file initialize to common open dialog for .ptm files
		mapControl.mapFileInitialize (hwnd);
		
		// Start the Initialize dialog box
		userInterface.InitializeDialog (hwnd);

		// If the user chose to read in from serial
		if (userInterface.getIsSerial())
		{
			// Populate wind data reader
			if ( !userInterface.getWindFrom().empty() )
				windDataReader.GenerateWindData(userInterface.getWindFrom());
			else
				MessageBox (hwnd, "No wind data table.", "Critical Error.", 0);
			
			// Set abstract parser to a new SerialParser
			parser = new SerialParser (serial, hwnd);
			
			// Open the com port
			if ( !userInterface.getReadingFrom().empty() )
				parser->openCom( userInterface.getReadingFrom().c_str() );
			else
				MessageBox (hwnd, "No COM port selected.", "Critical Error.", 0);
			
			// Attach parser to the observer
			parser->attach (&controlState);
		}
		
		else
		{
			// If the user didn't select serial, then they had to select
			// from file, so set abstract parser to a FileParser and pass
			// the file it is reading from
			parser = new FileParser (userInterface.getReadingFrom());
		}

		// Set parsers private member _balloon to balloon
		parser->setBalloon (&balloon);
		
		// Set parsers private member _mapControl to mapControl
		parser->attach (&mapControl);

		// If the user is reading from a file
		if ( !userInterface.getIsSerial() )
		{
			// Read in the entire file
			parser->readIn();
		}

		break;

	case WM_COMMAND:	// COMMAND MESSAGE RECIEVED
		// If the combo box has a new selection
		if (LOWORD(wParam) == COMBO && HIWORD (wParam) == LBN_SELCHANGE)
		{
			// Find which text has been selected and set update frequenchy appropiately
			switch (SendMessage (hwndCombo, CB_GETCURSEL, 0, 0))
			{
			case 0:
				mapControl.setUpdateFrequency (1);
				break;
			case 1:
				mapControl.setUpdateFrequency (3);
				break;
			case 2:
				mapControl.setUpdateFrequency (6);
				break;
			default:
				break;
			}
		}

		switch (LOWORD(wParam))
		{
		case FOLLOW:	// Follow button has been checked
			SendMessage ( (HWND) lParam, BM_SETCHECK, (WPARAM)
				!SendMessage ((HWND) lParam, BM_GETCHECK, NULL, NULL), NULL );

			// Switch the bool member follow
			mapControl.SwitchFollow ( );
			break;

		case FPERS:		// Feet Per Second Selected
			SendMessage (hwndFpers, BM_SETCHECK, 1, 0);
			SendMessage (hwndFperm, BM_SETCHECK, 0, 0);
			SendMessage (hwndMpers, BM_SETCHECK, 0, 0);

			// Set the ascent rate display
			mapControl.setAscentRateEnum ( FEETPERSECOND );
			break;

		case FPERM:		// Feet Per Minute Selected
			SendMessage (hwndFpers, BM_SETCHECK, 0, 0);
			SendMessage (hwndFperm, BM_SETCHECK, 1, 0);
			SendMessage (hwndMpers, BM_SETCHECK, 0, 0);
			
			// Set the ascent rate display to feet per minute
			mapControl.setAscentRateEnum ( FEETPERMINUTE );
			break;

		case MPERS:		// Meter Per Second Selected
			SendMessage (hwndFpers, BM_SETCHECK, 0, 0);
			SendMessage (hwndFperm, BM_SETCHECK, 0, 0);
			SendMessage (hwndMpers, BM_SETCHECK, 1, 0);

			// Set the ascent rate display to meters per second
			mapControl.setAscentRateEnum ( METERPERSECOND );
			break;

		case QUIT:
			// Clean up what we newed
			delete parser;
			PostQuitMessage(0);
			return 0;
			break;
		}

		break;
	
	case WM_PAINT:
		// Paint the window
		hdc = BeginPaint (hwnd, &ps);
		GetClientRect (hwnd, &rect);

		EndPaint (hwnd, &ps);
		return 0;

	case WM_DESTROY:
		// Clean up what we newed
		delete parser;
		PostQuitMessage(0);
		return 0;
    }

    return DefWindowProc (hwnd, message, wParam, lParam);
}