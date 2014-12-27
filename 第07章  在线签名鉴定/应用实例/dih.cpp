/////////////////////////////////////////////////////////////////////////////////
//dih.c

#include"dih.h"

//////////////////////////////////////////////////////////////////////////////////
//计算方向，x[]，y[]，dire[]分别是x,y坐标，方向数组，length是数组长度
void dih_compute_direction(double x[],double y[],int dire[],int length)
{
	int i;
	double xdist;
	double ydist;
	double dist;
	double theta;
	//dire[0]=0;
	for(i=0;i<length-1;i++){
		xdist=x[i+1]-x[i];
		ydist=y[i+1]-x[i];
		double dist=sqrt(xdist*xdist+ydist*ydist);
		if(dist>DUANBILENGTH){
			if(i==0)
				dire[i]=0;
			else
				dire[i]=dire[i-1];
		}//end if
		
		else{
			if(xdist==0)
			dire[i]=2;
		else{
			theta=ydist/xdist;
			if((theta>=(-0.414))&&(theta<0.414))
				dire[i]=0;
			else if((theta>=0.414)&&(theta<2.415))
				dire[i]=1;
			else if((theta>=2.415)||(theta<(-2.415)))
				dire[i]=2;
			else if((theta<(-0.414))&&(theta>=(-2.415)))
				dire[i]=3;
			else
				dire[i]=3;
		}//end else
		}
	}//end for
	
	dire[length-1]=dire[length-2];
}

//////////////////////////////////////////////////////////////////////////////////
//计算频率
//dire[]是方向数组，temp保存结果
void dih_compute_frequency(int dire[],int length,PDIHFQ temp)
{
	int fr0=0,fr1=0,fr2=0,fr3=0;
	int i;
	
	//计算频率
	for(i=0;i<length;i++){
		if(dire[i]==0)
			fr0++;
		else if(dire[i]==1)
			fr1++;
		else if(dire[i]==2)
			fr2++;
		else
			fr3++;
	}//end for
	
	temp->f0=(double)fr0/((double)length);
	temp->f1=(double)fr1/((double)length);
	temp->f2=(double)fr2/((double)length);
	temp->f3=(double)fr3/((double)length);
}
	
////////////////////////////////////////////////////////////////////////////////////
//计算频率，加上距离修正
void dih_compute_frequency_dist(int dire[],double x[],double y[],int length,PDIHFQ temp)
{
	double totaldist,xdist,ydist,dist;
	double fr0=0.0,fr1=0.0,fr2=0.0,fr3=0.0;
	int i;
	totaldist=0.0;		
		
	for(i=0;i<length-1;i++){
		xdist=x[i+1]-x[i];
		ydist=y[i+1]-y[i];
		dist=sqrt(xdist*xdist+ydist*ydist);
		
		if(dist>DUANBILENGTH){
			if(dire[i]==0)
				fr0+=1;
			else if(dire[i]==1)
				fr1+=1;
			else if(dire[i]==2)
				fr2+=1;
			else
				fr3+=1;
			totaldist+=1;//总距离增加1
		}//endif
		else{
			if(dire[i]==0)
				fr0+=dist;
			else if(dire[i]==1)
				fr1+=dist;
			else if(dire[i]==2)
				fr2+=dist;
			else 
				fr3+=dist;
			totaldist+=dist;
		}//end else
	}//end for
	
	//最后一个点
	if(dire[i]==0)
		fr0+=1;
	else if(dire[i]==1)
		fr1+=1;
	else if(dire[i]==2)
		fr2+=1;
	else
		fr3+=1;
	totaldist+=1;
	
	temp->f0=fr0/totaldist;
	temp->f1=fr1/totaldist;
	temp->f2=fr2/totaldist;
	temp->f3=fr3/totaldist;
}//end 


/////////////////////////////////////////////////////////////////////////////////////////
//计算频率，加上压力修正
void dih_compute_frequency_pressure(int dire[],double pressure[],int length,PDIHFQ temp)
{
	double fr0=0,fr1=0,fr2=0,fr3=0;
	double totalpressure=0;
	int i;
	
	//计算频率
	for(i=0;i<length;i++){
		if(dire[i]==0)
			fr0+=pressure[i];
		else if(dire[i]==1)
			fr1+=pressure[i];
		else if(dire[i]==2)
			fr2+=pressure[i];
		else
			fr3+=pressure[i];
		totalpressure+=pressure[i];
	}//end for
	
	temp->f0=fr0/totalpressure;
	temp->f1=fr1/totalpressure;
	temp->f2=fr2/totalpressure;
	temp->f3=fr3/totalpressure;
}
/////////////////////////////////////////////////////////////////////////////////////////
//同时加上压力和频率修正
void dih_compute_frequency_dp(int dire[],double pressure[],double x[],double y[],int length,PDIHFQ temp)
{
	double totaldist,xdist,ydist,dist;
	double fr0=0.0,fr1=0.0,fr2=0.0,fr3=0.0;
	int i;
	totaldist=0.0;		
		
	for(i=0;i<length-1;i++){
		xdist=x[i+1]-x[i];
		ydist=y[i+1]-y[i];
		dist=sqrt(xdist*xdist+ydist*ydist);
		
		if(dist>DUANBILENGTH){
			if(dire[i]==0)
				fr0+=pressure[i];
			else if(dire[i]==1)
				fr1+=pressure[i];
			else if(dire[i]==2)
				fr2+=pressure[i];
			else
				fr3+=pressure[i];
			totaldist+=pressure[i];//总距离增加1
		}//endif
		else{
			dist=dist*pressure[i];
			if(dire[i]==0)
				fr0+=dist;
			else if(dire[i]==1)
				fr1+=dist;
			else if(dire[i]==2)
				fr2+=dist;
			else 
				fr3+=dist;
			totaldist+=dist;
		}//end else
	}//end for
	
	//最后一个点
	if(dire[i]==0)
		fr0+=pressure[i];
	else if(dire[i]==1)
		fr1+=pressure[i];
	else if(dire[i]==2)
		fr2+=pressure[i];
	else
		fr3+=pressure[i];
	totaldist+=pressure[i];
	
	temp->f0=fr0/totaldist;
	temp->f1=fr1/totaldist;
	temp->f2=fr2/totaldist;
	temp->f3=fr3/totaldist;
}//end 

//////////////////////////////////////////////////////////////////////////////////////////
//计算距离
double dih_dist_compute(PDIHFQ fq1,PDIHFQ fq2)
{
	double dist=0;
	dist+=((fq1->f0)-(fq2->f0))*((fq1->f0)-(fq2->f0));
	dist+=((fq1->f1)-(fq2->f1))*((fq1->f1)-(fq2->f1));
	dist+=((fq1->f2)-(fq2->f2))*((fq1->f2)-(fq2->f2));
	dist+=((fq1->f3)-(fq2->f3))*((fq1->f3)-(fq2->f3));
	
	return dist;
}
	
	
		
			
