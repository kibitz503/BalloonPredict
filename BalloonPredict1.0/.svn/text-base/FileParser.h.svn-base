#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <fstream>
using std::ifstream;
#include "ParserABC.h"

class FileParser :
	public ParserABC
{
public:
	FileParser ( );
	FileParser ( string file ) ;
	~FileParser ( );

	/*****************************************************
	This function accepts observers that wish to be 
	notified and adds them to our observer list.
	*****************************************************/
	virtual void attach ( ObserverABC *aObserver );
	/*****************************************************
	This function notifies all of the observers that a new
	point has been received and decoded.
	*****************************************************/
	virtual void notify ( );
	/*****************************************************
	This function set the file to read in data from.
	*****************************************************/
	void setFileName ( string file );
	/*****************************************************
	This function doesn't do anything.
	*****************************************************/
	virtual void openCom ( LPCSTR comPort );

protected:
	/*****************************************************
	This function takes the data from the file.
	It then calls the decoding functions and inserts the
	data into our balloon class
	*****************************************************/
	virtual bool readIn ( );

	//the filename to read in from
	string		_fileName;
	//the start time to read in from
	time_t		_startTime;
	//the pointer to the file where the docoded data is stored
	ofstream	_fpOutDecoded;
};

#endif