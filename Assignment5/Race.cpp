/*
 * Race.cpp
 *
 *  Created on: 2016. 3. 26.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	int max_dis, num_shop;
	int* distance = new int[103];
	int* shop_time = new int[103];
	int* dp = new int[103];

	cin >> max_dis;
	cin >> num_shop;

	for(int i = 1 ; i <= num_shop+1 ; ++i)
	{
		cin >> distance[i];

		distance[i] = distance[i] + distance[i-1];
	}

	for(int i = 1 ; i <= num_shop ; ++i)
		cin >> shop_time[i];

	for(int i = 1 ; i <= num_shop+1 ; ++i)
	{
		dp[i] = 0x7d2b7500;

		for(int j = 0 ; j < i ; ++j)
		{
			// 갈 수 있다면, 최대 거리보다 길지 않은가 검사, 갈 수 있다면 시간 구하고 최적값
			if(distance[i] - distance[j] <= max_dis)
				if(dp[i] > dp[j] + shop_time[i])
					dp[i] = dp[j] + shop_time[i];
		}
	}
	cout << dp[num_shop+1];
}



