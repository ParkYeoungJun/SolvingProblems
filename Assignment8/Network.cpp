/*
 * Network.cpp
 *
 *  Created on: 2016. 5. 13.
 *      Author: Park
 */

#include<iostream>
#include<string.h>
#include<vector>

using namespace std;

int size;
int scc_count;
int school[102][102];
int school_reverse[102][102];
int visited[102];

vector<int> order;

void DFS(int i)
{
	visited[i] = 1;

	for(int j = 1 ; j <= size ; ++j)
	{
		if(school[i][j] == 1 && visited[j] == 0)
		{
			DFS(j);
		}
	}

	order.push_back(i);
}


void DFS2(int i)
{
	visited[i] = scc_count;

	for(int j = 1 ; j <= size ; ++j)
	{
		if(school_reverse[i][j] == 1 && visited[j] == 0)
		{
			DFS2(j);
		}
	}
}

void aDFS(int solution)
{
	int count = 0;
	int temp;

	if(solution == 1)
	{

		for(int i = 1 ; i <= size ; ++i)
		{
			if(visited[i] == 0)
			{
				DFS(i);
			}
		}
	}
	else
	{
		vector<int>::iterator iter = order.end()-1;

		for( ; iter >= order.begin() ; --iter)
		{
			if(visited[(*iter)] == 0)
			{
				++scc_count;
				DFS2((*iter));
			}
		}
	}
}

int main()
{
	std::ios::sync_with_stdio(false);

	cin >> size;

	int temp;
	int count = 0;

	for(int i = 1 ; i <= size ; ++i)
	{
		for(int j = 1 ; j <= size ; ++j)
		{
			cin >> temp;

			if(temp == 0)
				break;

			++count;

			school[i][temp] = 1;
			school_reverse[temp][i] = 1;
		}
	}

	if( count != 0)
	{
		aDFS(1);

		memset(visited , 0 , sizeof(visited));

		aDFS(2);

		if(scc_count == 1)
		{
			cout << "1" << endl << 0;
		}
		else
		{

			int out[102] = {};
			int in[102] = {};

			for(int i = 1 ; i <= size ; ++i)
			{
				for(int j = 1 ; j <= size ; ++j)
				{
					if(school[i][j] == 1)
					{
						if(visited[i] != visited[j])
						{
							++in[visited[j]];
							++out[visited[i]];
						}
					}
				}
			}

			int in_count = 0;
			int out_count = 0;

			for(int i = 1 ; i <= scc_count ; ++i)
			{
				if(in[i] == 0)
					++in_count;
				if(out[i] == 0)
					++out_count;
			}

			cout << in_count << endl << max(in_count, out_count);

		}
	}
	else
	{
		cout << size << endl << size;
	}
}


