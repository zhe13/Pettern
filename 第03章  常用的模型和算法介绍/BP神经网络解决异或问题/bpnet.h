/* ========================================== *
 * Filename:	bpnet.h                       *
 * Description:								  *
 * 一个微型神经网络，使用BP来调整权值         *
 * ========================================== */

#include <math.h>
#include <stdlib.h>
#include <time.h>

#define BP_LEARNING	(float)(0.5)	// 学习系数

class CBPNet 
{
	public:
		CBPNet();
		~CBPNet() {};

		float Train(float, float, float);
		float Run(float, float);

	private:
		float m_fWeights[3][3];		// 3个神经元

		float Sigmoid(float);		// S形函数
};

CBPNet::CBPNet() 
{
	srand((unsigned)(time(NULL)));
	
	for (int i=0;i<3;i++) 
	{
		for (int j=0;j<3;j++) 
		{
			// 由于一些原因，微软提供的rand()函数产生的随机数是
			// 整数，所以需要将之做适当的变换，变到-1～1之间
			m_fWeights[i][j] = (float)(rand())/(32767/2) - 1;
		}
	}
}

//训练网络
float CBPNet::Train(float i1, float i2, float d) 
{
	// 变量
	float net1, net2, i3, i4, out;
	
	// 计算隐含层的神经元值
	net1 = 1 * m_fWeights[0][0] + i1 * m_fWeights[1][0] +
		  i2 * m_fWeights[2][0];
	net2 = 1 * m_fWeights[0][1] + i1 * m_fWeights[1][1] +
		  i2 * m_fWeights[2][1];

	// 使用S函数
	i3 = Sigmoid(net1);
	i4 = Sigmoid(net2);

	// 计算输出层的值
	net1 = 1 * m_fWeights[0][2] + i3 * m_fWeights[1][2] +
	   	  i4 * m_fWeights[2][2];
	out = Sigmoid(net1);

	//计算误差，反向传播
	float deltas[3];
	
	deltas[2] = out*(1-out)*(d-out);
	deltas[1] = i4*(1-i4)*(m_fWeights[2][2])*(deltas[2]);
	deltas[0] = i3*(1-i3)*(m_fWeights[1][2])*(deltas[2]);

	// 调整权值
	float v1 = i1, v2 = i2;
	for(int i=0;i<3;i++) 
	{
		// 如果有必要，改变输出层的值
		if (i == 2) 
		{
			v1 = i3;
			v2 = i4;
		}
				
		m_fWeights[0][i] += BP_LEARNING*1*deltas[i];
		m_fWeights[1][i] += BP_LEARNING*v1*deltas[i];
		m_fWeights[2][i] += BP_LEARNING*v2*deltas[i];
	}

	return out;
}

//S函数
float CBPNet::Sigmoid(float num) 
{
	return (float)(1/(1+exp(-num)));
}

//运行网络
float CBPNet::Run(float i1, float i2) 
{
	float net1, net2, i3, i4;
	
	net1 = 1 * m_fWeights[0][0] + i1 * m_fWeights[1][0] +
		  i2 * m_fWeights[2][0];
	net2 = 1 * m_fWeights[0][1] + i1 * m_fWeights[1][1] +
		  i2 * m_fWeights[2][1];

	i3 = Sigmoid(net1);
	i4 = Sigmoid(net2);

	net1 = 1 * m_fWeights[0][2] + i3 * m_fWeights[1][2] +
	   	  i4 * m_fWeights[2][2];
	return Sigmoid(net1);
}

