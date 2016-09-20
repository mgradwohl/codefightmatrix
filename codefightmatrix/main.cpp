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

using namespace std;

bool findPath(vector<vector<int>> matrix);

void main()
{
	bool ret;

	vector<vector<int>> m1{ {1, 4, 5},{2, 3, 6} };
	ret = findPath(m1);
	cout << "m1 " << ret << endl;

	vector<vector<int>> m2{ { 1, 5, 3 },{ 4, 2, 6 } };
	ret = findPath(m2);
	cout << "m2 " << ret << endl;

	cin.ignore(1);
}

bool findPath(std::vector<std::vector<int>> matrix)
{
	int sizey = matrix.size();
	int sizex = matrix[0].size();

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

	return ok;
}