#include "Assistance.h"					// ���������
#include "AdjMatrixUndirGraph.h"

// �ڽӾ�������ͼ

int main(void)
{
	clock_t startTime, endTime;
	double duration;
    try									// ��try��װ���ܳ����쳣�Ĵ���
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
		int w;                                        //���Ȩֵ
		AdjMatrixUndirGraph<char> g(vexs, n, 70);

		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++)
				if (m[u][v] != 0 && m[u][v] != DEFAULT_INFINITY) g.InsertArc(u, v, m[u][v]);

	
	    while (c != '0')	{
            cout << endl << "1. ͼ���.";
            cout << endl << "2. ��ʾͼ.";
            cout << endl << "3. ȡָ�������ֵ.";
            cout << endl << "4. ����ָ�������ֵ.";
            cout << endl << "5. ɾ������.";
            cout << endl << "6. ���붥��.";
            cout << endl << "7. ɾ����.";
            cout << endl << "8. �����.";
			cout << endl << "9. ��Ȩֵ";
			cout << endl << "A. ���޻�";
			cout << endl << "B. ��ζ�·������";
			cout << endl << "C.������·��";
		    cout << endl << "0. �˳�";
		    cout << endl << "ѡ����(0~9):";
		    cin >> c;
		    switch (c) 		{
			    case '1':
			        g.Clear();
				    break;
			    case '2':
                    if (g.IsEmpty())
                        cout << "��ͼΪ�ա�" << endl;
                    else 
			            g.Display();
				    break;
			    case '3':
			        cout << endl << "���붥����ţ�ͼ�Ķ�����Ŵ�0��ʼ��:";
			        cin >> v;
		            g.GetElem(v, e);
		            cout << "���Ϊ" << v << "�Ķ���Ϊ" << e;
			        break;
			    case '4':
			        cout << endl << "���붥����ţ�ͼ�Ķ�����Ŵ�0��ʼ��:";
			        cin >> v;
			        cout << endl << "����" << v <<"�Ŷ����ֵ:";
			        cin >> e;
		            g.SetElem(v, e);
			        break;
			    case '5':
			        cout << endl << "���뱻ɾ�������ֵ:";
			        cin >> e;
		            g.DeleteVex(e);
			        break;
			    case '6':
			        cout << endl << "������붥���ֵ:";
			        cin >> e;
		            g.InsertVex(e);
			        break;
			    case '7':
			        cout << endl << "�����뱻ɾ���߹�������������ֵ:";
			        cin >> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.DeleteArc(v1, v2);
			        break;
			    case '8':
			        cout << endl << "���������߹�������������ֵ:";
			        cin >> e1 >> e2;
					cout << endl << "����ñߵ�Ȩֵ:";
					cin >> w;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
		            g.InsertArc(v1, v2, w);
			        break;
				case '9':
					cout << endl << "������������ֵ:";
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
					cout << endl << "������������ֵ:";
					cin >> e1 >> e2;
					g.SecShortestPath(e1, e2);
				case 'C':
					cout << endl << "������������ֵ:";
					cin >> e1 >> e2;
					g.superpath(e1, e2);
       	      }
         }
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}

