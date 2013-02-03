#ifndef WINDDATA_H
#define WINDDATA_H

#include "Balloon.h"
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>
using namespace std;

class WindDataReader
{
public:
	WindDataReader ( );
	WindDataReader(Balloon * balloonData);

	//This function opens the wind data text file and reads the file in,
	//generating the data later used in prediction to give us an idea 
	//of the wind's direction and speed at various altitudes
	void GenerateWindData(string FileName);
	//sets the attribute _balloon
	void setBalloon ( Balloon* balloon );

private:
	//holds the pointer to balloon
	Balloon * _balloon;
};

#endif