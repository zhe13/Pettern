<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title></title>
</head>
<body>
<pre>/*******************************************************************/
/*	wirecoge.cpp&nbsp;笔迹鉴别源文件
/*	笔迹鉴别程序
/*	功能:根据人手写特定字的压力曲线和位置曲线识别写字人
/*	作者:闾海荣	高秋彬
/*	单位:清华大学自动化系自81班
/*	时间:2001年8月29日
/*******************************************************************/

#include&quot;wirecoge.h&quot;

/*dtw()
x=[0&nbsp;1.25&nbsp;3&nbsp;4&nbsp;5&nbsp;6.5&nbsp;7.5&nbsp;8.3&nbsp;8.9&nbsp;9.3&nbsp;9.8&nbsp;10&nbsp;10
9.9&nbsp;9.5&nbsp;8.75&nbsp;7.8&nbsp;7.5&nbsp;3.5&nbsp;2.5&nbsp;1.0&nbsp;0.2&nbsp;0&nbsp;0.3&nbsp;2.0&nbsp;3.0&nbsp;5.5
7&nbsp;8&nbsp;9&nbsp;9.5&nbsp;9.4&nbsp;9&nbsp;7&nbsp;4&nbsp;2&nbsp;1&nbsp;0];
y=[0&nbsp;2&nbsp;4.6&nbsp;6&nbsp;7.4&nbsp;8.6&nbsp;9.6&nbsp;10&nbsp;9.6&nbsp;9&nbsp;7.6&nbsp;6&nbsp;3.8&nbsp;2&nbsp;0&nbsp;0&nbsp;0&nbsp;0.4
2&nbsp;5&nbsp;9&nbsp;10&nbsp;7&nbsp;3&nbsp;1&nbsp;1&nbsp;0];
*/

float&nbsp;wirecoge::DTWCompute(float&nbsp;A[],int&nbsp;I,float&nbsp;B[],int&nbsp;J)
{
	int&nbsp;W=0;
	int&nbsp;i,j;
	int&nbsp;pathsign=1;	/*路径标志*/
	float&nbsp;notcomputed=-1.0;	/*还没有计算的标志*/
	float&nbsp;dist,m;
	int&nbsp;istart,imax;
	int&nbsp;r=AbsInt(I-J)+10;
	for(i=0;i&lt;I;i++){
		for(j=0;j&lt;J;j++){
			DTWDistance[i][j]=notcomputed;
			DTWPath[i][j]=0;
		}
	}

	for(j=1;j&lt;J;j++){
		istart=j-r+2;
		if(j&lt;r)
			istart=1;
		imax=r+j-1;
		if(imax&gt;=I)
			imax=I-1;
		for(i=istart;i&lt;=imax;i++)
			DTWDistance[i][j]=0;
	}

	DTWDistance[0][0]=AbsFloat(A[0]-B[0]);
	for(i=1;i&lt;r;i++)
		DTWDistance[i][0]=DTWDistance[i-1][0]+AbsFloat(A[i]-B[0]);
	for(j=1;j&lt;r;j++)
		DTWDistance[0][j]=DTWDistance[0][j-1]+AbsFloat(A[0]-B[j]);

	for(j=1;j&lt;J;j++){
		istart=j-r+1;
		if(j&lt;r)
			istart=1;
		imax=r+j-1;
		if(imax&gt;=I)
			imax=I-1;
		for(i=istart;i&lt;=imax;i++){
			if(DTWDistance[i][j-1]==notcomputed)
				DTWDistance[i][j]=MinFloat(DTWDistance[i-1][j]+AbsFloat(A[i]-B[j]),
									DTWDistance[i-1][j-1]+2*AbsFloat(A[i]-B[j]));
			else&nbsp;if(DTWDistance[i-1][j]==notcomputed)
				DTWDistance[i][j]=MinFloat(DTWDistance[i-1][j-1]+2*AbsFloat(A[i]-B[i]),
									DTWDistance[i][j-1]+AbsFloat(A[i]-B[i]));
			else
				DTWDistance[i][j]=MinFloat(MinFloat(DTWDistance[i-1][j]+AbsFloat(A[i]-B[j]),
									DTWDistance[i-1][j-1]+2*AbsFloat(A[i]-B[j])),
										DTWDistance[i][j-1]+AbsFloat(A[i]-B[j]));
			if(DTWDistance[i][j]==DTWDistance[i-1][j-1]+2*AbsFloat(A[i]-B[j]))
				W+=2;
			else
				W+=1;
		}
	}

	i=I-1;
	j=J-1;
	while(j&gt;=1){
		m=MinFloat(MinFloat(DTWDistance[i-1][j],DTWDistance[i-1][j-1]),DTWDistance[i][
j-1]);
		if(m==DTWDistance[i-1][j]){
			DTWPath[i-1][j]=pathsign;
			i--;
		}
		else&nbsp;if(m==DTWDistance[i-1][j-1]){
			DTWPath[i-1][j-1]=pathsign;
			i--;
			j--;
		}
		else{
			DTWPath[i][j-1]=pathsign;
			j--;
		}
	}
	
	dist=DTWDistance[I-1][J-1]/W;
	return&nbsp;dist;
}

float&nbsp;wirecoge::MinFloat(float&nbsp;a,float&nbsp;b)
{
	if(a&lt;=b)
		return&nbsp;a;
	else&nbsp;
		return&nbsp;b;
}

float&nbsp;wirecoge::AbsFloat(float&nbsp;a)
{
	if(a&lt;0)
		return&nbsp;-a;
	else
		return&nbsp;a;
}

int&nbsp;wirecoge::AbsInt(int&nbsp;a)
{
	if(a&lt;0)
		return&nbsp;-a;
	else&nbsp;
		return&nbsp;a;
}
</pre>
</body>
</html>