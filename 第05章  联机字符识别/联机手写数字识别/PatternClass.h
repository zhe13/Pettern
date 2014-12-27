//模式识别类，实现了链码的存储，识别等
//清华大学自动化系98级  闾海荣
#include<stdio.h>

class PatternClass{
private:
	//私有变量
	int xMax,yMax;//数组的实际维数
	int realValue;//该数组表示的实际值
	int M[32][32];//存储数组

private:
	//私有函数
	int Linknize(void);
	int Recognize(void);

public:
	PatternClass();
	void SetXY(int x,int y){xMax=x;yMax=y;}
	void SetValue(int value){realValue=value;}
	void GetValue(int &value){value=realValue;}
	void GetXY(int &x,int &y){x=xMax;y=yMax;}
	void SetM(int data[32][32]);
};


