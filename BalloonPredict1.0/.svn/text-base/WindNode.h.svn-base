/**************************************************************
*
*	WindNode:
*
*	Functions:
*	void setAlt ( double )
*		sets the attribute _alt
*	void setLatVelocity ( double )
*		sets the attribute _latVel
*	void setLonVelocity ( double )
*		sets the attribute _lonVel
*	void setAtmosPres ( double )
*		sets the attribute _atmosPres
*	void setTemp ( double )
*		sets the attribute _temp
*	void setNoaa ( bool )
*		sets the attribute _noaa
*	bool getNoaa ( )
*		returns the value in attribute _noaa
*	double getAlt ( )
*		returns the value in attribute _alt
*	double getLatVelocity ( )
*		returns the value in attribute _latVel
*	double getLonVelocity ( )
*		returns the value in attribute _lonVel
*	double getAtmosPres ( )
*		returns the value in attribute _atmosPres
*	double getTemp ( )
*		returns the value in attribute _temp
*	
*	Attributes:
*	double	_alt
*		holds the altitude of the wind velocities
*	double	_latVel
*		wind velocity in the latatude direction
*	double	_lonVel
*		wind velocity in the longitude direction
*	double	_atmosPres
*		atmosphereic pressure in Pa
*	double	_temp
*		temperature in Kelvin
*	bool	_noaa
*		flag stating weather the data has been overwriten with new data
*
**************************************************************/

#ifndef WINDNODE_H
#define WINDNODE_H

class WindNode
{
public:
	WindNode ( );
	WindNode ( double, double, double, double, double, bool noaa = true );
	WindNode ( const WindNode & copy );
	~WindNode ( );
	WindNode& operator= ( const WindNode& rhs );
	bool operator!= ( const WindNode& rhs );
	bool operator< ( const WindNode& rhs );
	bool operator> ( const WindNode& rhs );

	void setAlt ( double );
	void setLatVelocity ( double );
	void setLonVelocity ( double );
	void setAtmosPres ( double );
	void setTemp ( double );
	void setNoaa ( bool );
	bool getNoaa ( );
	double getAlt ( );
	double getLatVelocity ( );
	double getLonVelocity ( );
	double getAtmosPres ( );
	double getTemp ( );


private:
	double	_alt;
	double	_latVel;
	double	_lonVel;
	double	_atmosPres;
	double	_temp;
	bool	_noaa;
};

#endif