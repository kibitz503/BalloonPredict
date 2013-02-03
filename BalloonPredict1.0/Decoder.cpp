#include "Decoder.h"

const int ALTMULT = 91;
const int ALTSUB = 33;
const int ALTDEC = 10000;
const double LONSUB = 28.0;
const double LATMULT = 10.0;

Decoder::Decoder( )
{ }

Decoder::~Decoder( )
{ }

string Decoder::decodeCallsign ( string data )
{	return data.substr(0, 6);	}


double Decoder::decodeAlt ( string data )
{
	//select the part of the string to be decoded for altitude
	string alt = data.substr(24, 3);
	//take the first character, sub by ALTSUB then mult by ALTMULT^2
	double altdec = ( ALTMULT * ALTMULT * ( alt[0] - ALTSUB ));
	//take second char, sub by ALTSUB then mult by ALTMULT
	altdec += ( ALTMULT * (alt[1] - ALTSUB) ); 
	//take third char and sub by ALTSUB
	altdec += ( alt[2]- ALTSUB );
	//account for the 10000 meters below sea level
	altdec -= ALTDEC;
	//return the decoded altitude
	return altdec; 
}

double Decoder::decodeLon ( string data )
{
	//selects the part of the string to be decoded for longitude
	string lon = data.substr(15, 3);

	//take the first char and sub by LONSUB, then add offset
	double lonDec = ( lon[0] - LONSUB ) + _offset;
	
	//if lonDec is between 180 and 189 subtract 80
	if( 180 <= lonDec && lonDec <= 189 )
	{
		lonDec -= 80;
	}

	//take the second char and sub by LONSUB
	double lonMin = ( lon[1] - LONSUB );
	
	//lonMin can never be greater than 60
	if (lonMin  >= 60 )
	{
		lonMin -= 60;
	}
	
	//take the third char and sub by LONSUB
	double lonTenMin = ( lon[2] - LONSUB );
	
	//pass decoded longitude variables to converLong to finish the conversion
	return convertLong ( lonDec, lonMin, lonTenMin );
	//longitude relies on lat calculations
}

double Decoder::decodeLat ( string data )
{
	//selects the part of the string to be decoded for latitude
	string latstr = data.substr( 7, 6 );
	double lat, latMin, latTenMin;

	//decode the first character, then mult by LATMULT
	lat = LATMULT * latDecode( latstr[0] );
	//add the decoded second char to lat
	lat +=  latDecode( latstr[1] );

	//decode the third char, then mult by LATMULT
	latMin = LATMULT * latDecode( latstr[2] );
	//add the decoded fourth char to latMin
	latMin += latDecode( latstr[3] );
	//decode the fourth char to see if it is in the north or south hemisphere
	_n_s = NS ( latstr[3] );

	//decode the fifth char, then mult by LATMULT
	latTenMin = LATMULT * latDecode( latstr[4] );
	//send the fifth char to find the offset
	_offset = offset( latstr[4] );
	//decode the sixth char and add to latTenMin
	latTenMin += latDecode( latstr[5] );
	//decode the sixth char to see if it is in the east or west hemisphere
	_e_w = EW ( latstr[5] );


	return convertLat( lat, latMin, latTenMin );
}

double Decoder::convertLat( double lat, double latMin, double latTenMin )
{
	//take latTenMin and move it back to the tenth's place
	//add it to latMin and divide by 60 to make minutes
	//add it to latitude
	lat = ( ( lat ) + ( ( latMin + ( latTenMin * .01F ) )/ 60.0F ) );

	//if in the southern hemisphere make negative
	if ( _n_s == 's' )
	{
		lat = lat - 2.0 * lat;
	}
	return lat;
}

double Decoder::convertLong ( double lonDec, double lonMin, double lonTenMin )
{
	//take lonTenMin and move it back to the tenth's place
	//add it to lonMin and divide by 60 to make minutes
	//add it to longitude
	lonDec = ( ( lonDec ) + ( ( lonMin + ( lonTenMin  * .01F ) ) / 60.0F ) );

	//if in the western hemisphere make negative
	if ( _e_w == 'w' )
	{
		lonDec = lonDec - 2.0 * lonDec;
	}
	return lonDec;
}

int Decoder::latDecode ( char data )
{
	//APRS decode function
	switch( data )
	{
	case '0':
	case 'A':
	case 'P':
		return 0;
		break;
	case '1':
	case 'B':
	case 'Q':
		return 1;
		break;
	case '2':
	case 'C':
	case 'R':
		return 2;
		break;
	case '3':
	case 'D':
	case 'S':
		return 3;
		break;
	case '4':
	case 'E':
	case 'T':
		return 4;
		break;
	case '5':
	case 'F':
	case 'U':
		return 5;
		break;
	case '6':
	case 'G':
	case 'V':
		return 6;
		break;
	case '7':
	case 'H':
	case 'W':
		return 7;
		break;
	case '8':
	case 'I':
	case 'X':
		return 8;
		break;
	case '9':
	case 'J':
	case 'Y':
		return 9;
		break;
	default:
		return 0;
		break;
	}
}

char Decoder::NS ( char data )
{
	//if 0-9 or L return south
	//else return north
	switch(data)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'L':
		return 's';
		break;
	default:
		return 'n';
		break;
	}
}

char Decoder::EW ( char data )
{
	//if 0-9 or L return east
	//else return west
	switch ( data )
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'L':
		return 'e';
		break;
	default:
		return 'w';
		break;
	}
	
}

double Decoder::offset ( char data )
{
	//if 0-9 or L return an offset of 0
	//else return an offset of 100
	switch ( data )
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'L':
		return 0;
		break;
	default:
		return 100;
		break;
	}
}