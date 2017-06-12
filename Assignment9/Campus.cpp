/*
 * Campus.cpp
 *
 *  Created on: 2016. 5. 18.
 *      Author: Park
 */

#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string.h>

using namespace std;

struct array{
	double x;
	double y;
}array[1002];


int visited[1002];
double lower[1002];
double dis[1002][1002];

void prim(int size)
{
	memset(visited, 0 , sizeof(visited));

	double result = 0;
	double min;
	int pos;

	visited[1] = 1;

	for(int i = 1 ; i <= size ; ++i)
		lower[i] = dis[1][i];

	for(int i = 1 ; i <= size ; ++i)
	{
		min = 0xFFFFFFF;

		for(int j = 1 ; j <= size ; ++j)
		{
			if(visited[j] == 0 && lower[j] < min)
			{
				min = lower[j];
				pos = j;
			}
				}

		if(min == 0xFFFFFFF)
		{
			break;
		}

		result += min;

		visited[pos] = 1;

		for(int j = 1 ; j <= size ; ++j)
		{
			if(visited[j] == 0 && lower[j] > dis[pos][j])
				lower[j] = dis[pos][j];
		}
	}


	printf("%.2lf\n", result);
}

int main()
{
//	std::ios::sync_with_stdio(false);
	cout.precision(3);
	cin.precision(2);

	int size;
	int cable;
	int temp1, temp2;

	while(cin >> size)
	{

		for(int i = 1 ; i <= size ; ++i)
		{
			cin >> array[i].x >> array[i].y;
		}

		for(int i = 1 ; i <= size ; ++i)
		{
			for(int j = 1 ; j <= size ; ++j)
			{


				dis[i][j] = sqrt(((array[i].x - array[j].x)*(array[i].x - array[j].x))+
						((array[i].y - array[j].y) * (array[i].y - array[j].y)));
			}
		}

		cin >> cable;


		for(int i = 1 ; i <= cable ; ++i)
		{
			cin >> temp1 >> temp2;

			dis[temp1][temp2] = 0;
			dis[temp2][temp1] = 0;
		}

		prim(size);
	}
}


