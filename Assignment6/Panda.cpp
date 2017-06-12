/*
 * Panda.cpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int array[502][502];
int dp[502][502];

int size;

int x_y_pos[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

int dfs(int x, int y)
{
	if(dp[x][y] == 0)
	{
		dp[x][y] = 1;
		for(int i = 0 ; i < 4 ; ++i)
		{
			int temp_x = x + x_y_pos[i][0];
			int temp_y = y + x_y_pos[i][1];

			if( temp_x > 0 || temp_y > 0 || temp_x <= size || temp_y <= size)
			{
				if(array[temp_x][temp_y] > array[x][y])
					dp[x][y] = max( dfs(temp_x,temp_y)+1 , dp[x][y]);
			}
		}
	}

	return dp[x][y];
}

int main(void)
{
	cin >> size;

	for(int i = 1 ; i <= size ; ++i)
		for(int j = 1 ; j <= size ; ++j)
			cin >> array[i][j];

	int result = -1;

	for(int i = 1 ; i <= size ; ++i)
		for(int j = 1 ; j <= size ; ++j)
			result = max(result, dfs(i, j));

	cout << result;
}


