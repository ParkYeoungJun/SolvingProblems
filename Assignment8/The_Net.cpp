/*
 * The_net.cpp
 *
 *  Created on: 2016. 5. 14.
 *      Author: Park
 */

#include<iostream>
#include<string.h>
#include<algorithm>

using namespace std;

int** path_array;

void path(int x, int y)
{
        if(path_array[x][y] != 0){
                path(x, path_array[x][y]);
                cout << " " << path_array[x][y];
                path(path_array[x][y], y);
        }
}

int main()
{
	std::ios::sync_with_stdio(false);


	int size;
	int deter_size;
	int x, y;
	char* input;
	char* temp;

	int** dp;
	int** index;

	while(cin >> size)
	{

		dp = new int* [size+3];
		path_array = new int* [size+3];
		temp = new char [size+3];
		for(int i = 0 ; i <= size ; ++i)
		{
			dp[i] = new int[size+3];
			path_array[i] = new int[size+3];
		}

		for(int i = 1; i <= size ; ++i){

			memset(temp , 0 , sizeof(temp));

			cin >> temp;

			input = strtok(temp,"-,");
			x = atoi(input);

			while(input = strtok('\0',"-,")){
				y = atoi(input);
				dp[x][y] = 1;
			}

		}

		for(int i = 1; i <= size; ++i){
			for(int j = 1; j <= size; ++j){
				for(int k = 1; k <= size; ++k){
					if(dp[j][i]&&dp[i][k])
						if( !dp[j][k] ||dp[j][k] > dp[j][i]+dp[i][k]){
							dp[j][k] = dp[j][i]+dp[i][k];
							path_array[j][k] = i;
						}
				}
			}
		}

		cin >> deter_size;

		index = new int* [deter_size+3];
		for(int i = 0 ; i <= deter_size ; ++i)
			index[i] = new int[3];


		for(int i = 1; i <= deter_size; ++i){
			cin >> index[i][0] >> index[i][1];
		}

		cout << "-----" << endl;

		for(int i = 1; i <= deter_size; ++i){
			if(dp[index[i][0]][index[i][1]] != 0)
			{
				cout << index[i][0];
				path(index[i][0], index[i][1]);
				cout << " " << index[i][1] << endl;
			}
			else
			{
				cout << "connection impossible" << endl;
			}
		}
	}
}

