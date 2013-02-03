#include "Predictor.h"

const double RADIUS = 6372000;
const double PI = acos (-1.0);
const double GRAVITY = 9.8016;
const double SPLIT = .1;
const double HELIUM_DENSITY = .18;
const double R = 100000 / ( 293.15 * 1.2 );	//proportanality constant for volume
const double NEWTONS = 4.4482;
const int MULTIPLE = 2;

Predictor::Predictor() : _ascentRate(0.0), _mAir(0.0), _bAir(0.0), _mVol(0.0),
_bVol(0.0), _burstAlt(0.0), _balloon(0)
{	}

/***************************************************************
*	
*	setBalloon:
*	This function sets the _balloon attribute
*
***************************************************************/
void Predictor::setBalloon(Balloon* balloon)
{	
	_balloon = balloon;
}

/***************************************************************
*	
*	latVelocity:
*	This function converts a latidudinal velocity in meters per 
*	second to latitude per second, based on the placement on the earth.
*
***************************************************************/
double Predictor::latVelocity ( double lat_mps, double altitude )
{	
	return ( ( ( 1.0 / ( RADIUS + altitude ) ) * lat_mps ) * 180.0 / PI );
}

/***************************************************************
*	
*	latMps:
*	This function converts a latidudinal velocity in latitude per 
*	second to latidudinal velocity in meters per second, based on
*	the placement on the earth.
*
***************************************************************/
double Predictor::latMps ( double lat_vel, double altitude )
{	
	return ( lat_vel * ( RADIUS + altitude ) * ( PI / 180.0 ) );	
}

/***************************************************************
*
*	lonVelocity:
*	This function converts a longitudinal velocity in meters per 
*	second to longitude per second, based on the placement on the earth.
*
***************************************************************/
double Predictor::lonVelocity ( double lon_mps, double alt, double lat )
{	
	double bottom = ( RADIUS + alt ) * cos( ( lat * PI ) / 180.0 );
	bottom = 1 / bottom;
	bottom = bottom * lon_mps * 180.0 / PI;
	return bottom;
}

/***************************************************************
*
*	lonMps:
*	This function converts a longitudinal velocity in longitude
*	per second to meters per second, based on the placement on the earth.
*
***************************************************************/
double Predictor::lonMps ( double lon_vel, double alt, double lat )
{	
	return lon_vel * ( RADIUS + alt ) * cos( lat * (PI/180) ) * ( PI / 180.0 );
}

/***************************************************************
*
*	setWind:
*	This function overwrites the NOAA wind data with the most up 
*	to date wind velocities based on the data recieved from the balloon.
*
***************************************************************/
void Predictor::setWind ( double highAlt )
{
	double lowAlt, xAvg(0), yAvg(0),holdLat(0), holdLon(0);
	int number(0), holdTime(0);
	list<WindNode>::iterator move = _balloon->getWindTable().begin();

	//moves the wind into position
	while ( (*move).getAlt() < highAlt )
		++move;

	//get the previous wind data altitude
	if ( move != _balloon->getWindTable().begin() )
	{
		--move;
		lowAlt = (*move).getAlt();
		++move;
	}
	else
		lowAlt = ( *_balloon->getNewPointList().begin() ).getAlt();

	list<CurrentNode>::iterator backPoint = _balloon->getNewPointList().end();
	backPoint--;

	if ( _balloon->getNewPointList().size() > 1 )
	{
		//accumulates all the data points between the two altitudes to get the most up to date wind data
		while ( backPoint != _balloon->getNewPointList().begin() && (*backPoint).getAlt() > lowAlt )
		{
			holdLat = (*backPoint).getLat();
			holdLon = (*backPoint).getLon();
			holdTime = (*backPoint).getTime();
			--backPoint;
			yAvg += ( holdLat - (*backPoint).getLat() ) / ( holdTime - (*backPoint).getTime() );
			xAvg += ( holdLon - (*backPoint).getLon() ) / ( holdTime - (*backPoint).getTime() );
			++number;
		}

		//averages the wind data
		xAvg /= number;
		yAvg /= number;

		//converts back to meters per second
		yAvg = latMps ( yAvg, (*move).getAlt() );
		xAvg = lonMps ( xAvg, (*move).getAlt(), _balloon->getLatestPoint().getLat() );

		//over writes the NOAA data with the current wind data
		(*move).setLatVelocity(yAvg);
		(*move).setLonVelocity(xAvg);
		(*move).setNoaa(false);
	}

}

/***************************************************************
*
*	descent:
*	This function calculates the descent of the balloon when the 
*	balloon is actually descending. The difference between this 
*	and descentPre is this uses the most current point to start 
*	predicting from.
*
***************************************************************/
void Predictor::descent ( )
{
	PredictedNode older, newer;
	int n(0);
	double h(SPLIT), z(0), zPrime(0), uPrime1(0), vPrime1(0), uPrime2(0), vPrime2(0);
	list<WindNode>::iterator movewind = _balloon->getWindTable().end();
	--movewind;

	// sets the interval to what the current points are coming in at
	setInterval();

	//sets z to the altitude of the latest point
	z = _balloon->getLatestPoint().getAlt();

	//sets zprime to the current ascent rate of the balloon
	zPrime = _ascentRate;

	//moves the wind list iterator into the correct position based on altitude
	while ( movewind != _balloon->getWindTable().begin() &&
		(*movewind).getAlt() > _balloon->getLatestPoint().getAlt() )
		--movewind;

	//sets older to the most recent point recieved from the balloon
	older.setAltPre ( _balloon->getLatestPoint().getAlt() );
	older.setLatPre ( _balloon->getLatestPoint().getLat() );
	older.setLonPre ( _balloon->getLatestPoint().getLon() );
	older.setTimePre( _balloon->getLatestPoint().getTime() );
		
	//clears the last predicted point list
	_balloon->getPrePointDescent().clear();

	//loops while the predicted altitude(z) is greater than the landing height
	while( z > _balloon->getLand() )
	{
		//calculates the altitude of the next point
		uPrime1 = uPrime ( zPrime );
		vPrime1 = vPrimeDesc ( z, zPrime );
		uPrime2 = uPrime ( zPrime + h * vPrime1 );
		vPrime2 = vPrimeDesc ( z + h * uPrime1, zPrime + h * vPrime1 );
		z = z + h * ( uPrime1 + uPrime2 ) * .5;
		zPrime = zPrime + h * ( vPrime1 + vPrime2 ) * .5;
		n++;

		//only store every 12 seconds worth of data
		if ( n >= ( (_balloon->getInterval() * MULTIPLE) / h) )
		{
			//move the wind list iterator into a new position if necessary
			if ( movewind != _balloon->getWindTable().begin() )
			{
				if ( older.getAltPre() < (*movewind).getAlt() )
					--movewind;
			}

			//sets the predicted node to be stored
			newer.setAltPre( z );
			newer.setLatPre( older.getLatPre() + ( latVelocity( (*movewind).getLatVelocity(), older.getAltPre () ) * _balloon->getInterval() * MULTIPLE ) );
			newer.setLonPre( older.getLonPre() + ( lonVelocity( (*movewind).getLonVelocity(), older.getAltPre (), older.getLatPre() ) * _balloon->getInterval() * MULTIPLE ) );
			newer.setTimePre( older.getTimePre() + _balloon->getInterval() * MULTIPLE );
			//stores the predicted point in the Predicted points list
			_balloon->getPrePointDescent().push_back( newer );
			older = newer;
			n = 0;
		}
	}
}

/***************************************************************
*
*	uPrime:
*	This function returns what it is passed. This is a formality
*	to better expand on how a second order equation should be solved
*
***************************************************************/
double Predictor::uPrime( double v )
{	
	return v;
}

/***************************************************************
*
*	vPrimeDesc:
*	This function is used to solve the descent of the second order
*	equation
*
***************************************************************/
double Predictor::vPrimeDesc (double u , double v)
{
	return ( ( _balloon->getDragPara() * _balloon->getArea() * ( v * v ) * air( u ) ) / 
		( 2 * _balloon->getMassPayload() ) ) - GRAVITY;
}

/***************************************************************
*
*	descentPre:
*	This function creates the predicted path of the balloon in the descent
*	before the balloon is descending
*
***************************************************************/
void Predictor::descentPre ( )
{
	PredictedNode older, newer;
	int n(0);
	double h(SPLIT), z(0), zPrime(0), uPrime1(0), vPrime1(0), uPrime2(0), vPrime2(0);
	list<WindNode>::iterator movewind = _balloon->getWindTable().end();
	list<PredictedNode>::iterator movepoint = _balloon->getPrePointAscent().end();
	
	--movewind;

	//sets z to the current altitude of the balloon
	if ( _balloon->getPrePointAscent().size() > 1 )
	{
		--movepoint;
		z = (*movepoint).getAltPre();

		//moves the wind list iterator into the correct position based on altitude
		while ( movewind != _balloon->getWindTable().begin() &&
			(*movewind).getAlt() > (*movepoint).getAltPre() )
			--movewind;

		//sets older to the most recent point predicted in the ascent
		older.setAltPre ( (*movepoint).getAltPre() );
		older.setLatPre ( (*movepoint).getLatPre() );
		older.setLonPre ( (*movepoint).getLonPre() );
		older.setTimePre( (*movepoint).getTimePre() );

		_balloon->getPrePointDescent().clear();

		//loops while the predicted altitude(z) is greater than the landing height
		while( z > _balloon->getLand() )
		{
			//calculates the altitude of the next point
			uPrime1 = uPrime ( zPrime );//1
			vPrime1 = vPrimeDesc ( z, zPrime );//3
			uPrime2 = uPrime ( zPrime + h * vPrime1 );//2
			vPrime2 = vPrimeDesc ( z + h * uPrime1, zPrime + h * vPrime1 );//4
			z = z + h * ( uPrime1 + uPrime2 ) * .5;
			zPrime = zPrime + h * ( vPrime1 + vPrime2 ) * .5;
			n++;

			//only store every 12 seconds worth of data
			if ( n >= ( (_balloon->getInterval() * MULTIPLE) / h) )
			{
				//move the wind list iterator into a new position if necessary
				if ( movewind != _balloon->getWindTable().begin() )
				{
					if ( older.getAltPre() < (*movewind).getAlt() )
						--movewind;
				}
				//sets the predicted node to be stored
				newer.setAltPre( z );
				newer.setLatPre( older.getLatPre() + ( latVelocity( (*movewind).getLatVelocity(), older.getAltPre () ) * _balloon->getInterval() * MULTIPLE) );
				newer.setLonPre( older.getLonPre() + ( lonVelocity( (*movewind).getLonVelocity(), older.getAltPre (), older.getLatPre() ) * _balloon->getInterval() * MULTIPLE ) );
				newer.setTimePre( older.getTimePre() + _balloon->getInterval() * MULTIPLE );
				//stores the predicted point in the Predicted points list
				_balloon->getPrePointDescent().push_back( newer );
				older = newer;
				n = 0;
			}
		}
	}
}

/***************************************************************
*
*	getAscentRate:
*	This function returns the attribute _ascentRate
*
***************************************************************/
double Predictor::getAscentRate( )
{	
	return _ascentRate;	
}

/***************************************************************
*
*	setAscentRate:
*	This function takes the previous two points and calculates 
*	the ascent rate
*
***************************************************************/
void Predictor::setAscentRatePre( )
{
	double airDen = air ( _balloon->getLatestPoint().getAlt() );
	double vol = volume ( _balloon->getLatestPoint().getAlt() );
	double totMass = ( _balloon->getMassPayload() + _balloon->getMassBalloon() );
	double areaBalloon = area( _balloon->getLatestPoint().getAlt() );
	totMass *= GRAVITY;
	double top = 2.0 * .85 * airDen * vol * GRAVITY;
	top = top - 2.0 * totMass;
	double bottom = _balloon->getDragBalloon() *  areaBalloon * airDen;
	top = top / bottom;
	_ascentRate = sqrt ( top );
}

/***************************************************************
*
*	setAscentRate:
*	This function takes the previous two points and calculates 
*	the ascent rate
*
***************************************************************/
void Predictor::setAscentRate( )
{
	list<CurrentNode>::iterator test = _balloon->getNewPointList().end();
	--test;
	--test;
	double ar = ( _balloon->getLatestPoint().getAlt() - (*test).getAlt() ) / ( _balloon->getLatestPoint().getTime() - (*test).getTime() );
	double alt = (*test).getAlt();
	double time = (*test).getTime();
	--test;
	ar  += ( alt - (*test).getAlt() ) / ( time - (*test).getTime() );
	ar /= 2;
	_ascentRate = ar;
}

double Predictor::getAscentRateReal()
{
	double ar(0.0);
	if ( _balloon->getNewPointList().size() > 2 )
	{
		list<CurrentNode>::iterator test = _balloon->getNewPointList().end();
		--test;
		--test;
		ar = ( _balloon->getLatestPoint().getAlt() - (*test).getAlt() ) / ( _balloon->getLatestPoint().getTime() - (*test).getTime() );
		double alt = (*test).getAlt();
		double time = (*test).getTime();
		--test;
		ar  += ( alt - (*test).getAlt() ) / ( time - (*test).getTime() );
		ar /= 2;
	}
	return ar;
}

/***************************************************************
*
*	ascent:
*	This function creates the predicted path of the balloon in 
*	the ascent
*
***************************************************************/
void Predictor::ascent ( )
{
	PredictedNode older, newer;
	int n(0);
	double h(SPLIT), z(0), zPrime(0), uPrime1(0), vPrime1(0), uPrime2(0), vPrime2(0);
	list<WindNode>::iterator movewind = _balloon->getWindTable().begin();

	//sets z to the current altitude of the balloon
	z = _balloon->getLatestPoint().getAlt();

	//moves the wind list iterator into the correct position based on altitude
	while ( movewind != _balloon->getWindTable().end() &&
		(*movewind).getAlt() < _balloon->getLatestPoint().getAlt() )
		++movewind;

	//set incoming point interval
	setInterval();

	//wind check to overwrite
	if ( movewind != _balloon->getWindTable().begin() )
	{
		--movewind;
		if ( (*(movewind)).getNoaa() )
			setWind( (*(movewind)).getAlt() );
		++movewind;
	}

	zPrime = _ascentRate;

	//sets older to the most recent point from the balloon
	older.setAltPre ( _balloon->getLatestPoint().getAlt() );
	older.setLatPre ( _balloon->getLatestPoint().getLat() );
	older.setLonPre ( _balloon->getLatestPoint().getLon() );
	older.setTimePre( _balloon->getLatestPoint().getTime() );

	//clears the last predicted point list
	_balloon->getPrePointAscent().clear();

	//loops while the predicted altitude(z) is less than the burst altitude
	while( older.getAltPre() < getBurstAlt() )
	{
		//move the wind list iterator into a new position if necessary
		if ( movewind != _balloon->getWindTable().end() && older.getAltPre() > (*movewind).getAlt() )
		{
			++movewind;
		}

		if ( movewind == _balloon->getWindTable().end() )
			--movewind;
		
		//sets the predicted node to be stored
		newer.setAltPre( older.getAltPre() + ( _ascentRate * _balloon->getInterval() ) * MULTIPLE );
		newer.setLatPre( older.getLatPre() + ( latVelocity( (*movewind).getLatVelocity(), older.getAltPre () ) * _balloon->getInterval() ) * MULTIPLE );
		newer.setLonPre( older.getLonPre() + ( lonVelocity( (*movewind).getLonVelocity(), older.getAltPre (), older.getLatPre() ) * _balloon->getInterval() ) * MULTIPLE );
		newer.setTimePre( older.getTimePre() + ( _balloon->getInterval() ) );

		//stores the predicted point in the Predicted points list
		_balloon->getPrePointAscent().push_back( newer );
		older = newer;
	}
}

/***************************************************************
*
*	air:
*	This function uses the attributes _mAir and _bAir to return
*	the air density at an altitude
*
***************************************************************/
double Predictor::air ( double alt )
{	
	return _bAir * exp ( _mAir * alt );
}

/***************************************************************
*
*	volume:
*	This function uses the attributes _mVol and _bVol to return
*	the volume of the balloon at an altitude
*
***************************************************************/
double Predictor::volume ( double alt )
{
	return _bVol * exp ( _mVol * alt );
}

/***************************************************************
*
*	leastSquares:
*	This function is passed an array of doubles and stores the
*	curve fitted slope and intercept
*
***************************************************************/
void Predictor::leastSquares ( list<double> random, double & m, double & b )
{
	double sx(0), sy(0), sxx(0), syy(0), sxy(0), lny(0), D(0);
	int len(_balloon->getWindTable().size());
	list<double> prediction;
	list<WindNode>::iterator movewind = _balloon->getWindTable().begin();
	list<double>::iterator move = random.begin();

	while ( movewind != _balloon->getWindTable().end() )
	{
		//creates all the sums needed to curve fit
		lny = log ( (*move) );
		sx += (*movewind).getAlt();
		sy += lny;
		sxx += (*movewind).getAlt() * (*movewind).getAlt() ;
		syy += lny * lny;
		sxy += lny * (*movewind).getAlt();
		++move;
		++movewind;
	}
	//denominator
	D = ( len * sxx ) - ( sx * sx );
	//slope
	m = ( 1 / D ) * ( len * sxy - sx * sy );
	//intercept
	b = ( 1 / D ) * ( sxx * sy - sx * sxy );
	b = exp ( b );
}

/***************************************************************
*
*	airDensity:
*	This function calculates the air density up to burst altitude.
*	Then passes it to the leastSquares function to get the curve 
*	fitted slope and intercept
*
***************************************************************/
list<double> Predictor::airDensity ( )
{
	list<double> airdensity;
	list<WindNode>::iterator move = _balloon->getWindTable().begin();

	while ( move != _balloon->getWindTable().end() )
	{
		//creats a predicted air density for the current altitude of the wind table
		airdensity.push_back( ( 1 / R ) * (*move).getAtmosPres() / (*move).getTemp() );
		++move;
	}

	//gets the slope and intercept of the air density for any altitude
	leastSquares ( airdensity, _mAir, _bAir );
	return airdensity;
}

/***************************************************************
*
*	volumeBalloon:
*	This function calculates the volume of the balloon up to burst altitude.
*	Then passes it to the leastSquares function to get the curve 
*	fitted slope and intercept
*
***************************************************************/
void Predictor::volumeBalloon ( list<double> air )
{
	double C(0), Fn(_balloon->getLift() * NEWTONS), r(.15);
	list<double> volume;
	list<double>::iterator moveden = air.begin();
	list<WindNode>::iterator movewind = _balloon->getWindTable().begin();

	//sets the first volume of the balloon
	volume.push_back( ( Fn + _balloon->getMassBalloon() * GRAVITY ) / 
		( ( 1.2 * exp( _mAir * _balloon->getLatestPoint().getAlt() ) ) * GRAVITY * ( 1 - r ) ) );		//1.2 is the sea level value
	
	list<double>::iterator movevol = volume.begin();

	//sets the mass of the helium in the balloon
	_balloon->setMassHelium( (*movevol) * ( r * 1.2 * exp( _mAir * _balloon->getLatestPoint().getAlt() ) ) );

	//sets the constant used to predict the volume of the balloon
	C =  (*movewind).getAtmosPres() * ( (*movevol)  / (*movewind).getTemp() );

	while ( movewind != _balloon->getWindTable().end() )
	{
		//creats a predicted volume for the current altitude of the wind table
		volume.push_back( C * ( (*movewind).getTemp() / (*movewind).getAtmosPres() ) );
		++movewind;
	}

	//gets the slope and intercept of the volume of the balloon for any altitude
	leastSquares ( volume, _mVol, _bVol );
}

/***************************************************************
*
*	setup:
*	This function calls the airDensity, volumeBalloon, and setBurstAlt
*	functions which initializes the class
*
***************************************************************/
void Predictor::setup ( )
{
	_balloon->setLand(_balloon->getLatestPoint().getAlt());
	list<double> air = airDensity();
	volumeBalloon ( air );
	setAscentRatePre( );
	setBurstAlt ( );
	setupFile ( );
}

/***************************************************************
*
*	area:
*	This function returns the area of the balloon at a given altitude
*
***************************************************************/
double Predictor::area( double alt )
{	
	double top = 3.0 * volume ( alt );
	double bottom = 4.0 * PI;
	top = top / bottom;
	top = pow( top, .333333333 );

	double area = PI * top * top;
	return area;

	//return ( 9.0/ (16.0 * PI) ) * pow( volume(alt), .6666 );	
}

/***************************************************************
*
*	setBurstAlt:
*	This function sets the _burstAlt attribute to the estimated burst
*	altitude based upon the volume of the balloon and the set
*	burst diameter.
*
***************************************************************/
void Predictor::setBurstAlt ( )
{
	double burstVol = (4.0/3.0) * PI * pow((_balloon->getBurst()/2.0), 3.0);
	_burstAlt = (1.0/_mVol) * log( burstVol/_bVol );
}

/***************************************************************
*
*	getBurstAlt:
*	This function returns the attribute _burstAlt
*
***************************************************************/
double Predictor::getBurstAlt ( )
{	
	return _burstAlt;	
}

/***************************************************************
*
*	setInterval:
*	This function sets the interval of te points recieved by the
*	system
*
***************************************************************/
void Predictor::setInterval ( )
{
	if ( _balloon->getNewPointList().size() > 1 )
	{
		list<CurrentNode>::iterator move = _balloon->getNewPointList().end();
		--move;

		double time1 = (*move).getTime();
		--move;
		_balloon->setInterval( time1 - (*move).getTime() );
	}
}

void Predictor::setupFile ( )
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
	strcpy(_outFile, "Predicted PreLaunch Data for Launch Date ");
	strcat(_outFile, _dateStr);
	strcat(_outFile, " Time ");
	strcat(_outFile, _timeStr);
	strcat(_outFile, ".txt");
	_fpOutPredicted.open ( _outFile, ios::app );

	_fpOutPredicted <<"Callsign: "
					<< _balloon->getCallSign() <<'\n'
					<<"Area of Parachute: "
					<< _balloon->getArea() <<'\n'
					<<"CD of Balloon: "
					<< _balloon->getDragBalloon() <<'\n'
					<<"CD of Parachute: "
					<< _balloon->getDragPara() <<'\n'
					<<"Mass of Balloon: "
					<< _balloon->getMassBalloon() <<'\n'
					<<"Mass of Payload: "
					<< _balloon->getMassPayload() <<'\n'
					<<"Mass of Helium: "
					<< _balloon->getMassHelium() <<'\n'
					<<"Lift in lbs: "
					<< _balloon->getLift() <<'\n'
					<<"Burst Diameter: "
					<< _balloon->getBurst() <<'\n'
					<<"---------------------" <<'\n';

	_fpOutPredicted <<"Air Density Intercept (b): "
					<< _bAir <<'\n'
					<<"Air Density Slope (m): "
					<< _mAir <<'\n'
					<<"Air Density at Launch: "
					<< air( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"Volume Intercept (b): "
					<< _bVol <<'\n'
					<<"Volume Slope (m): "
					<< _mVol <<'\n'
					<<"Volume at Launch: "
					<< volume ( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"\n*********************"
					<<"\nPrelaunch Prediction"
					<<"\n*********************" <<"\n\n";
}

void Predictor::replaceChar ( char *s, char find, char replace )
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

void Predictor::writeFile ( )
{
	double altHold(0), timeHold(0);
	list<PredictedNode>::iterator move = _balloon->getPrePointAscent().begin();

	if ( _balloon->getPrePointAscent().size() > 1 )
	{
		while ( move != _balloon->getPrePointAscent().end() )
		{
			_fpOutPredicted <<"Predicted Altitude: "
							<<(*move).getAltPre() <<'\n'
							<<"Predicted Latitude: "
							<<(*move).getLatPre() <<'\n'
							<<"Predicted Longitude: "
							<<(*move).getLonPre() <<'\n'
							<<"Predicted Time: "
							<<(*move).getTimePre() <<'\n';
			altHold = (*move).getAltPre();
			timeHold = (*move).getTimePre();
			++move;
			if ( move != _balloon->getPrePointAscent().end() )
			{
				_fpOutPredicted <<"Ascent Rate: "
					<<getAscentRate() <<'\n';
			}
			_fpOutPredicted <<"---------------------" <<'\n';
		}
	}

	if ( _balloon->getPrePointDescent().size() > 1 )
	{
		move = _balloon->getPrePointDescent().begin();
		while ( move != _balloon->getPrePointDescent().end() )
		{
			_fpOutPredicted <<"Predicted Altitude: "
							<<(*move).getAltPre() <<'\n'
							<<"Predicted Latitude: "
							<<(*move).getLatPre() <<'\n'
							<<"Predicted Longitude: "
							<<(*move).getLonPre() <<'\n'
							<<"Predicted Time: "
							<<(*move).getTimePre() <<'\n';
			altHold = (*move).getAltPre();
			timeHold = (*move).getTimePre();
			++move;
			if ( move != _balloon->getPrePointDescent().end() )
			{
				_fpOutPredicted <<"Ascent Rate: "
					<<getAscentRate() <<'\n';
			}
			_fpOutPredicted <<"---------------------" <<'\n';
		}
	}
}

void Predictor::writeFileDesc ( )
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
	strcpy(_outFile, "Predicted Descent Data for Launch Date ");
	strcat(_outFile, _dateStr);
	strcat(_outFile, " Time ");
	strcat(_outFile, _timeStr);
	strcat(_outFile, ".txt");
	_fpOutPredicted.open ( _outFile, ios::app );

	_fpOutPredicted <<"Callsign: "
					<< _balloon->getCallSign() <<'\n'
					<<"Area of Parachute: "
					<< _balloon->getArea() <<'\n'
					<<"CD of Balloon: "
					<< _balloon->getDragBalloon() <<'\n'
					<<"CD of Parachute: "
					<< _balloon->getDragPara() <<'\n'
					<<"Mass of Balloon: "
					<< _balloon->getMassBalloon() <<'\n'
					<<"Mass of Payload: "
					<< _balloon->getMassPayload() <<'\n'
					<<"Mass of Helium: "
					<< _balloon->getMassHelium() <<'\n'
					<<"Lift in lbs: "
					<< _balloon->getLift() <<'\n'
					<<"Burst Diameter: "
					<< _balloon->getBurst() <<'\n'
					<<"---------------------" <<'\n';

	_fpOutPredicted <<"Air Density Intercept (b): "
					<< _bAir <<'\n'
					<<"Air Density Slope (m): "
					<< _mAir <<'\n'
					<<"Air Density at Launch: "
					<< air( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"Volume Intercept (b): "
					<< _bVol <<'\n'
					<<"Volume Slope (m): "
					<< _mVol <<'\n'
					<<"Volume at Launch: "
					<< volume ( _balloon->getLatestPoint().getAlt() ) <<'\n'
					<<"---------------------" <<'\n';
	_fpOutPredicted <<"\n*********************"
					<<"\nBurst Prediction"
					<<"\n*********************" <<"\n\n";

	double altHold(0), timeHold(0);
	list<PredictedNode>::iterator move = _balloon->getPrePointDescent().begin();

	if ( _balloon->getPrePointDescent().size() > 1 )
	{
		while ( move != _balloon->getPrePointDescent().end() )
		{
			_fpOutPredicted <<"Predicted Altitude: "
							<<(*move).getAltPre() <<'\n'
							<<"Predicted Latitude: "
							<<(*move).getLatPre() <<'\n'
							<<"Predicted Longitude: "
							<<(*move).getLonPre() <<'\n'
							<<"Predicted Time: "
							<<(*move).getTimePre() <<'\n';
			altHold = (*move).getAltPre();
			timeHold = (*move).getTimePre();
			++move;
			if ( move != _balloon->getPrePointDescent().end() )
			{
				_fpOutPredicted <<"Ascent Rate: "
					<<getAscentRate() <<'\n';
			}
			_fpOutPredicted <<"---------------------" <<'\n';
		}
	}
}

void Predictor::clear()
{
	_balloon->getPrePointAscent().clear();
	_balloon->getPrePointDescent().clear();
}