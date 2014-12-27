// JiuG.h: interface for the CJiuG class.

#if !defined(AFX_JIUG_H__A836D34F_3D4D_450C_BB2A_1412429F6451__INCLUDED_)
#define AFX_JIUG_H__A836D34F_3D4D_450C_BB2A_1412429F6451__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcoll.h>//包含类CPtrList

typedef struct JiuGongState{
	int curdistance;//当前的距离，从初始节点开始
	int state[3][3];
	struct JiuGongState *prestate;//上一个节点的指针
	struct JiuGongState *nextstate;//下一个节点的指针
}JGState;//定义九宫结构

class CJiuG  
{
public:
	JGState StateInit;//初始状态
	JGState StateObj;//目标状态
	JGState StateCur;//当前状态

	CPtrList OpenList;//Open表
	CPtrList CloseList;//Close表
	CPtrList ResultList;//保存结果
	JGState *curstep;

public:
	int m_ndepth;//搜索深度
	int ComputeJO(JGState *jo);//计算状态的奇偶性
	CJiuG();
	virtual ~CJiuG();
	bool MoveLeft(JGState *src,JGState *result);//左移
	bool MoveRight(JGState *src,JGState *result);//右移
	bool MoveUp(JGState *src,JGState *result);//上移
	bool MoveDown(JGState *src,JGState *result);//下移
	bool Compare(JGState *src1,JGState *src2);//比较两个状态是否相等
	int ComputeFn(JGState *cur,JGState *dest);//估价函数的计算，我们采用了Pn
	bool Search();//用A*算法搜索最优解
	void FreeList(CPtrList *list);//释放内存
	void CopyJG(JGState *src,JGState *dest);//复制九宫
};

#endif // !defined(AFX_JIUG_H__A836D34F_3D4D_450C_BB2A_1412429F6451__INCLUDED_)
