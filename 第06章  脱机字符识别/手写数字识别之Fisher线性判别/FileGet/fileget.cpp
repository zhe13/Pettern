#include "stdio.h"
#include "stdlib.h"

void main(void)
{
	FILE *fpsrc;
	FILE *fpdst;
	char ch1[2048];

	double db;
	int n, i;
	//读取train中的数据，分别保存为数据和结果两个文件
	fpsrc = fopen("D:\\USPS\\USPStrainingdata.mat", "rb");
	if(fpsrc == NULL)
		return;
	fseek(fpsrc, 6144L, 0);
	
	//Open fpdst
	fpdst = fopen("D:\\USPS\\trainData.bina", "wb+");
	if(fpdst == NULL)
		return;
	for(i=0; i<7291; i++)
	{
		fread(ch1, 1, 2048, fpsrc);
		fwrite(ch1, 1, 2048, fpdst);
	}
	fclose(fpdst);

	fpdst = fopen("D:\\USPS\\trainDataResult.bina", "wb+");
	if(fpdst == NULL)
		return;
	for(i=0; i<72910; i++)
	{
		fread(&db, sizeof(double), 1, fpsrc);
		n = (int)db;
		fwrite(&n, sizeof(int), 1, fpdst);
	}
	fclose(fpdst);
	fclose(fpsrc);

	//以同样的方式处理test中的数据
	fpsrc = fopen("D:\\USPS\\USPStestingdata.mat", "rb");
	if(fpsrc == NULL)
		return;
	fseek(fpsrc, 6144L, 0);
	
	//Open fpdst
	fpdst = fopen("D:\\USPS\\testData.bina", "wb+");
	if(fpdst == NULL)
		return;
	for(i=0; i<2007; i++)
	{
		fread(ch1, 1, 2048, fpsrc);
		fwrite(ch1, 1, 2048, fpdst);
	}
	fclose(fpdst);

	fpdst = fopen("D:\\USPS\\testDataResult.bina", "wb+");
	if(fpdst == NULL)
		return;
	for(i=0; i<20070; i++)
	{
		fread(&db, sizeof(double), 1, fpsrc);
		n = (int)db;
		fwrite(&n, sizeof(int), 1, fpdst);
	}
	fclose(fpdst);
	fclose(fpsrc);
}
