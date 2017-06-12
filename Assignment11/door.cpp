/*
 * door.cpp
 *
 *  Created on: 2016. 5. 31.
 *      Author: Park
 */

#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

int oper;

int door[21];

int memo[21][21][21];

int result;

bool checkMemo(int index, int open1, int open2, int cost)
{
	if(memo[index][open1][open2] == -1 ||
			memo[index][open1][open2] > cost)
		return true;
	else
		return false;
}

void tracking(int index, int open1, int open2, int cost)
{
	if(index == oper)
	{
		if(result > cost)
			result = cost;
		return;
	}

	if(checkMemo(index, open1, open2, cost) && result > cost)
	{
		int temp_1, temp_2;

		temp_1 = open1-door[index];
		temp_2 = open2-door[index];

		if(temp_1 < 0)
			temp_1 *= -1;
		if(temp_2 < 0)
			temp_2 *= -1;

		memo[index][open1][open2] = cost;

		tracking(index+1, door[index], open2, cost+temp_1);
		tracking(index+1, open1, door[index], cost+temp_2);
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	memset(memo, -1, sizeof(memo));

	int size;

	cin >> size;

	int open1, open2;

	cin >> open1 >> open2;

	cin >> oper;

	for(int i = 0 ; i < oper ; ++i)
		cin >> door[i];

	result = 0x7FFFFFFF;

	tracking(0, open1, open2, 0);

	cout << result;
}


