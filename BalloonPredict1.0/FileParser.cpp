#include "FileParser.h"

/************************************************************************
*
*	FileParser( )
*	C'tor for FileParser.
*
************************************************************************/
FileParser::FileParser( )
{	}

/************************************************************************
*
*	FileParser( string file )
*	1 arg c'tor for FileParser which sets private member _fileName equal
*	to the string passed in
*
************************************************************************/
FileParser::FileParser( string file ) : _fileName(file)
{	}

/************************************************************************
*
*	~FileParser( )
*	D'tor for FileParser.
*
************************************************************************/
FileParser::~FileParser( )
{	}

/************************************************************************
*
*	readIn( )
*	This function takes the data from the file. It then calls the 
*	decoding functions and inserts the data into our balloon class
*
************************************************************************/
bool FileParser::readIn( )
{
	char temp[30];									// temp buffer to hold APRS string
	ifstream _fpIn;									// declare my input stream 
    _startTime = time (NULL);						// set starting time
    time_t _seconds;								// variable to hold seconds
	int _elapsed = 0;								// elapsed time
	double lat, lon, alt;							// variables to hold the latitude, longitude, and altitute of the point read in
	string call;									// string which holds the callsign

	// Open the input file
	_fpIn.open( _fileName.c_str() );				

	// While the file pointer is not at the end, continue reading
	while( !_fpIn.eof( ) )
	{
		// Grab 30 bytes from the text file or until a new line is reached
		_fpIn.getline (temp, 30); 
		
		// Time stamp the point
		_seconds = time (NULL);
		_elapsed = int( _seconds - _startTime);
		
		// Check to see if there is an error
		if( !isError( temp ) )
		{
			// If there is no error, decode the data read in
			lat = _decoder.decodeLat ( temp );
			lon = _decoder.decodeLon ( temp );
			alt = _decoder.decodeAlt ( temp );
			call = _decoder.decodeCallsign ( temp );

			// Add the new point to the balloon data structure
			if ( !isBadPoint ( lat, lon, alt, _elapsed ) )
			{
				_balloon->addNewPoint ( lat, lon, alt, _elapsed );

				// Write the decoded point to the file
				writeFile ( lat, lon, alt, _elapsed, call );

				// Notifies the system the point has been recieved
				notify();
			}
		}
	}

	// Close the input file
	_fpIn.close();

	return true;
}

/************************************************************************
*
*	attach( ObserverABC* aObserver )
*	This function accepts observers that wish to be notified and adds 
*	them to our observer list.
*
************************************************************************/
void FileParser::attach( ObserverABC* aObserver )
{    
	_myObs.push_back( aObserver );	
}

/************************************************************************
*
*	notify( )
*	This function notifies all of the observers that a new point has been
*	received and decoded.
*
************************************************************************/
void FileParser::notify( )
{
	list<ObserverABC*>::iterator move = _myObs.begin();		// List of all attached observers
	
	// Iterator through the entire list
	while ( move != _myObs.end() )
	{
		// Update the observer
        (*move)->update( );

		++move;
	}
}

/************************************************************************
*
*	setFileName ( string file )
*	This function set the file to read in data from.
*
************************************************************************/
void FileParser::setFileName ( string file )
{	
	_fileName = file;	
}

/************************************************************************
*
*	openCom ( LPCSTR comPort )
*	Empty function, needed due to polymorphism.
*
************************************************************************/
void FileParser::openCom ( LPCSTR comPort )
{	}