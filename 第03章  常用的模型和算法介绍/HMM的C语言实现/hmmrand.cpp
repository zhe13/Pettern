/*
**	File:	hmmrand.cpp
**	功能：随机数发生器，这样使得其余部分的代码称为平台无关的。
*/

#include "StdAfx.h"
#include <stdlib.h>
#include <math.h>

/*
** 得到一个随机数种子，可以更具自己的情况修改该函数
*/
int  hmmgetseed(void) 
{
	return (17*rand());
}

/* 
** 设置随机数种子
*/
void hmmsetseed(int seed) 
{
	srand(seed);
}

/*
**  得到0－1之间的一个双精度随机数
*/

double hmmgetrand(void)
{
	return (double) rand()/RAND_MAX;
}

