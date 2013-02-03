#include "SerialParser.h"

SerialParser::SerialParser()
{ }

SerialParser::SerialParser (CSerialWnd serial, HWND hwnd)
{
	_serial = serial;
	_hwnd = hwnd;
	_startTime = time (NULL);
	openFile( );
}

SerialParser::~SerialParser(void)
{
	_fpOut.close();
}

void SerialParser::openCom ( LPCSTR comPort )
{
	//opens the selectd COM port
	_serial.Open( _T(comPort), _hwnd);
	//sets the baud rate to 9600
	_serial.Setup(CSerial::EBaud9600,CSerial::EData8,CSerial::EParNone,CSerial::EStop1);
	//sets up the handshake with the system
    _serial.SetupHandshaking(CSerial::EHandshakeHardware);
	//sets a timeout to recieve data
	_serial.SetupReadTimeouts(CSerial::EReadTimeoutNonblocking);
}

void SerialParser::openFile( )
{
	 char outFile[100];
	 char dateStr [9];
	 char timeStr [9];
	
	 _strdate( dateStr);
     _strtime( timeStr );

	 //replaces character with a file readable one
	 replaceChar(dateStr, '/', '-');
	 replaceChar(timeStr, ':', ' ');

	 //name, date and time of file creation
	 strcpy(outFile, "APRS Data for Launch Date ");
	 strcat(outFile, dateStr);
	 strcat(outFile, " Time ");
	 strcat(outFile, timeStr);
	 strcat(outFile, ".txt");
	 _fpOut.open ( outFile, ios::app );
}

// Read in from serial
bool SerialParser::readIn ( )
{
	//Initializations
	char tmp_char;
	string buffer;
	int elapsed;
	double lat, lon, alt;
	string call;
	time_t _seconds;
	DWORD dwBytesRead = 0;

	do
	{
		//Read in a single byte into tmp_char
		_serial.Read ( &tmp_char, 1, &dwBytesRead );
		
		//If the serial read was succesful, prepend tmp_char
		if ( dwBytesRead > 0 )
			_queue.Prepend ( tmp_char );

		//While queue is larger than 0 and end is not K, pop
		if ( _queue.getCount() > 0 && _queue.Last() != 'K' )
		{
			while (_queue.getCount() > 0 && _queue.Last() != '}')
				_queue.Pop();

			if ( _queue.getCount() > 0 )
				_queue.Pop();
		}

		//Ready to process
		if ( _queue.getCount() > 27 )
		{
			//Start new buffer
			buffer.clear();
			buffer.resize(28);

			//For the length of APRS data
			for ( int i(0); i < 28; i++ )
			{
				if ( _queue.Last() != '}' || i == 27)
				{
					buffer[i] = _queue.Last();
					_queue.Pop();
				}

				else
				{
					//TODO: PRINT TO ERROR
					return false;
				}
			}

			if ( buffer[27] == '}' )
			{
				_seconds = time (NULL);
				elapsed = int( _seconds - _startTime);//time stamp
			
				if( !isError(buffer) )
				{
					buffer[28] = 0;

					_fpOut << buffer << endl;

					//decode the info out of the APRS format
					lat = _decoder.decodeLat ( buffer );
					lon = _decoder.decodeLon ( buffer );
					alt = _decoder.decodeAlt ( buffer );
					call = _decoder.decodeCallsign ( buffer );

					if ( !isBadPoint( lat, lon, alt, elapsed ) )
					{
						_balloon->addNewPoint ( lat, lon, alt, elapsed );

						notify();
					
						writeFile ( lat, lon, alt, elapsed, call );
					}
				}
			}
		}
	} while ( dwBytesRead > 0 );

	return true;
}

//add a new observer to notify
void SerialParser::attach(ObserverABC *aObserver)
{    
	_myObs.push_back(aObserver);
}

//tell observers I have new information
void SerialParser::notify()
{
	list<ObserverABC*>::iterator move = _myObs.begin();
	while ( move != _myObs.end() )
	{
        (*move)->update( );
		++move;
	}
}