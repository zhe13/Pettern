/////////////////////////////////////////////////////////////////////////////
//movement.h
/////////////////////////////////////////////////////////////////////////////
#ifndef movement_h
#define movement_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct feagure_movement{
	double f1;	//oritention
	double f2;	//inertial ratio
	double f3;	//aspect ratio
	double f4;	//spreadness
	double f5;	//horizontal skewness
	double f6;	//vertical skewness
	double f7;	//balance of horizontal extension
	double f8;	//balance of vertical skewness
};

typedef struct feagure_movement FEAGURE_MV;
typedef struct feagure_movement* PFEAGURE_MV;//point

//#define FGMAX 2000	// max array length

//////////////////////////////////////////////////////////////////////////////////////////////////
// compute_feagure:
// x[],y[] represent the coordinate,length represent the array length
// feaguretemp save the feagure computed
void compute_feagure(double x[],double y[],int length,PFEAGURE_MV feaguretemp);

/////////////////////////////////////////////////////////////////////////////////////////////////
// add a pressure array
void compute_feagure_ex(double x[],double y[],double pressure[],int length,PFEAGURE_MV feaguretemp);

/////////////////////////////////////////////////////////////////////////////////////////////////
// compute the feagure distance 
double feagure_distance(PFEAGURE_MV feagure1,PFEAGURE_MV feagure2);

#endif
