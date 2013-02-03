#ifndef ParserABC_H
#define ParserABC_H

#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "ObserverABC.h"
#include "Decoder.h"
#include "Balloon.h"

using std::list;
using std::ofstream;
using std::string;
using std::endl;
using std::ios;

class ObserverABC;
class Decoder;
/*****************************************************
The ParserABC is a base class that can be inherited
so that a common interface is possible for all APRS
parsers.
*****************************************************/
class ParserABC
{
public:
	ParserABC( );
	~ParserABC( );
	/**************************************************************
	This function stes the _balloon attribute
	**************************************************************/
	void setBalloon(Balloon* balloon);
	/*****************************************************
	This function accepts observers that wish to be 
	notified and adds them to our observer list.
	*****************************************************/
	virtual void attach ( ObserverABC *aObserver ) = 0;
	/*****************************************************
	This function notifies all of the observers that a new
	point has been received and decoded.
	*****************************************************/
	virtual void notify ( ) = 0;
	/*****************************************************
	This function opens a com port for program use if the
	port is neccessary.
	*****************************************************/
	virtual void openCom ( LPCSTR comPort ) = 0;
	/*****************************************************
	This function writes all the decoded data to a file
	for future user analasys.
	*****************************************************/
	void writeFile ( double lat, double lon, double alt, int time, string call );
	/*****************************************************
	This function searches a string for all instances of
	a character and replaces them with a different char.
	*****************************************************/
	void replaceChar ( char *s, char find, char replace );
	/*****************************************************
	This function holds logic to check if the inputed
	APRS data is in a recognised format.  I it is not
	it returns false.
	*****************************************************/
	bool isError ( string temp );
	/*****************************************************
	This function holds logic to check if the inputed
	APRS data is decoded and fits into the path.
	*****************************************************/
	bool isBadPoint ( double, double, double, int );
	/*****************************************************
	This function holds the logic to extract APRS data
	from whatever medium it needs to.
	*****************************************************/
	virtual bool readIn ( ) = 0;

protected:
	/*****************************************************
	This function opens any needed files in the inherited
	class.
	*****************************************************/
	void openFile ( );
	//holds a decoder object
	Decoder				_decoder;
	//a list of objects to call when notified
	list<ObserverABC*>	_myObs;
	//a file pointer to point to the encoded data file
	ofstream			_fpOut;
	//a file pointer to point to the decoded data file
	ofstream			_fpOutDec;
	//a pointer to the balloon object in the system
	Balloon*			_balloon;
	int					_wrong;

};

#endif