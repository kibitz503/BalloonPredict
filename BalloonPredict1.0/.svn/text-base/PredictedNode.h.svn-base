/**************************************************************
*
*	PredictedNode:
*
*	Functions:
*	void setLatPre ( double )
*		sets the value of the attribute _latPredict
*	void setLonPre ( double )
*		sets the value of the attribute _lonPredict
*	void setAltPre ( double )
*		sets the value of the attribute _altPredict
*	void setTimePre ( int )
*		sets the value of the attribute _timePredict
*	double getLatPre ( )
*		returns the value stored in the attribute _latPredict
*	double getLonPre ( )
*		returns the value stored in the attribute _lonPredict
*	double getAltPre ( )
*		returns the value stored in the attribute _altPredict
*	int getTimePre ( )
*		returns the value stored in the attribute _timePredict
*	
*	Attributes:
*	double	_latPredict
*		holds the value of the predicted latitude
*	double	_lonPredict
*		holds the value of the predicted longitude
*	double	_altPredict
*		holds the value of the predicted altitude
*	int		_timePredict
*		holds the value of the predicted time the point should occur
*
**************************************************************/

#ifndef PREDICTEDNODE_H
#define PREDICTEDNODE_H

class PredictedNode
{
public:
	PredictedNode ( );
	PredictedNode ( double lat, double lon, double alt, int time );
	PredictedNode ( const PredictedNode & copy );
	~PredictedNode ( );
	PredictedNode& operator= ( const PredictedNode& rhs );
	bool operator!= ( const PredictedNode& rhs );
	bool operator< ( const PredictedNode& rhs );
	bool operator> ( const PredictedNode& rhs );

	void setLatPre ( double );
	void setLonPre ( double );
	void setAltPre ( double );
	void setTimePre ( int );
	double getLatPre ( );
	double getLonPre ( );
	double getAltPre ( );
	int getTimePre ( );


private:
	double	_latPredict;
	double	_lonPredict;
	double	_altPredict;
	int		_timePredict;
};

#endif