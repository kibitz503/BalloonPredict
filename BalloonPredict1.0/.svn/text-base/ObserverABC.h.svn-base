#ifndef OBSERVERABC_H
#define OBSERVERABC_H

#include "ParserABC.h"

class ParserABC;
/***************************************
This class gives classes the ability to
inherate the interface to receive data
from the parser.
***************************************/
class ObserverABC
{
public:
	ObserverABC ( );
	virtual ~ObserverABC ( );
	/***************************************
	This function calls the logic that is 
	triggered by a new event form the
	observee
	***************************************/
	virtual void update ( ) = 0;
};

#endif