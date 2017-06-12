/*
 * Locomotive.cpp
 *
 *  Created on: 2016. 3. 16.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	int size, car, upsize;
	int* data;
	int* sum;
	int** dp;

	cin >> size;

	upsize = size+1;	// size+1 ������ �ݺ� �ǹǷ�

	data = new int[size];

	for(int i = 0 ; i < size ; ++i)
		cin >> data[i];

	cin >> car;

	sum = new int[upsize];

	for(int i = car ; i <= size ; ++i)
	{
		for(int j = i - car ; j < i ; ++j)
		{
			sum[i] += data[j];
		}
	}

	dp = new int* [4];

	for(int i = 0 ; i < 4 ; ++i)
		dp[i] = new int[upsize];

	for(int i = 1 ; i < 4 ; ++i)
		for(int j = i*car ; j <= size ; ++j)
		{
			/*
			 * sum[j] + dp[i-1][j-car] = ���� j��  i��° ���� ������� �ش� �� �� ������
			 * dp[i][j-1] = ���� j�� i��° ���� ������� ���� ���� ���� �� ������
			 */

			dp[i][j] = max(sum[j] + dp[i - 1][j - car], dp[i][j - 1]);
		}

	cout << dp[3][size];
}


