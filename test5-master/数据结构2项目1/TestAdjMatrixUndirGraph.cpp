#include "Assistance.h"					// 辅助软件包
#include "AdjMatrixUndirGraph.h"

// 邻接矩阵无向图

int main(void)
{
	clock_t startTime, endTime;
	double duration;
    try									// 用try封装可能出现异常的代码
	{
		char vexs[] = {'A', 'B', 'C', 'D', 'E','r','f','s','h','w'};
		/*int m[5][5] = {
			{0, DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY, 6},
			{9, 0, 3, DEFAULT_INFINITY, DEFAULT_INFINITY},
			{2, DEFAULT_INFINITY, 0, 5, DEFAULT_INFINITY},
			{DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY, 0, 1},
			{DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY, 0},
		};*/
		/*int m[6][6] = {
			{DEFAULT_INFINITY,5, 7,DEFAULT_INFINITY, DEFAULT_INFINITY},
			{DEFAULT_INFINITY, DEFAULT_INFINITY,4,DEFAULT_INFINITY,DEFAULT_INFINITY,DEFAULT_INFINITY},
			{8, DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY,9},
			{DEFAULT_INFINITY, DEFAULT_INFINITY,5,DEFAULT_INFINITY, DEFAULT_INFINITY, 6},
			{DEFAULT_INFINITY, DEFAULT_INFINITY,5, DEFAULT_INFINITY, DEFAULT_INFINITY},
			{3,DEFAULT_INFINITY, DEFAULT_INFINITY, DEFAULT_INFINITY,1, DEFAULT_INFINITY},
		};*/
		 int m[10][10];
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				m[i][j] = rand()%10;
			}
			m[i][i] = 0;
		} 
		char c = 'a', e, e1, e2;
		int n = 10, v, v1, v2;
		int w;                                        //存放权值
		AdjMatrixUndirGraph<char> g(vexs, n, 70);

		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++)
				if (m[u][v] != 0 && m[u][v] != DEFAULT_INFINITY) g.InsertArc(u, v, m[u][v]);

	
	    while (c != '0')	{
            cout << endl << "1. 图清空.";
            cout << endl << "2. 显示图.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
			cout << endl << "9. 求权值";
			cout << endl << "A. 有无环";
			cout << endl << "B. 求次短路径长度";
			cout << endl << "C.求任意路径";
		    cout << endl << "0. 退出";
		    cout << endl << "选择功能(0~9):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
			        g.Clear();
				    break;
			    case '2':
                    if (g.IsEmpty())
                        cout << "该图为空。" << endl;
                    else 
			            g.Display();
				    break;
			    case '3':
			        cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
			        cin >> v;
		            g.GetElem(v, e);
		            cout << "序号为" << v << "的顶点为" << e;
			        break;
			    case '4':
			        cout << endl << "输入顶点序号（图的顶点序号从0开始）:";
			        cin >> v;
			        cout << endl << "输入" << v <<"号顶点的值:";
			        cin >> e;
		            g.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "输入被删除顶点的值:";
			        cin >> e;
		            g.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "输入插入顶点的值:";
			        cin >> e;
		            g.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "输入与被删除边关联的两个顶点值:";
			        cin >> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "输入与插入边关联的两个顶点值:";
			        cin >> e1 >> e2;
					cout << endl << "输入该边的权值:";
					cin >> w;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.InsertArc(v1, v2, w);
			        break;
				case '9':
					cout << endl << "输入两个顶点值:";
					cin >> e1 >> e2;
					v1 = g.GetOrder(e1);
					v2 = g.GetOrder(e2);
					cout<<g.GetWeight(v1, v2);
					break;
				case 'A':
					//git config --global http.proxy http ://127.0.0.1:19180
					//git config --global https.proxy http ://127.0.0.1:19180
					startTime = clock();
					for (int i = 0; i < 100; i++)
					cout<<g.hasCycle();
					endTime = clock();
					cout << setw(10) << (double)(endTime - startTime) / CLOCKS_PER_SEC << endl;
					startTime = clock();
					for (int i = 0; i < 100; i++)
					cout << g.hasCycleViolent();
					endTime = clock();
					cout << setw(10) << (double)(endTime - startTime) / CLOCKS_PER_SEC <<  endl;
					break;
				case 'B':
					cout << endl << "输入两个顶点值:";
					cin >> e1 >> e2;
					g.SecShortestPath(e1, e2);
				case 'C':
					cout << endl << "输入两个顶点值:";
					cin >> e1 >> e2;
					g.superpath(e1, e2);
       	      }
         }
	}
	catch (Error err)					// 捕捉并处理异常
	{
		err.Show();						// 显示异常信息
	}

	system("PAUSE");					// 调用库函数system()
	return 0;							// 返回值0, 返回操作系统
}

