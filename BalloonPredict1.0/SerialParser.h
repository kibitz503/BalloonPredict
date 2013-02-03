#ifndef SERIALPARSER_H
#define SERIALPARSER_H

#ifdef _UNICODE
#define _T(x)      L ## x
#else /* _UNICODE */
#define _T(x)      x
#endif /* _UNICODE */

#include "ParserABC.h"
#include "CircularQueue.h"
#include "Serial.h"
#include "SerialWnd.h"

/*****************************************************
The SerialParser class inherits from the ParserABC
and handles APRS data that is received from the 
serial port.
*****************************************************/
class SerialParser : public ParserABC
{
public:
	SerialParser ( );
	SerialParser (CSerialWnd serial, HWND hwnd);
	~SerialParser ( );
	
	/*****************************************************
	This function accepts observers that wish to be 
	notified and adds them to our observer list.
	*****************************************************/
	void attach ( ObserverABC *aObserver );
	/*****************************************************
	This function notifies all of the observers that a new
	point has been received and decoded.
	*****************************************************/
	void notify ( );
	/*****************************************************
	This function opens the com port that our program will
	use to receive data.
	*****************************************************/
	void openCom ( LPCSTR comPort );
	
protected:
	/*****************************************************
	This function opens the file that our decoded APRS 
	data will be printed to for future use.
	*****************************************************/
	void openFile( );
	/*****************************************************
	This function takes the data for the com port and 
	inserts it into our queue for error checking and 
	decoding.

	It then calls the decoding functions and inserts the
	data into our balloon class
	*****************************************************/
	bool readIn ( );
	/*****************************************************
	This queue holds all of our read in data so we can 
	error check it and decode it.
	*****************************************************/
	CircularQueue<char> _queue;
	/*****************************************************
	This is the filename for our output file.
	*****************************************************/
	string				_fileName;
	/*****************************************************
	This is the tiem reference poitn from the start of
	the program;
	*****************************************************/
	time_t				_startTime;
	/*****************************************************
	The CSerialWnd is a library used by our program to
	access data from the com port.
	*****************************************************/
	CSerialWnd			_serial;
	/*****************************************************
	This is the handle to our UI.  It needs handle to 
	access the com port.
	*****************************************************/
	HWND				_hwnd;
};

#endif