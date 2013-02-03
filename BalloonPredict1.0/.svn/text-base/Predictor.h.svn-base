/***************************************************************
*
*	Predictor:
*
*	Functions:
*	void ascent ( )
*		creates the predicted path of the balloon in the ascent
*	void descent ( )
*		creates the predicted path of the balloon in the descent
*		while the balloon is descending
*	void descentPre ( )
*		creates the predicted path of the balloon in the descent
*		before the balloon is descending
*	void setBalloon( Balloon* balloon )
*		sets the _balloon attribute
*	void setWind( double altitude )
*		overwrites the NOAA wind data with the most up to date 
*		wind velocities, based on the data recieved from the balloon
*	void setAscentRate ( )
*		takes the previous two points and calculates the ascent rate
*	void setup ( )
*		This function calls the airDensity, volumeBalloon, and setBurstAlt
*		functions which initializes the class
*	double getBurstAlt ( )
*		returns the attribute _burstAlt
*	double getAscentRate( )
*		returns the attribute _ascentRate
*	double latVelocity ( double lat_mps, double altitude )
*		converts a latidudinal velocity in meters per second, to latitude
*		per second, based on the placement on the earth.
*	double lonVelocity ( double lon_mps, double altitude, double lat )
*		converts a longitudinal velocity in meters per second, to longitude
*		per second, based on the placement on the earth.
*	double uPrime ( double )
*		This function returns what it is passed. This is a formality
*		to better expand how a second order equation should be solved.
*	double vPrimeDesc ( double, double )
*		This function is used to solve the descent of the second order
*		equation
*	double vPrimeAsc ( double, double )
*	double air ( double alt )
*		This function uses the attributes _mAir and _bAir to return
*		the air density at an altitude
*	double volume ( double alt )
*		This function uses the attributes _mVol and _bVol to return
*		the volume of the balloon at an altitude
*	void leastSquares ( list<double> random, double & m, double & b )
*		This function is passed an array of doubles and stores the
*		curve fitted slope and intercept
*	list<double> airDensity ( )
*		This function calculates the air density up to burst altitude.
*		Then passes it to the leastSquares function to get the curve 
*		fitted slope and intercept
*	void volumeBalloon ( list<double> )
*		This function calculates the volume of the balloon up to burst altitude.
*		Then passes it to the leastSquares function to get the curve 
*		fitted slope and intercept
*	double area ( double alt )
*		returns the area of the balloon at a given altitude
*	void setBurstAlt ( )
*		This function sets the _burstAlt attribute to the estimated burst
*		altitude based upon the volume of the balloon and the set
*		burst diameter.
*
*
*	Attributes:
*	double _ascentRate
*		contains the current ascent rate of the balloon
*	double _mAir
*		contains the slope of the air density around the balloon
*	double _bAir
*		contains the intercept of the air density
*	double _mVol
*		contains the slope of the volume of the balloon
*	double _bVol
*		contains the intercept of the volume of the balloon
*	double _burstAlt
*		contains the predicted burst altitude of the balloon
*	Balloon* _balloon
*		contains a pointer to te balloon
*
*
***************************************************************/
#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <fstream>
#include <time.h>
#include <math.h>
#include "Balloon.h"
#include "PredictedNode.h"
using namespace std;

class Predictor
{
public:
	Predictor();
	void ascent ( );
	void descent ( );
	void descentPre ( );
	void setBalloon( Balloon* balloon );
	void setWind( double altitude );
	void setAscentRate ( );
	void setAscentRatePre ( );
	void setInterval ( );
	void setup ( );
	void writeFile ( );
	void writeFileDesc ( );
	void clear ( );
	double getBurstAlt ( );
	double getAscentRate( );
	double getAscentRateReal( );

private:
	double latVelocity ( double lat_mps, double altitude );
	double latMps ( double lat_vel, double altitude );
	double lonVelocity ( double lon_mps, double altitude, double lat );
	double lonMps ( double lon_vel, double altitude, double lat );
	double uPrime ( double );
	double vPrimeDesc ( double, double );
	double vPrimeAsc ( double, double );
	double air ( double alt );
	double volume ( double alt );
	void leastSquares ( list<double> random, double & m, double & b );
	list<double> airDensity ( );
	void volumeBalloon ( list<double> );
	double area ( double alt );
	void setBurstAlt ( );
	void setupFile ( );
	void replaceChar ( char *s, char find, char replace );
	
	double		_ascentRate;
	double		_mAir;
	double		_bAir;
	double		_mVol;
	double		_bVol;
	double		_burstAlt;
	Balloon*	_balloon;
	ofstream	_fpOutPredicted;
};

#endif