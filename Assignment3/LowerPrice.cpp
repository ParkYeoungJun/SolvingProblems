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

		// new�� ��������, new�� �ٿ��� ���ٴ� ���� ���� �׳� �Ҵ�
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
				 *  for ������ ���ۼ��� ���̱� ���ؼ� max��ŭ�� ���Ѽ��� ��
				 *  max���� ���� �� ���������� ���� ���̱� ������ �� �ʿ� �����Ƿ� �ں��� ��
				 *  dp[i-j] + dp[j] = �ڽ��� ������ �����ϴ� ���� ��Ʈ�� ��ǰ 1���� ���� �� ���� �ƴ� �� ���� ���� ������ ��Ʈ ���ǵ��� ��� ������ ������
				 *  dp[i] = �ڽ��� �����ϴ� ��Ʈ ��ǰ 1���� ��
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
