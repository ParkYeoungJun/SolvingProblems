/*
 * Jop.cpp
 *
 *  Created on: 2016. 6. 2.
 *      Author: Park
 */

#include<iostream>
#include<list>
#include<queue>
#include<string.h>

using namespace std;

struct Edge
{
	int s;
	int t;
	int cost;
	int flow;
	int rev;
	int cap;

	Edge()
	{
		s = 0;
		t = 0;
		cost = 0;
		flow = 0;
		rev = 0;
		cap = 0;
	}

	Edge(int s, int t, int rev, int cap, int cost)
	{
		this->s = s;
		this->t = t;
		this->rev = rev;
		this->cap = cap;
		this->cost = cost;
		this->flow = 0;
	}
};

struct Item
{
	int dist;
	int v;

	Item(int dist, int v)
	{
		this->dist = dist;
		this->v = v;
	}

};

struct cmp
{
	bool operator()(const Item& it1,const Item& it2)
	{
		if(it1.dist > it2.dist)
			return true;
		else if(it1.dist < it2.dist)
			return false;
		else
		{
			return true;
		}

//		return it1.dist > it2.dist;
	}
};


int n,m;

int count = 0;

void add(int s, int t, int cap, int cost, vector<vector<Edge> > &edges)
{
	Edge temp_s(s, t, edges[t].size(), cap, cost);
	edges[s].push_back(temp_s);

	Edge temp_t(t, s, edges[s].size()-1, 0, -cost);
	edges[t].push_back(temp_t);
}

int MCMF(int source, int sink, int vertex_num, vector<vector<Edge> > &edges)
{
	int* spot = new int[vertex_num];
	int flow = 0;
	int cost = 0;

	for(int i = 0 ; i < vertex_num ; ++i)
		spot[i] = 0;

	while(true)
	{
		++count ;

		Edge* parent = new Edge[vertex_num];

		int* dist = new int[vertex_num];

		for(int i = 0 ; i < vertex_num ; ++i)
			dist[i] = 0x7FFFFFFF;

		dist[source] = 0;

		priority_queue<Item, vector<Item>, cmp> que;

		Item tm(0, source);

		que.push(tm);

		while(!que.empty())
		{
			Item temp = que.top();
			que.pop();

			cout << "top.dist : " << temp.dist << "top.v : " << temp.v << endl;

			if(temp.dist != dist[temp.v])
				continue;

			for(int i = 0 ; i < edges[temp.v].size() ; ++i)
			{
				Edge temp_e = edges[temp.v].at(i);

				long temp_c = dist[temp.v] + temp_e.cost + spot[temp.v] - spot[temp_e.t];

//				cout << "temp_e.cap : " << temp_e.cap << endl;
//				cout << "temp_e.flow : " << temp_e.flow << endl;
//				cout << "temp_e.t : " << temp_e.t << endl;
//				cout << "dist[temp_e.t] : " << dist[temp_e.t] << endl;
//				cout << "temp_c : " << temp_c << endl;
//				cout << endl;

				if(temp_e.cap > temp_e.flow && dist[temp_e.t] > temp_c)
				{
					dist[temp_e.t] = temp_c;
					parent[temp_e.t] = temp_e;

					Item it(temp_c, temp_e.t);

					cout << "it.dist : " << it.dist << "it.v : " << it.v << endl;

					que.push(it);
				}
			}
		}

		if(count == 1)
			break;

		if(parent[sink].s == 0 && parent[sink].t == 0 && parent[sink].cap == 0 && parent[sink].cost == 0 && parent[sink].flow == 0 && parent[sink].rev == 0)
		{
			break;
		}

		for(int i = 0 ; i < vertex_num ; ++i)
		{
			if(parent[i].s != 0 && parent[i].t != 0)
			{
				spot[i] += dist[i];
			}
		}

		int aflow = 0x7FFFFFFF;

		for(int i = sink ; i != source ; i = parent[i].s)
		{
			aflow = min(aflow, parent[i].cap - parent[i].flow);
		}


		for(int i = sink ; i != source ; i = parent[i].s)
		{
			Edge t_e = parent[i];

			t_e.flow += aflow;
			edges[t_e.t].at(t_e.rev).flow -= aflow;
			cost += aflow * t_e.cost;
		}

		flow += aflow;
	}

	return cost;
}

int main()
{
	std::ios::sync_with_stdio(false);

	while(cin >> n >> m)
	{
		if(n == 0 && m == 0)
			break;

		int vertex_num = n+m+2;

		vector<vector<Edge> > edges(vertex_num);


//		for(int i = 0 ; i < n ; ++i)
//			edges[i] = new vector<Edge>;

		int p;

		for(int i = 0 ; i < n ; ++i)
		{
			cin >> p;

			add(m+i, vertex_num-1, p, 0, edges);
		}

		for(int i = 0 ; i < m ; ++i)
		{

			add(vertex_num-2, i, 1, 0, edges);

			int grade, posting, cost;
			cin >> grade;
			for(int j = 0 ; j < 4 ; ++j)
			{
				cin >> posting;
				cost = 13-grade*4+j;

				add(i, m+posting, 1, cost, edges);
			}
		}

//		for(int i = 0 ; i < edges.size() ; ++i)
//		{
//			for(int j = 0 ; j < edges[i].size() ; ++j)
//			{
//				cout << "cap : " << edges[i][j].cap << endl;
//				cout << "cost : " << edges[i][j].cost << endl;
//				cout << "flow : " << edges[i][j].flow << endl;
//				cout << "rev : " << edges[i][j].rev << endl;
//				cout << "s : " << edges[i][j].s << endl;
//				cout << "t : " << edges[i][j].t << endl;
//			}
//		}

		cout << 13*m - MCMF(vertex_num-2, vertex_num-1, vertex_num, edges) << endl;
	}
}
