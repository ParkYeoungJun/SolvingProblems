/*
 * Distance.cpp
 *
 *  Created on: 2016. 3. 21.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	string str1;
	string str2;
	int size_str1;
	int size_str2;

	int dp[83][83];

	while(getline(cin, str1))
	{
		size_str1 = str1.length();

		cin.clear();

		getline(cin, str2);

		size_str2 = str2.length();

		cin.clear();

		dp[0][0] = 0;

		for(int i = 1 ; i <= size_str1 ; ++i)
			dp[i][0] = i;

		for(int i = 1 ; i <= size_str2 ; ++i)
			dp[0][i] = i;

		for(int i = 1 ; i <= size_str1 ; ++i)
		{
			for(int j = 1 ; j <= size_str2 ; ++j)
			{
				int val = (str1[i-1] == str2[j-1]) ? 0 : 1;

				dp[i][j] = min(dp[i - 1][j - 1] + val ,dp[i - 1][j] + 1);
				dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
			}
		}

		cout << dp[size_str1][size_str2] << endl;

		int n = size_str1;
		int m = size_str2;
		int count = 0;

		while(n > 0 || m > 0)
		{
			if(str1[n - 1] == str2[m - 1]){
				--n;
				--m;
			}
			else
			{

				cout << ++count << " ";

				if(m > 0 && dp[n][m] == dp[n][m - 1]+1)
				{
					cout << "Insert " << n+1 << "," << str2[m - 1];
					str1.insert(n, 1, str2[m - 1]);
					--m;
				}
				else if(n > 0 && dp[n][m] == dp[n - 1][m] + 1)
				{
					cout << "Delete " << n;
					str1.erase(n - 1, 1);
					--n;
				}
				else if(n > 0 && m > 0)
				{
					cout << "Replace " << n << "," << str2[m - 1];
					str1[n - 1] = str2[m - 1];

					--n;
					--m;
				}

				cout << endl;

			}
		}

		if(!cin.peek())
			cout << endl;
	}
}

