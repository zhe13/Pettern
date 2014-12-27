//movement.c
// date: 2001.9.22

#include "movement.h"
#define pi 3.1415926535
//////////////////////////////////////////////////////////////////////////////////////////////////
// compute_feature:
// x[],y[] represent the coordinate,length represent the array length
// featuretemp save the feagure computed
void compute_feagure(double x[],double y[],int length,PFEAGURE_MV feaguretemp)
{
	double fg1,fg2,fg3,fg4,fg5,fg6,fg7,fg8;
	int i;
	double theta; //angle
	double lm1,lm2;
	double u00=0,u02=0,u20=0,u11=0;
	double u03a=0,u03s=0,u03;//u03a>0,u03s<0
	double u30a=0,u30s=0,u30;//u30a>0,u30s<0
	double u12a=0,u12s=0,u12;//u12a>0,u12s<0
	double u21a=0,u21s=0,u21;//u21a>0,u21s<0
	double size;
	double xmax=0,xmin=10000000.0,ymax=0,ymin=100000000.0;
	double xav=0,yav=0;
	
	//compute xav,yav;
	for(i=0;i<length;i++){
		xav+=x[i];
		yav+=y[i];
	}//end for
	xav/=(double)length;
	yav/=(double)length;
	
	//compute the necessary parameter
	for(i=0;i<length;i++){
		//compute xmax,ymax,xmin,ymin
		if(x[i]>xmax)
			xmax=x[i];
		if(x[i]<xmin)
			xmin=x[i];
		if(y[i]>ymax)
			ymax=y[i];
		if(y[i]<ymin)
			ymin=y[i];
			
		//add u02,u20......
		u02+=(y[i]-yav)*(y[i]-yav);
		u20+=(x[i]-xav)*(x[i]-xav);
		u11+=(x[i]-xav)*(y[i]-yav);
		
		u30=(x[i]-xav)*(x[i]-xav)*(x[i]-xav);
		if(u30>0)
			u30a+=u30;
		else
			u30s-=u30;
			
		u03=(y[i]-yav)*(y[i]-yav)*(y[i]-yav);
		if(u03>0)
			u03a+=u03;
		else
			u03s-=u03;
			
		u12=(x[i]-xav)*(y[i]-yav)*(y[i]-yav);
		if(u12>0)
			u12a+=u12;
		else
			u12s-=u12;
			
		u21=(x[i]-xav)*(x[i]-xav)*(y[i]-yav);
		if(u21>0)
			u21a+=u21;
		else
			u21s-=u21;
	}//end for
	
	theta=atan((u02-u20+sqrt((u20-u02)*(u20-u02)+4*u11*u11))/(2*u11));
	lm1=((u20+u02)+sqrt((u20-u02)*(u20-u02)+4*u11*u11))/2;
	lm1=((u20+u02)-sqrt((u20-u02)*(u20-u02)+4*u11*u11))/2;
	
	size=sqrt((xmax-xmin)*(ymax-ymin));
	fg1=theta*2/pi;//orientation
	fg2=(lm1-lm2)/(lm1+lm2);//inertial ratio
	fg3=((u20-u02)/(u20+u02)+1)/2;//aspect ration
	fg4=sqrt((u02+u20)/(double)length)*2/size;//spreadness
	
	fg5=((u30a-u30s)/(u30a+u30s)+1)/2;	//horizantal skewness
	fg6=((u03a-u03s)/(u03a+u03s)+1)/2;	//vertical skewness
	fg7=((u21a-u21s)/(u21a+u21s)+1)/2;  //banlance of horizontal extension
	fg8=((u12a-u12s)/(u12a+u12s)+1)/2;	//banlance of vertical extention
	
	feaguretemp->f1=fg1;
	feaguretemp->f2=fg2;
	feaguretemp->f3=fg3;
	feaguretemp->f4=fg4;
	feaguretemp->f5=fg5;
	feaguretemp->f6=fg6;
	feaguretemp->f7=fg7;
	feaguretemp->f8=fg8;
}//end feagure compute
	
void compute_feagure_ex(double x[],double y[],double pressure[],int length,PFEAGURE_MV feaguretemp)
{
	double fg1,fg2,fg3,fg4,fg5,fg6,fg7,fg8;
	double m00=0.0;
	int i,j;
	double theta; //angle
	double lm1,lm2;
	double u00=0,u02=0,u20=0,u11=0;
	double u03a=0,u03s=0,u03;//u03a>0,u03s<0
	double u30a=0,u30s=0,u30;//u30a>0,u30s<0
	double u12a=0,u12s=0,u12;//u12a>0,u12s<0
	double u21a=0,u21s=0,u21;//u21a>0,u21s<0
	double size;
	double xmax=0,xmin=10000000.0,ymax=0,ymin=100000000.0;
	double xav=0,yav=0;
	
	//compute xav,yav,m00;
	for(i=0;i<length;i++){
		xav+=x[i]*pressure[i];
		yav+=y[i]*pressure[i];
		m00+=pressure[i];
	}//end for
	xav/=m00;
	yav/=m00;
	
	//compute the necessary parameter
	for(i=0;i<length;i++){
		//compute xmax,ymax,xmin,ymin
		if(x[i]>xmax)
			xmax=x[i];
		if(x[i]<xmin)
			xmin=x[i];
		if(y[i]>ymax)
			ymax=y[i];
		if(y[i]<ymin)
			ymin=y[i];
			
		//add u02,u20......
		u02+=(y[i]-yav)*(y[i]-yav)*pressure[i];
		u20+=(x[i]-xav)*(x[i]-xav)*pressure[i];
		u11+=(x[i]-xav)*(y[i]-yav)*pressure[i];
		
		u30=(x[i]-xav)*(x[i]-xav)*(x[i]-xav)*pressure[i];
		if(u30>0)
			u30a+=u30;
		else
			u30s-=u30;
			
		u03=(y[i]-yav)*(y[i]-yav)*(y[i]-yav)*pressure[i];
		if(u03>0)
			u03a+=u03;
		else
			u03s-=u03;
			
		u12=(x[i]-xav)*(y[i]-yav)*(y[i]-yav)*pressure[i];
		if(u12>0)
			u12a+=u12;
		else
			u12s-=u12;
			
		u21=(x[i]-xav)*(x[i]-xav)*(y[i]-yav)*pressure[i];
		if(u21>0)
			u21a+=u21;
		else
			u21s-=u21;
	}//end for
	
	theta=atan((u02-u20+sqrt((u20-u02)*(u20-u02)+4*u11*u11))/(2*u11));
	lm1=((u20+u02)+sqrt((u20-u02)*(u20-u02)+4*u11*u11))/2;
	lm1=((u20+u02)-sqrt((u20-u02)*(u20-u02)+4*u11*u11))/2;
	
	size=sqrt((xmax-xmin)*(ymax-ymin));
	fg1=theta*2/pi;//orientation
	fg2=(lm1-lm2)/(lm1+lm2);//inertial ratio
	fg3=((u20-u02)/(u20+u02)+1)/2;//aspect ration
	fg4=sqrt((u02+u20)/m00)*2/size;//spreadness
	
	fg5=((u30a-u30s)/(u30a+u30s)+1)/2;	//horizantal skewness
	fg6=((u03a-u03s)/(u03a+u03s)+1)/2;	//vertical skewness
	fg7=((u21a-u21s)/(u21a+u21s)+1)/2;  //banlance of horizontal extension
	fg8=((u12a-u12s)/(u12a+u12s)+1)/2;	//banlance of vertical extention
	
	feaguretemp->f1=fg1;
	feaguretemp->f2=fg2;
	feaguretemp->f3=fg3;
	feaguretemp->f4=fg4;
	feaguretemp->f5=fg5;
	feaguretemp->f6=fg6;
	feaguretemp->f7=fg7;
	feaguretemp->f8=fg8;
}//end feagure compute ex
	
double feagure_distance(PFEAGURE_MV feagure1,PFEAGURE_MV feagure2)
{
	double dist=0.0;
	double rx;
	dist+=fabs(feagure1->f3-feagure2->f3);
	dist+=fabs(feagure1->f4-feagure2->f4);
	dist+=fabs(feagure1->f5-feagure2->f5);
	dist+=fabs(feagure1->f6-feagure2->f6);
	dist+=fabs(feagure1->f7-feagure2->f7);
	dist+=fabs(feagure1->f8-feagure2->f8);
	
	rx=fabs(feagure1->f1-feagure2->f1);
	if(rx>1)
		rx=2-rx;
	
	dist+=rx*(feagure1->f2+feagure2->f2);
	
	return dist;
}
	