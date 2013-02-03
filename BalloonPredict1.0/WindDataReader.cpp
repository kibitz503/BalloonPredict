#include "windDataReader.h"

const double PI = acos(-1.0);
#define KnotsToMeters 1852
#define HoursToSeconds 3600
#define DegreesToRadians 180
#define CelciusToKelvin 273.15
#define hPaToPa 100				//conversion from hPa (hectopascals) to pascals


WindDataReader::WindDataReader ( )
{	}

WindDataReader::WindDataReader ( Balloon * balloonData ) : _balloon(balloonData)
{	}

void WindDataReader::setBalloon ( Balloon* balloon )
{	_balloon = balloon;	}

//--------------------GenerateWindData-------------------------------------
//   This function opens the wind data text file and reads the file in,
//		generating the data later used in prediction to give us an idea 
//		of the wind's direction and speed at various altitudes
//--------------------------------------------------------------------------
void WindDataReader::GenerateWindData( std::string FileName )
{
	FILE* in_p = NULL;
	in_p = fopen( FileName.c_str(), "r+");	//the open dialog box to get the wind text file
	int windDataAltitudeM (0);		//altitude measured in meters
	int windDataDRCTDeg (0);	//Wind direction measured in degrees
	int windDataSKNTKnot (0);	//wind speed measured in knots
	double XwindVelMeters(0);	// wind velocity in meters per second pertaining to east-west
	double YwindVelMeters(0);	// wind velocity in meters per second pertaining to north-south
	double metersPerSecond(0);	// wind velocity in meters per second, before conversion to xy		
	double angle(0);			//this is the direction of the wind in radians
	float atmosPres(0);			//atmospheric pressure at a specific altitude
	float temp(0);				//temperature in celcius at a specific altitude
	int trashint;				//a temporary int into which unneeded info is read in, then trashed
	float trashfloat;			//a temporary float into which unneeded info is read in, then trashed
	string windDataTrashString;	//a temporary string into which unneeded info is read in, then trashed
	WindNode Wind;				//the wind node into which information is stored, then passed to addWind()
	
	if(!in_p)
	{
		throw "Wind file is not found";
	}

	else
	{	//while the file is open
		while (!feof(in_p)) 
		{	//check to see if the current line contains a float double float float double float double double float float float in that order
			if(fscanf(in_p, "%f %d %f %f %d %f %d %d %f %f %f", &atmosPres, &windDataAltitudeM, &temp, &trashfloat, &trashint, 
				&trashfloat, &windDataDRCTDeg, &windDataSKNTKnot, &trashfloat, &trashfloat, &trashfloat) == 11)
			{
				//convert knots per hour to meters per second
				metersPerSecond = windDataSKNTKnot * KnotsToMeters / HoursToSeconds;
				
				//direction of wind from read in is direction wind is blowing from 
				//in nautical degrees north, we add 180 degrees to offset this for later calculations
				windDataDRCTDeg += 180;
				
				//if the wind data is >360, find the direction in range of unit circle
				if ( windDataDRCTDeg >= 360 )
					windDataDRCTDeg -= 360;
				
				//convert angle from degrees to radians
				angle = windDataDRCTDeg * ( PI / DegreesToRadians );

				//find the respective x and y velocity values at angle in meters per second 
				YwindVelMeters = ( metersPerSecond * cos( angle ) );
				XwindVelMeters = ( metersPerSecond * sin( (angle) ) );
				
				
				temp += CelciusToKelvin;
				atmosPres *= hPaToPa;	//convert from hectopascals to pascals

				//set wind object's data members to correct values
				Wind.setAlt( double(windDataAltitudeM) );
				Wind.setLatVelocity( double(YwindVelMeters) );
				Wind.setLonVelocity( double(XwindVelMeters) );
				Wind.setAtmosPres( double(atmosPres) );
				Wind.setTemp( double( temp ) );
				//add wind object to balloon's wind table
				_balloon->addWind(Wind);
				
				//reset values for next run-through
				atmosPres = 0;
				temp = 0;
			}
			else
			{	//if the file doesn't containt he correct data in the right order, scrap it all
				fscanf (in_p, "%[^\n\r]s", &windDataTrashString );
			}
		}
	}
}

