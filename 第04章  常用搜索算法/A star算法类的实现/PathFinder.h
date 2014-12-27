//////////////////////////////////////////////////////////////////
// CPathFinder class 
//
// A* 算法接口，针对迷宫问题设计

#ifndef _PATHFINDER_H_
#define _PATHFINDER_H_

#include <memory.h>

//节点类
class _asNode {
	public:
		_asNode(int a = -1,int b = -1) : x(a), y(b), number(0), numchildren(0) 
		{
			parent = next = NULL;
			memset(children, 0, sizeof(children));
		}

		int			f,g,h;			// A*算法的估价函数值等
		int			x,y;			// 坐标
		int			numchildren;
		int			number;			// x*30+y
		_asNode		*parent;		// 父节点
		_asNode		*next;
		_asNode		*children[8];	// 8领域
};

// 堆栈
struct _asStack {
	_asNode	 *data;
	_asStack *next;
};

typedef int(*_asFunc)(int, int, void *);

//迷宫类
class CPathFinder {
	public:
		CPathFinder();
		~CPathFinder();

		bool	GeneratePath(int, int, int, int);
		void	SetValid(_asFunc sv) { udValid = sv;   }
		void	SetCost(_asFunc sc)  { udCost = sc;    }
		void	SetData(void *sd)	 { m_pCBData = sd; }
		void	SetRows(int r)		 { m_iRows = r;    }

		_asNode	*GetBestNode() { return m_pBest; }

	protected:
		int		m_iRows;			// 用来计算节点的个数
		int		m_iSX, m_iSY, m_iDX, m_iDY, m_iDNum;
		void	*m_pCBData;			// 已经经过的节点

		_asNode	*m_pOpen;			// OPEN表
		_asNode	*m_pClosed;			// CLOSE表
		_asNode *m_pBest;			// 最好的节点
		_asStack*m_pStack;			// 堆栈

		_asFunc	udCost;				// 用户定义的费用
		_asFunc udValid;			// 用户定义的有效费用

		// 一些结构操作函数
		void	AddToOpen(_asNode *);
		void	ClearNodes();
		void	CreateChildren(_asNode *);
		void	LinkChild(_asNode *, int, int);
		void	UpdateParents(_asNode *);

		// 堆栈操作函数
		void	Push(_asNode *);
		_asNode *Pop();
		
		_asNode *CheckList(_asNode *, int);
		_asNode	*GetBest();
		
		// 内联函数
		inline int Coord2Num(int x, int y) { return x * m_iRows + y; }
};

#endif
