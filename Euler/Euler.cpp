#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;
#define vmax 20
#define vc 100
struct DoThi
{
	int flag;
	int n;
	int m[vmax][vmax];
};
int chuaxet[100];
void docFile(DoThi &g,string filename)
{
	fstream f;
	f.open(filename);
	cout <<"Do thi: "<<filename;
	if (f.eof())cout << "\nKhong tim thay file";
	else
	{
		f >> g.flag;
		f >> g.n;
		for (int i = 1; i <= g.n; i++)
		{
			for (int j = 1; j <= g.n; j++)
			{
				f >> g.m[i][j];
			}
		}
	}
	f.close();
}
void xuatDoThi(DoThi g)
{
	if (g.flag == 0)
		cout << "\nDothi vo huong";
	else
		cout << "\nDo thi co huong";
	cout << "\nMa tran cua do thi la: \n";
	for (int i = 1; i <= g.n; i++)
	{
		cout << endl;
		for (int j = 1; j <= g.n; j++)
			cout << g.m[i][j] << " ";
	}
}
void tinhBacCuaDinh(DoThi g,int bac[])
{
	for (int i = 1; i <= g.n; i++)
	{
		bac[i] = 0;
		if (g.flag == 0)
		{
			for (int j = 1; j <= g.n; j++)
				bac[i] += g.m[i][j];
			bac[i] += g.m[i][i];
		}
		else
		{
			for (int j = 1; j <= g.n; j++)
				bac[i] += g.m[i][j] + g.m[j][i];
		}
	}
	for (int i = 1; i <= g.n; i++)
	{
	//cout << "\nBac cua dinh " << i << " la: " << bac[i];
	}
}
int soThanhPhanLienThong(DoThi g)
{
	int stplt = 0;
	for (int i = 1; i <= g.n; i++)
	{
		chuaxet[i] = 0;
	}
	int dem = 0;
	stack <int> s;
	while (dem < g.n)
	{
		int i = 1;
		while (chuaxet[i] != 0)
		{
			i++;
		}
		s.push(i);
		while (!s.empty())
		{
			int i = s.top();
			s.pop();
			chuaxet[i] = 1;
			dem++;
			for (int j = 1; j <= g.n; j++)
			{
				if (chuaxet[j] == 0 && g.m[i][j] != 0)
				{
					s.push(j);
					chuaxet[j] = 1;
				}
			}
		}
		stplt++;
	}
	return stplt;
}

int demDinhBacLe(int bac[], int n)
{
	int dem = 0;
	for (int i = 1; i <= n; i++)
	{
		if (bac[i] % 2 != 0)
			dem++;
	}
	return dem;
}
int ktraEuler(DoThi g)
{
	int bac[vmax];
	tinhBacCuaDinh(g, bac);
	int dembacle = demDinhBacLe(bac, g.n);
	int demstplt = soThanhPhanLienThong(g);
	if (demstplt == 1)
	{
		if (dembacle == 0)
		{
			cout << "\nDo thi co chu trinh Euler";
			return 1;
		}
		else
		{
			if (dembacle == 2)
			{
				cout << "\nDo thi co duong di Euler";
				return 2;
			}
			else
			{

				cout << "\nDoThi khong co chu trinh va duong di Euler";
				return 0;
			}
		}
	}
	else
	{
		cout << "\nDo thi khong co chu trinh va duong di Euler";
		return 0;
	}
}
void chuTrinhEuler(DoThi g)
{
	
		stack<int> s;
		queue<int> ce;
		s.push(1);
		while (!s.empty())
		{
			int i = s.top();
			int j;
			for (j = 1; j <= g.n; j++)
				if (g.m[i][j] != 0)
				{
					s.push(j);
					g.m[i][j] = g.m[j][i] = 0;
					break;
				}
			if (j > g.n)
			{
				int p = s.top();
				s.pop();
				ce.push(p);
			}
		}
		cout << "\nChu trinh Euler can tim: ";
		while (!ce.empty())
		{
			cout << "\t" << ce.front();
			ce.pop();
		}
		cout << "\n";
	
	
}
void duongDiEuler(DoThi g)
{
	int bac[vmax];
	tinhBacCuaDinh(g, bac);
	int i = 1;
	while (bac[i] % 2 == 0)
		i++;
	stack<int> s;
	queue<int> ce;
	s.push(i);
	while (!s.empty())
	{
		int i = s.top();
		int j;
		for (j = 1; j <= g.n; j++)
			if (g.m[i][j] != 0)
			{
				s.push(j);
				g.m[i][j] = g.m[j][i] = 0;
				break;
			}
		if (j > g.n)
		{
			int p = s.top();
			s.pop();
			ce.push(p);
		}
	}
	cout << "\nDuong di Euler can tim: ";
	while (!ce.empty())
	{
		cout << "\t" << ce.front();
		ce.pop();
	}
	cout << "\n";

}
int main()
{
	DoThi g;
	string filename = "dothi3.txt";
	int bac[vmax];
	docFile(g,filename);
	xuatDoThi(g);
	cout<<"\nSo tplt: "<<soThanhPhanLienThong(g);
	//tinhBacCuaDinh(g,bac);
	//ktraEuler(g);
	int kq = ktraEuler(g);
	if (kq == 1)
	{
		chuTrinhEuler(g);
	}
	else if(kq==2)
	{
		duongDiEuler(g);
	}
	return 0;
}