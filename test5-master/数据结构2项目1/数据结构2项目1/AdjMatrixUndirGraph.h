#include "Assistance.h"	
#ifndef __ADJ_MATRIX_UNDIR_GRAPH_H__
#define __ADJ_MATRIX_UNDIR_GRAPH_H__
// 带权非负网络的邻接矩阵类
template <class ElemType>
class AdjMatrixUndirGraph 
{
protected:
// 邻接矩阵的数据成员:
	int vexNum, vexMaxNum, arcNum;			// 顶点数目、允许的顶点最大数目和边数
	int **arcs;							    // 存放边信息邻接矩阵
	ElemType *vertexes;						// 存放顶点信息的数组 
	mutable Status *tag;					// 标志数组

public:
// 邻接矩阵类型的方法声明:
	AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE);	
		// 以数组es[]为顶点,顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的有向图
	AdjMatrixUndirGraph(int vertexMaxNum = DEFAULT_SIZE);	
		// 构造允许的顶点最大数目为vertexMaxNum,边数为0的有向图
	~AdjMatrixUndirGraph();					// 析构函数
	void Clear();			              // 清空图			 
	bool IsEmpty();                       // 判断有向图是否为空 
	int GetOrder(ElemType &d) const;           // 求顶点的序号	
	Status GetElem(int v, ElemType &d) const;// 求顶点的元素值	
	Status SetElem(int v, const ElemType &d);// 设置顶点的元素值
	int GetVexNum() const;					// 返回顶点个数			 
	int GetArcNum() const;					// 返回边数			 
	int FirstAdjVex(int v) const;		 // 返回顶点v的第一个邻接点	(包含出度入度）		 
	int NextAdjVex(int v1, int v2) const;		 // 返回顶点v1的相对于v2的下一个邻接点（包含出度入读）			 
	void InsertVex(const ElemType &d);			 // 插入元素值为d的顶点		 
	void InsertArc(int v1, int v2,int weight);			     // 插入顶点为v1和v2的边（v1为入度，v2为出度）		 
	void DeleteVex(const ElemType &d);			 // 删除元素值为d的顶点			 
	void DeleteArc(int v1, int v2);			     // 删除顶点为v1和v2的边 包括出度入度			 
	Status GetTag(int v) const;			         // 返回顶点v的标志		 
	void SetTag(int v, Status val) const;	   // 设置顶点v的标志为val

    int GetWeight(int v1, int v2) const;//求有向边的权值
	int CountOutDegree(int v) const;    //统计顶点 v的出度；
	int CountInDegree(int v) const;     //统计顶点 v的入度；
	int SecShortestPath(int v1, int v2);    //求两个顶点之间的次短路径；
	int hasCycle();                 //判断有向图是否存在环。

	AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g);	// 复制构造函数
	AdjMatrixUndirGraph<ElemType> &operator =(const AdjMatrixUndirGraph<ElemType> &g); 
		// 赋值语句重载
  void Display();	                         // 显示邻接矩阵无向图
};

// 无向图的邻接矩阵类的实现部分
template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(ElemType es[], int vertexNum, int vertexMaxNum)
// 操作结果：构造数据元素为es[],顶点个数为vertexNum,允许的顶点最大数目为vertexMaxNum,边数为0的无向图

{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");        // 抛出异常

	if (vertexMaxNum < vertexNum)
    	throw Error("顶点数目不能大于允许的顶点最大数目!");// 抛出异常

	vexNum = vertexNum;			
	vexMaxNum = vertexMaxNum; 
	arcNum = 0;	

	vertexes = new ElemType[vexMaxNum];      // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];			       // 生成标志数组
	arcs = (int **)new int * [vexMaxNum];     // 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int [vexMaxNum];	

	for (int v = 0; v < vexNum; v++) {
		vertexes[v] = es[v];
		tag[v] = UNVISITED;
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = DEFAULT_INFINITY;
			arcs[v][v]=0;
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(int vertexMaxNum)
// 操作结果：构造允许顶点的最大数目为vertexMaxNum的有向向图
{
	if (vertexMaxNum < 0)
    	throw Error("允许的顶点最大数目不能为负!");// 抛出异常

	vexNum = 0;			
	vexMaxNum = vertexMaxNum;
	arcNum = 0;	

	vertexes = new ElemType[vexMaxNum];     // 生成生成顶点信息数组
	tag = new Status[vexMaxNum];		// 生成标志数组arcs = (int **)new int *[vexMaxNum];    // 生成邻接矩阵
	arcs = (int**)new int* [vexMaxNum];
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int[vexMaxNum];	
	
 }

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Clear()
// 操作结果：把无向图的顶点数和边数设置为0.			 
{
    vexNum = 0;
	arcNum = 0;	
}

template <class ElemType>
bool AdjMatrixUndirGraph<ElemType>::IsEmpty()
// 操作结果：如果无向图为空返回true,否则返回false.
{
	return vexNum == 0;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::~AdjMatrixUndirGraph()
// 操作结果：释放对象所占用的空间
{
	delete []vertexes;					// 释放顶点数据
	delete []tag;						    // 释放标志

	for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
		delete []arcs[v];
	delete []arcs;					    // 释放邻接矩阵
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetOrder(ElemType &d) const
// 操作结果：求顶点d的序号.顶点的序号从0开始，图中不存在顶点d时，返回-1. 
{
    for (int v = 0; v < vexNum; v++)
        if (vertexes[v] == d)
		   return v;	    // 顶点d存在,返回它的序号 
	return -1;	        // 顶点d不存在,返回-1
}	

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetElem(int v, ElemType &d) const
// 操作结果：求序号为v的顶点值, v的取值范围为0 ≤ v ＜ vexNum, v合法时函数
// 通过d取得顶点值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT
{
	if (v < 0 || v >= vexNum)
		return NOT_PRESENT;	// v范围错,返回元素不存在
	else	{
		d = vertexes[v];	  // 将顶点v的元素值赋给d
		return ENTRY_FOUND;	// 返回元素存在
	}
}	

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::SetElem(int v, const ElemType &d)
// 操作结果：设置顶点的元素值v的取值范围为0 ≤ v ＜ vexNum, v合法时函数返回
//	SUCCESS, 否则函数返回RANGE_ERROR
{
	if (v < 0 || v >= vexNum)
		return RANGE_ERROR;	// v范围错,返回位置错
	else	{
		vertexes[v] = d;		// 将顶点元素的值改为d 
		return SUCCESS;		  // 返回修改成功
	}
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetVexNum() const
// 操作结果：返回顶点个数			 
{
	return vexNum;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetArcNum() const
// 操作结果：返回边数
{
	return arcNum;
}		 

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::FirstAdjVex(int v) const
// 操作结果：返回顶点v的第1个邻接点的序号		 
{
	
	if (v < 0 || v >= vexNum)
       throw Error("v不合法!");// 抛出异常

	for (int u = 0; u < vexNum; u++)
	{
		if (arcs[v][u] != DEFAULT_INFINITY&&u!=v) return u;
		else if (arcs[u][v] != DEFAULT_INFINITY && u != v) return u;
	}
	
	return -1;					// 返回-1表示无邻接点
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::NextAdjVex(int v1, int v2) const
// 操作结果：返回顶点v1的相对于v2的下一个邻接点			 
{
	if (v1 < 0 || v1 >= vexNum)
       throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
       throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2) throw
       Error("v1不能等于v2!");		// 抛出异常

	for (int u = v2 + 1; u < vexNum; u++) {

		if (arcs[u][v1] != DEFAULT_INFINITY && u != v1) return u;
		else if (arcs[v1][u] != DEFAULT_INFINITY && u != v1) return u;
	}

	return -1;						// 返回-1表示无下一个邻接点
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertVex(const ElemType &d)
// 操作结果：插入顶点d			 
{
	if (vexNum == vexMaxNum)
    throw Error("图的顶点数不能超过允许的最大数!");	// 抛出异常

	vertexes[vexNum] = d;
	tag[vexNum] = UNVISITED;
	for (int v = 0; v <= vexNum; v++) {
		arcs[vexNum][v] = DEFAULT_INFINITY;
		arcs[v][vexNum] = DEFAULT_INFINITY;
  }
	arcs[vexNum][vexNum] = 0;
  vexNum++;
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::InsertArc(int v1, int v2,int weight)
// 操作结果：插入依附顶点v1和v2的边	（v1为入度，v2为出度）		 
{
	if (v1 < 0 || v1 >= vexNum)
    throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
    throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
    throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] == DEFAULT_INFINITY)	{	  // 原无向图中没有边(v1, v2) 
	   arcNum++;
	   arcs[v1][v2] = weight;	
    }
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteVex(const ElemType &d)
// 操作结果：删除元素为d的顶点			 
{
   int v;
   for (v = 0; v < vexNum; v++)
     if	(vertexes[v] == d)
        break;
   if (v == vexNum)
      throw Error("图中不存在要删除的顶点!");	// 抛出异常

   for (int u = 0; u < vexNum; u++)           // 删除与顶点d相关联的边 
   {
	   if (arcs[v][u] != DEFAULT_INFINITY) {
		   arcNum = arcNum - 1;
		   arcs[v][u] = DEFAULT_INFINITY;
	   }
	   if (arcs[u][v] != DEFAULT_INFINITY) {
		   arcNum = arcNum - 1;
		   arcs[u][v] = DEFAULT_INFINITY;
	   }
   }
   
   arcs[v][v] = 0;
	      
   vexNum--; 
   if (v < vexNum) {
      vertexes[v] = vertexes[vexNum];
	  tag[v] = tag[vexNum];
	  for (int u = 0; u <=vexNum; u++) 
		 arcs[v][u] = arcs[vexNum][u];
	  for (int u = 0; u <=vexNum; u++) 
         arcs[u][v] = arcs[u][vexNum];
   } 
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::DeleteArc(int v1, int v2)
// 操作结果：删除依附顶点v1和v2的边	双向删除出度和入度		 
{
	if (v1 < 0 || v1 >= vexNum)
    throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
    throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
    throw Error("v1不能等于v2!");// 抛出异常

	if (arcs[v1][v2] != DEFAULT_INFINITY) {	// 原无向图存在边(v1, v2)
		arcNum--;
		arcs[v1][v2] = DEFAULT_INFINITY;
	}
	if (arcs[v2][v1] != DEFAULT_INFINITY){
		arcNum--;
        arcs[v2][v1] = DEFAULT_INFINITY;
    } 
}

template <class ElemType>
Status AdjMatrixUndirGraph<ElemType>::GetTag(int v) const
// 操作结果：返回顶点v的标志		 
{
	if (v < 0 || v >= vexNum)
    throw Error("v不合法!");	// 抛出异常

	return tag[v];
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::SetTag(int v, Status val) const 
// 操作结果：设置顶点v的标志为val		 
{
	if (v < 0 || v >= vexNum)
    throw Error("v不合法!");	// 抛出异常

	tag[v] = val;
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType>::AdjMatrixUndirGraph(const AdjMatrixUndirGraph<ElemType> &g)
// 操作结果：由有向图的邻接矩阵g构造新有向图的邻接矩阵g——复制构造函数
{
	vexNum = g.vexNum;	
	vexMaxNum = g.vexMaxNum;
	arcNum = g.arcNum;	
	
	vertexes = new ElemType[vexMaxNum];		// 生成顶点数据数组
	tag = new Status[vexMaxNum];			// 生成标志数组
	arcs = (int **)new int *[vexMaxNum];	// 生成邻接矩阵
	for (int v = 0; v < vexMaxNum; v++) 
		arcs[v] = new int[vexMaxNum];	

	for (int v = 0; v < vexNum; v++)	{	// 复制顶点数据数组
		vertexes[v] = g.vertexes[v];
		tag[v] = g.tag[v];
		for (int u = 0; u < vexNum; u++)
			arcs[v][u] = g.arcs[v][u];
	}
}

template <class ElemType>
AdjMatrixUndirGraph<ElemType> &AdjMatrixUndirGraph<ElemType>::operator =(const AdjMatrixUndirGraph<ElemType> &g)
// 操作结果：将无向图的邻接矩阵g赋值给当前无向图的邻接矩阵——赋值语句重载
{
	if (&g != this)	{
	  delete []vertexes;				// 释放顶点数据
	  delete []tag;						  // 释放标志

	  for (int v = 0; v < vexMaxNum; v++)	// 释放邻接矩阵的行
       delete []arcs[v];
    delete []arcs;					  // 释放邻接矩阵
	  vexNum = g.vexNum;	
    vexMaxNum = g.vexMaxNum;
	  arcNum = g.arcNum;	
	
	  vertexes = new ElemType[vexMaxNum];	 // 生成顶点数据数组
	  tag = new Status[vexMaxNum];			   // 生成标志数组
	  arcs = (int **)new int *[vexMaxNum]; // 生成邻接矩阵
	  for (int v = 0; v < vexMaxNum; v++) 
		  arcs[v] = new int[vexMaxNum];	

	  for (int v = 0; v < vexNum; v++)	{	 // 复制顶点数据数组
		  vertexes[v] = g.vertexes[v];
		  tag[v] = g.tag[v];
		  for (int u = 0; u < vexNum; u++)
		    arcs[v][u] = g.arcs[v][u];
	  }
	}
	return *this;
}

template <class ElemType>
void AdjMatrixUndirGraph<ElemType>::Display()
// 操作结果: 显示邻接矩阵有向图
{
              
	for (int v = 0; v < vexNum; v++)
 		cout << "\t" << vertexes[v];
	cout << endl;

	for (int v = 0; v < vexNum; v++)	{
		cout << vertexes[v];
		for (int u = 0; u < vexNum; u++)
 			cout << "\t" << arcs[v][u];
		cout << endl;
	}
}


template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::GetWeight(int v1, int v2) const
// 操作结果：求v1与v2顶点之间的有向边的权值, v1、v2的取值范围为[0,vexNum), 二者合法时
// 若v1，v2之间有边，函数通过w取得权值，并返回ENTRY_FOUND；否则函数返回NOT_PRESENT；
//若不合法返回NOT_PRESENT
{
	if (v1 < 0 || v1 >= vexNum)
		throw Error("v1不合法!");	// 抛出异常
	if (v2 < 0 || v2 >= vexNum)
		throw Error("v2不合法!");	// 抛出异常
	if (v1 == v2)
		throw Error("v1不能等于v2!");// 抛出异常
	if (arcs[v1][v2] == DEFAULT_INFINITY) 
		throw Error("v1、v2不相邻!");// 抛出异常	
	else 
		return arcs[v1][v2];	    // 返回权值
	
	
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::CountOutDegree(int v) const
// 统计顶点 v的出度
{
	int OD = 0;
	for (int u = 0; u < vexNum; u++) {
		if (arcs[v][u] != 0 || arcs[v][u] != DEFAULT_INFINITY)
			OD++;
	}
	return OD;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::CountInDegree(int v) const
//统计顶点 v的入度
{
	int ID = 0;
	for (int u = 0; u < vexNum; u++)
		if (arcs[u][v] != 0 || arcs[u][v] != DEFAULT_INFINITY)
			ID++;

	return ID;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::SecShortestPath(int v1, int v2)
//暴力求两个顶点之间的次短路径长度
{
	int temp = 0;                       //暂存矩阵元素
	int l = 0;                          //路径长度，同时是矩阵乘方数
	int flag = 0;                       //记录次短路径
	int** a;                          //用于存放领接矩阵的n次方的矩阵 
	a = (int**) new int* [vexNum];
	for (int v = 0; v < vexNum; v++)
		a[v] = new int [vexNum];
	for (int i = 0; i < vexNum; i++)
		for (int j = 0; j < vexNum; j++)
			a[i][j] = 0;                   //初始化
	int** b;                          //用于存放领接矩阵的n次方的矩阵 
	b = (int**) new int* [vexNum];
	for (int v = 0; v < vexNum; v++)
		b[v] = new int [vexNum];

	for (int i = 0; i < vexNum; i++)
		for (int j = 0; j < vexNum; j++)
		{
			if (arcs[i][j] != 0 && arcs[i][j] != DEFAULT_INFINITY)
			{
				    arcs[i][j] = 1;
					b[i][j] = 1;
			}
			else
			{
				     arcs[i][j] = 0;
				     b[i][j] = 0;
			}
		}
	for (int i = 0; i < vexNum; i++)
	{
		for (int j = 0; j < vexNum; j++)
			printf("%d ", arcs[i][j]);
		printf("\n");
	}
	printf("\n");

	for (l = 1; l <= vexNum; l++)
	{
		if (b[v1][v2] != 0)
			flag = 1;
		if (flag)
			break;
		for (int i = 0; i < vexNum; i++)
			for (int j = 0; j < vexNum; j++)
				for (int k = 0; k < vexNum; k++)
					a[i][j] += arcs[i][k] * b[k][j];	

		for (int i = 0; i < vexNum; i++)
			for (int j = 0; j < vexNum; j++)
				b[i][j] = a[i][j];

		for (int i = 0; i < vexNum; i++)
		{
			for (int j = 0; j < vexNum; j++)
				printf("%d ", b[i][j]);
			printf("\n");
		}
		printf("\n");

	}
	if (flag)
		return l;
	else
		return 0;
}

template <class ElemType>
int AdjMatrixUndirGraph<ElemType>::hasCycle()
//暴力判断有向图是否存在环
{

	int l = 0;                          //路径长度，同时是矩阵乘方数
	int flag = 0;
	int** a;                          //用于存放领接矩阵的n次方的矩阵 
	a = (int**) new int* [vexNum];
	for (int v = 0; v < vexNum; v++)
		a[v] = new int [vexNum];
	for (int i = 0; i < vexNum; i++)
		for (int j = 0; j < vexNum; j++)
			a[i][j] = 0;                   //初始化

	int** b; //用于存放领接矩阵的n次方的矩阵
	b = (int**)new int* [vexNum];
	for (int v = 0; v < vexNum; v++)
		b[v] = new int [vexNum];

	for (int i = 0; i < vexNum; i++)
		for (int j = 0; j < vexNum; j++)
		{
			if (arcs[i][j] != 0 && arcs[i][j] != DEFAULT_INFINITY)
			{
				arcs[i][j] = 1;
				b[i][j] = 1;
			}
			else
			{
				arcs[i][j] = 0;
				b[i][j] = 0;
			}
		}
	for (l = 1; l <= vexNum; l++)
	{
		for (int i = 0; i < vexNum; i++)
			for (int j = 0; j < vexNum; j++)
				for (int k = 0; k < vexNum; k++)
					a[i][j] += arcs[i][k] * b[k][j];
		for (int i = 0; i < vexNum; i++)
			for (int j = 0; j < vexNum; j++)
				b[i][j] = a[i][j];
		for (int k = 0; k < vexNum; k++)
		{
			if (a[k][k] != 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag)
			break;
	}
  if (flag)
	return 1;
  else
	return 0;
}

#endif
