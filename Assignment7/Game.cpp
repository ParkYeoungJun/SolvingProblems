/*
 * Game.cpp
 *
 *  Created on: 2016. 5. 6.
 *      Author: Park
 */

#include<iostream>
#include<string.h>
#include<queue>
#include<limits.h>

using namespace std;

int size_cal, size_row;
int array[77][77];

typedef struct dp
{
	int memo;
	int visit;
}dp;

void solve(int x1, int x2, int y1, int y2)
{
	int dx[4] = {0,1,0,-1};
	int dy[4] = {1,0,-1,0};
	int cal, row, co;
	int temp_x, temp_y;
	int cost;


	dp dp[size_cal+3][size_row+3][4];

	for(int i = 0 ; i <= size_cal+2 ; ++i)
		for(int j = 0 ; j <= size_row+2 ; ++j)
			for(int k = 0 ; k < 4 ; ++k)
			{
				dp[i][j][k].memo = 0;
				dp[i][j][k].visit = 0;
			}

	queue<int> x, y, comp;

	x.push(x1);
	y.push(y1);
	comp.push(-1);

	while(!x.empty())
	{
		cal = x.front();
		x.pop();
		row = y.front();
		y.pop();
		co = comp.front();
		comp.pop();

		dp[cal][row][co].visit = 0;

		for(int i = 0 ; i < 4 ; ++i)
		{
			temp_x = cal+dx[i];
			temp_y = row+dy[i];
			if(i == co)
				cost = 0;
			else
				cost = 1;

			if(temp_x < 0 || temp_y < 0 || temp_x > size_cal+1 || temp_y > size_row+1)
				continue;

			if(temp_x == x2 && temp_y == y2){}
			else if(array[temp_x][temp_y] == 1)
				continue;


			if(dp[temp_x][temp_y][i].memo == 0 || dp[temp_x][temp_y][i].memo > dp[cal][row][co].memo + cost)
			{
				dp[temp_x][temp_y][i].memo = dp[cal][row][co].memo+cost;

				if(dp[temp_x][temp_y][i].visit == 0){
					dp[temp_x][temp_y][i].visit = 1;

					x.push(temp_x);
					y.push(temp_y);
					comp.push(i);
				}
			}
		}
	}

	int mini = INT_MAX;

	for(int i = 0 ; i < 4 ; ++i)
	{
		if(dp[x2][y2][i].memo)
			mini = min(mini, dp[x2][y2][i].memo);
	}

	if(mini == INT_MAX)
	{
		cout << "impossible." << endl;
	}
	else
		cout << mini << " segments." << endl;
}

int main(void)
{
	std::ios::sync_with_stdio(false);

	int board_count = 0;

	while(true)
	{
		cin >> size_row >> size_cal;

		if(size_row+size_cal == 0)
		{
			return 0;
		}

		memset(array, 0, sizeof(array));

		cin.get();

		for(int i = 1 ; i <= size_cal ; ++i)
		{
			string str;

			getline(cin, str);

			for(int j = 0 ; j < str.length() ; ++j)
			{
				if(str[j] == 'X')
					array[i][j+1] = 1;
			}
		}

		int x1,x2,y1,y2;

		int count = 0;

		cout << "Board #" << ++board_count << ":" << endl;

		while(cin >> y1 >> x1 >> y2 >> x2)
		{
			if(x1+x2+y1+y2 == 0)
			{
				cout << endl;
				break;
			}

			cout << "Pair " << ++count << ": ";

			solve(x1, x2, y1, y2);
		}
	}
}


