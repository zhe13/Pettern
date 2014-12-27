<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=gb2312">
<title></title>
</head>
<body>
<pre>/*******************************************************************/
/*	wirecoge.h&nbsp;笔迹鉴别头文件
/*	笔迹鉴别程序
/*	功能:根据人手写特定字的压力曲线和位置曲线识别写字人
/*	作者:闾海荣	高秋彬
/*	单位:清华大学自动化系自81班
/*	时间:2001年8月29日
/*******************************************************************/

#define&nbsp;WIMAXTIME	2000	/*定义采样点的个数,根据实际硬件的不同*/
							/*可以加以修改*/

#define&nbsp;MAXPRESSURE	100.00	/*定义压力的最大值,为了模式匹配时用*/
#define&nbsp;XLENGTH		300		/*定义字的位置X方向的长度*/
#define&nbsp;YLENGTH		150		/*定义字的位置Y方向的长度*/
#define&nbsp;DTWRESULTNUM	300	/*定义动态时间弯折数组结果的长度*/

typedef&nbsp;struct&nbsp;point{
	int&nbsp;x;
	int&nbsp;y;
}POINT;

class&nbsp;wirecoge{
private:	/*定义私有变量*/
public:
	unsigned&nbsp;char&nbsp;DTWPath[DTWRESULTNUM][DTWRESULTNUM];	/*保存动态时间弯折路径结果*/
	float&nbsp;DTWDistance[DTWRESULTNUM][DTWRESULTNUM];	/*计算动态时间弯折距离*/
	float&nbsp;pressure[WIMAXTIME];	/*压力大小数组*/
	float&nbsp;pressure1[WIMAXTIME];	/*点1的压力数组*/
	float&nbsp;pressure2[WIMAXTIME];	/*点2的压力数组*/
	float&nbsp;pressure3[WIMAXTIME];	/*点3的压力数组*/
	POINT&nbsp;position[WIMAXTIME];	/*位置数组*/
	POINT&nbsp;dtwresult[DTWRESULTNUM];	/*存储动态时间弯折匹配结果*/
public:		
	//wirecoge();/*有待重新定义*/
	//~wirecoge();
	float&nbsp;DTWCompute(float&nbsp;A[],int&nbsp;I,float&nbsp;B[],int&nbsp;J);	/*动态时间弯折，结果保存在DT
WPath中*/
	float&nbsp;MinFloat(float&nbsp;a,float&nbsp;b);
	float&nbsp;AbsFloat(float&nbsp;a);
	int&nbsp;AbsInt(int&nbsp;a);
};

</pre>
</body>
</html>