/*
 * Help.cpp
 *
 *  Created on: 2016. 5. 6.
 *      Author: Park
 */

#include<iostream>
#include<string.h>
#include<algorithm>

using namespace std;

int temp[30];
string array[16];
int topic_size, single_size, pro_size;
int dp[17][17];

void dfs(int index, int i)
{
	if(index == single_size)
	{
		for(i = 0 ; i < index ; ++i)
		{
			cout << array[temp[i]];

			if(i < index-1)
				cout << " ";
		}

		cout << endl;

		return;
	}

	int k;

	for(; i < topic_size ; ++i)
	{
		for(k = 0 ; k < index ; ++k)
			if(dp[i][temp[k]] == 1)
				break;


		if(k == index){
			temp[index] = i;
			dfs(index+1, i+1);
		}
	}
}

bool compare_length(string a, string b){
	if(a.length() != b.length())
		return a.length() > b.length();
	else
		return a < b;
}

int get_position(string* array, int topic_size)
{
	string a;
	int i;

	cin >> a;

	for(i = 0 ; i < a.length() ; ++i)
	{
		a[i] = toupper(a[i]);
	}

	for(i = 0 ; i < topic_size ; ++i)
	{
		if(a.compare(array[i]) == 0)
			break;
	}

	return i;
}

int main(void)
{
	std::ios::sync_with_stdio(false);

	int set_size, count;

	cin >> set_size;

	count = 0;

	while(true)
	{

		cin >> topic_size >> pro_size >> single_size;

		for(int i = 0 ; i < topic_size ; ++i)
		{
			cin >> array[i];

			for(int j = 0 ; j < array[i].length() ; ++j)
			{
				array[i][j] = toupper(array[i][j]);
			}
		}

		sort(array, array+topic_size , compare_length);

		memset(dp, 0, sizeof(dp));

		int pos_x, pos_y;

		for(int i = 0 ; i < pro_size ; ++i)
		{
			pos_x = get_position(array, topic_size);
			pos_y = get_position(array, topic_size);

			dp[pos_x][pos_y] = 1;
			dp[pos_y][pos_x] = 1;
		}

		cout << "Set " << ++count << ":" << endl;

		dfs(0 , 0);

		cin.clear();

		cout << endl;

		if(count == set_size)
			return 0;
	}
}


