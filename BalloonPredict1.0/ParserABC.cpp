#include "ParserABC.h"

const int LENGTH = 28;
const int DEL1 = 6;
const int DEL2 = 13;
const int DEL3 = 23;
const int DEL4 = 27;
const int MIN = 60;
const double MAXDIST = .005;

ParserABC::ParserABC( ) : _wrong(0)
{
	char _outFile[100];
	char _dateStr[9];
	char _timeStr[9];

	_strdate( _dateStr);
    _strtime( _timeStr );

	//replaces invalid character for file names
	replaceChar( _dateStr, '/', '-' );
	replaceChar( _timeStr, ':', ' ' );

	//creates the filename for decoded data
	strcpy(_outFile, "Decoded Data for Launch Date ");
	strcat(_outFile, _dateStr);
	strcat(_outFile, " Time ");
	strcat(_outFile, _timeStr);
	strcat(_outFile, ".txt");
	_fpOutDec.open ( _outFile, ios::app );
}

ParserABC::~ParserABC( )
{	}

void ParserABC::replaceChar ( char *s, char find, char replace )
{
	//searches the string and replaces the find character
	//with the replace character
	while (*s != 0) 
	{
		if (*s == find)
		*s = replace;
		s++;
	}
}

void ParserABC::setBalloon( Balloon* balloon )
{	
	_balloon = balloon;
}

bool ParserABC::isError ( string test )
{
	//checks for the delimeters that are always in APRS data
	if ( ( test.length() == LENGTH )
		&& ( test.substr(0, 5) == _balloon->getCallSign() )
		&& ( test[DEL1] == '>' )
		&& ( test[DEL2] == ':' )
		&& ( test[DEL3] == '>' )
		&& ( test[DEL4] == '}' ) )
		return true;
	else
		return false;
}

void ParserABC::writeFile ( double lat, double lon, double alt, int time, string call )
{
	//writes out the decoded data to the decoded data file
	_fpOutDec << "Call Sign: ";
	_fpOutDec << call << endl;
	_fpOutDec << "Altitude: ";
	_fpOutDec << alt << endl;
	_fpOutDec << "Latitude: ";
	_fpOutDec << lat << endl;
	_fpOutDec << "Longitude: ";
	_fpOutDec << lon << endl;
	_fpOutDec << "Time: ";
	_fpOutDec << time << endl;
	_fpOutDec << "---------------------" << endl;
}

bool ParserABC::isBadPoint(double lat, double lon, double alt, int time)
{
	//if ( _balloon->getNewPointList().size() > 3 )
	//{
	//	if ( time - _balloon->getLatestPoint().getTime() < MIN )
	//	{
	//		if ( lat > ( _balloon->getLatestPoint().getLat() + MAXDIST * (_wrong + 1) )
	//			|| lat < ( _balloon->getLatestPoint().getLat() - MAXDIST * (_wrong + 1) )
	//			|| lon > ( _balloon->getLatestPoint().getLon() + MAXDIST * (_wrong + 1) )
	//			|| lon < ( _balloon->getLatestPoint().getLon() - MAXDIST * (_wrong + 1) ) )
	//		{
	//			++_wrong;
	//			return true;
	//		}
	//	}
	//}
	//_wrong = 0;
	return false;
}