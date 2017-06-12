/*
 * Palin.cpp
 *
 *  Created on: 2016. 3. 21.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	int size;

	cin >> size;

	char* str = new char[size + 2];
	char* reverse = new char[size + 2];

	int rev = size;

	for(int i = 1 ; i <= size ; ++i)
	{
		cin >> str[i];

		reverse[rev--] = str[i];
	}

	int** dp;
	dp = new int*[size + 2];
	for (int i = 0; i <= size; ++i)
	dp[i] = new int[size + 2];

	for (int i = 1; i <= size; ++i)
	{
		for (int j = 1; j <= size; ++j)
		{
			if(str[i] != reverse[j])
				dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			else
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
		}
	}
	cout << size - dp[size][size];
}