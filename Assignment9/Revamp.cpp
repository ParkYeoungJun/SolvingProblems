/*
 * Revamp.cpp
 *
 *  Created on: 2016. 5. 17.
 *      Author: Park
 */

#include<iostream>
#include<queue>
#include<string.h>

using namespace std;

typedef struct way{

	int v;
	int t;

}way;

typedef struct node{

	int v;
	int k;
	int dist;

	bool operator < (node temp) const
	{
		return dist > temp.dist;
	}

}node;



int main()
{
	std::ios::sync_with_stdio(false);

	int road, garden, highway;

	cin >> road >> garden >> highway;

	vector< vector<way> > array(road+2);

//	way** array;
//	array = new way* [road+2];
//	for(int i = 0 ; i < road+2 ; ++i)
//		array[i] = new way[road+2];

	way way_temp;

	for(int i = 0 ; i < road ; ++i)
	{
		way_temp.v = i;
		way_temp.t = 0;

		array[i].push_back(way_temp);
	}

	int n, m, k;

	for(int i = 0 ; i < garden ; ++i)
	{
		cin >> n >> m >> k;
		--n;
		--m;

		way_temp.v = m;
		way_temp.t = k;
		array[n].push_back(way_temp);

		way_temp.v = n;
		array[m].push_back(way_temp);
	}

	priority_queue<node> que;

	int visited[road][highway+2];

	memset(visited , 0 , sizeof(visited));

	node node_temp;
	node node_que;

	node_temp.v = 0;
	node_temp.k = 0;
	node_temp.dist = 0;

	que.push(node_temp);

	while(true)
	{
		node_que = que.top();
		que.pop();

		if(node_que.v == road-1 && node_que.k == highway)
		{
			cout << node_que.dist;
			return 0;
		}

		if(visited[node_que.v][node_que.k] == 1)
			continue;

		visited[node_que.v][node_que.k] = 1;

		for(int i = 0 ; i < array[node_que.v].size() ; ++i)
		{
			if(visited[array[node_que.v][i].v][node_que.k] == 0)
			{
				node_temp.v = array[node_que.v][i].v;
				node_temp.k = node_que.k;
				node_temp.dist = node_que.dist + array[node_que.v][i].t;
				que.push(node_temp);
			}

			if(node_que.k < highway && visited[array[node_que.v][i].v][node_que.k+1] == 0)
			{
				node_temp.v = array[node_que.v][i].v;
				node_temp.k = node_que.k+1;
				node_temp.dist = node_que.dist;
				que.push(node_temp);
			}
		}
	}
}


