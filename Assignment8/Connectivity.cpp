/*
 * Connectivity.cpp
 *
 *  Created on: 2016. 5. 13.
 *      Author: Park
 */

#include<iostream>
#include<string.h>
#include<stdio.h>

using namespace std;

int visited[30];
int graph[30][30];
int size;

void aDFS(int i)
{
	visited[i] = 1;

	for(int j = 1 ; j <= size ; ++j)
	{
		if(graph[i][j] == 1 && visited[j] == 0)
		{
			aDFS(j);
		}
	}
}

int DFS()
{
	int count = 0;

	for(int i = 1 ; i <= size ; ++i)
	{
		if(visited[i] == 0)
		{
			aDFS(i);
			++count;
		}
	}

	return count;
}

int main(){

	int casenum;
	char str[3];

    scanf("%d\n\n",&casenum);

	char al1, al2;
	string temps;

	while(casenum-- > 0)
	{
		getline(cin, temps);

		size = temps[0] - 64;

		memset(graph,0,sizeof(graph));
		memset(visited,0,sizeof(visited));

		while(true)
		{
            if(!getline(cin,temps) || temps.empty())
            	break;

			int x = temps[0]-64, y = temps[1] - 64;

			graph[x][y] = 1;
			graph[y][x] = 1;
		}

		cout << DFS() << endl;

		if(casenum > 0)
			cout << endl;
	}
}


