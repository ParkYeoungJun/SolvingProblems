/*
 * LowerPrice.cpp
 *
 *  Created on: 2016. 3. 17.
 *      Author: Park
 */


#include<iostream>
#include<iomanip>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	cout.setf(ios::fixed);
	cout.precision(2);

	double unit_price;
	int line, temp;
	int count = 1;

	while(cin >> unit_price >> line)
	{

		// new를 썻었지만, new를 줄여야 좋다는 것을 보고 그냥 할당
		double dp[102];

		for(int i = 0 ; i < 102 ; ++i)
		{
			dp[i] = 0xfffff;
		}

		dp[1] = unit_price;

		int number;
		double price;

		for(int i = 0 ; i < line ; ++i)
		{
			cin >> number >> price;

			for(int j = number ; j > 0 ; --j)
			{
				dp[j] = min(dp[j], price);
			}
		}


		cin.clear();
		cin.ignore();

		cout << "Case " << count++ << ":" << endl;

		int max = 0;

		while(cin >> temp)
		{
			if(max < temp)
			{
				/*
				 *  for 루프의 동작수를 줄이기 위해서 max만큼의 하한선을 둠
				 *  max이전 것은 다 최적값으로 나온 것이기 때문에 돌 필요 없으므로 뒤부터 돔
				 *  dp[i-j] + dp[j] = 자신의 개수를 포함하는 상한 세트의 상품 1개로 구입 한 것이 아닌 그 보다 적은 개수의 세트 물건들을 섞어서 나오는 최적값
				 *  dp[i] = 자신을 포함하는 세트 상품 1개의 값
				 */

				for(int i = max ; i <= temp ; ++i)
					for(int j = 0 ; j < i ; ++j)
						dp[i] = min(dp[i - j] + dp[j], dp[i]);

				max = temp;
			}

			cout << "Buy " << temp << " for $" << dp[temp] << endl;

			if(cin.peek() == '\n')
				break;
		}
	}
}
