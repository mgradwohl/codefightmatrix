#include <iostream>
#include <vector>
#include <cstdarg>
#include <string>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#include <sstream>
#include <numeric>
#include <iterator>
#include <iomanip>
#include <utility>
#include <stack>
#include <functional>
#include <deque>
#include <complex>
#include <bitset>
#include <list>
#include <array>
#include <regex>
#include <unordered_set>
#include <unordered_map>
#include <random>
using namespace std;

// 0==success
// >0 == # of iterations through to find failure
int findPath0(vector<vector<int>> matrix);
int findPath1(vector<vector<int>> matrix);
bool makeMatrix(vector<vector<int>> &matrix);
bool printMatrix(vector<vector<int>> &matrix);

void main()
{
	int ret0 = 1;
	int ret1 = 1;
	int mtx = 1;

	// simple test
	//vector<vector<int>> m1{ { 1,5 }, { 2, 6 }, { 4,3 } };
	//ret = findPath(m1);
	//cout << "Try #" << tries << "\t" << m1.size() << "," << m1[0].size() << "\t" << (ret ? "true" : "false") << endl;
	//ret = findPath2(m1);
	//cout << "Try #" << tries << "\t" << m1.size() << "," << m1[0].size() << "\t" << (ret ? "true" : "false") << endl;
	//printMatrix(m1);
	//cout << endl;

	vector<vector<int>> m0;
	while (mtx < 5)
	{
		makeMatrix(m0);
		ret0 = findPath0(m0);
		ret1 = findPath1(m0);
		cout << "Matrix #" << mtx << "\t" << "r0: " << ret0 << " r1: " << ret1 << "\t" << m0.size() << "," << m0[0].size() << "\t" << endl;
		printMatrix(m0);
		cout << endl;
		mtx++;
	}

	cout << "Hit enter..." << endl;
	cin.ignore(1);
}

bool makeMatrix(vector<vector<int>> &matrix)
{
	// create a random y, x matrix
	random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<> distr(2, 50);

	int sizex = distr(eng);
	int sizey = distr(eng);
	int k = sizex * sizey;
	matrix.clear();
	matrix.resize(sizey);
	for (int z = 0; z < sizey; z++)
	{
		matrix[z].clear();
		matrix[z].resize(sizex);
	}

	// make a map of all the numbers from 1 to y * k so that you use each value only once
	uniform_int_distribution<> range(1, k);
	vector<bool> list(k+1);
	for (int t = 0; t < list.size(); t++)
	{
		list[t] = false;
	}

	// populate the matrix, making sure 0,0 == 1
	int val = 0;
	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			if ((x == 0) && (y == 0))
			{
				val = 1;
			}
			else
			{
				// if the value has been used, get another one within the range
				val = range(eng);
				while (list[val] == true)
				{
					val = range(eng);
				}
			}
			list[val] = true;
			matrix[y][x] = val;
		}
	}
	return true;
}

bool printMatrix(vector<vector<int>> &matrix)
{
	int sizey = (int)matrix.size();
	int sizex = (int)matrix[0].size();

	for (int y = 0; y < sizey; y++)
	{
		cout << "[";
		for (int x = 0; x < sizex; x++)
		{
			cout << setw(3) << matrix[y][x];
			if (x < sizex - 1)
			{
				cout << ", ";
			}
		}
		cout << "]" << endl;
	}
	return true;
}

int findPath0(vector<vector<int>> matrix)
{
	int sizey = (int)matrix.size();
	int sizex = (int)matrix[0].size();

	int v = 0;
	int x = 0;
	int y = 0;
	bool ok = true;

	while (y < sizey && ok)
	{
		while (x < sizex && ok)
		{
			v = matrix[y][x];

			int t = matrix[max(0, y - 1)][x];
			int b = matrix[min(sizey-1, y + 1)][x];
			int l = matrix[y][max(0, x - 1)];
			int r = matrix[y][min(sizex-1, x + 1)];

			if( (abs(l-v) ==1) ||
				(abs(r-v) ==1) ||
				(abs(t-v) ==1) ||
				(abs(b-v) ==1) )
			{
				ok = true;
				x++;
			}
			else
			{
				ok = false;
			}
		}
		x = 0;
		y++;
	}

	return ok?0:x*y;
}

int findPath1(vector<vector<int>> matrix)
{
	int sizey = (int)matrix.size();
	int sizex = (int)matrix[0].size();
	int sizek = sizey * sizex;

	int v, j, k = 0;
	int x = 0;
	int y = 0;
	int i = 2;

	bool ok = true;

	while (i <= sizek && ok)
	{
		v = matrix[y][x];
		ok = false;

		// check top
		// int t = matrix[max(0, y - 1)][x];
		if (!ok)
		{
			j = max(0, y - 1);
			k = x;
			if (matrix[j][k] == i)
			{
				y = j;
				x = k;
				ok = true;
			}
		}

		// check bottom
		// int b = matrix[min(sizey - 1, y + 1)][x];
		if (!ok)
		{
			j = min(sizey - 1, y + 1);
			k = x;
			if (matrix[j][k] == i)
			{
				y = j;
				x = k;
				ok = true;
			}
		}

		// check right
		// int r = matrix[y][min(sizex - 1, x + 1)];
		if (!ok)
		{
			j = y;
			k = min(sizex - 1, x + 1);
			if (matrix[j][k] == i)
			{
				y = j;
				x = k;
				ok = true;
			}
		}

		// check left
		// int l = matrix[y][max(0, x - 1)];
		if (!ok)
		{
			j = y;
			k = max(0, x - 1);
			if (matrix[j][k] == i)
			{
				y = j;
				x = k;
				ok = true;
			}
		}
		i++;
	}

	return ok ? 0 : i - 2;
}