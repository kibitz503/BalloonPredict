#ifndef DECODER_H
#define DECODER_H

#include <string>
using std::string;

/*****************************************************
The Decoder class is passed an APRS Mic-e data string 
and returns a specific decoded data item with each 
function call.
*****************************************************/
class Decoder
{
public:
	Decoder ( );
	~Decoder ( );
	/*****************************************************
	This function is passed an APRS string and returns 
	the call sign.
	*****************************************************/
	string decodeCallsign ( string );
	/*****************************************************
	This function is passed and APRS string and returns 
	the decoded altitude.
	*****************************************************/
	double decodeAlt ( string );
	/*****************************************************
	This function is passed and APRS string and returns 
	the decoded longitude
	*****************************************************/
	double decodeLon ( string );
	/*****************************************************
	This function is passed and APRS string and returns 
	the decoded latitude.
	*****************************************************/
	double decodeLat ( string );
	/*****************************************************
	This function is passed a string a char to find in the
	string and a char to replace it with.  This is used
	to remove unprintable chars from file names.
	*****************************************************/
	void replaceChar ( char* s, char find, char replace );

private:
	/*****************************************************
	This function runs a char from the latitude field
	through a decoding table to get the correct value and
	returns it.
	*****************************************************/
	int latDecode ( char data );
	/*****************************************************
	This function returns if the data is for the northern
	or southern hemisphere.
	*****************************************************/
	char NS ( char data );
	/*****************************************************
	This function returns if the data is from the eastren 
	or western hemisphere
	*****************************************************/
	char EW ( char data );
	/*****************************************************
	This function determins if the longitude needs offset 
	and what that offset should be.
	*****************************************************/
	double offset ( char data );
	/*****************************************************
	This converts latitude from hours/min n/s to decimal.
	*****************************************************/
	double convertLat ( double, double, double );
	/*****************************************************
	This converts longitude from hours/min e/w to decimal.
	*****************************************************/
	double convertLong ( double, double, double );

	//holds what the offset should be based on the latitude
	double			_offset;
	//holds the east or west hemisphere
	char			_e_w;
	//holds the north or south hemisphere
	char			_n_s;
};

#endif