/*
 * Power.cpp
 *
 *  Created on: 2016. 5. 23.
 *      Author: Park
 */

#include<iostream>
#include<queue>
#include<string.h>

using namespace std;

int cap[105][105];

int Solve(int n)
{
    queue <int> q;

    int flow[105][105];
    int a[105];
    int p[105];

    memset(flow, 0, sizeof(flow));
    memset(p, 0, sizeof(p));

    int result = 0;

    while(true)
    {

    	memset(a, 0, sizeof(a));

    	a[0] = 0xFFFFFF;
        q.push(0);

        while(!q.empty())
        {
            int t = q.front();
            q.pop();

            for(int i = 0; i <= n+1; i++)
            {
                if((a[i] <= 0) && (cap[t][i] > flow[t][i]))
                {
                	p[i] = t;
                	q.push(i);
                	a[i] = min(a[t],cap[t][i] - flow[t][i]);
                }
            }
        }

        if(a[n+1] == 0)
            break;

        for(int i = n+1; i; i = p[i])
        {
            flow[p[i]][i] += a[n+1];
            flow[i][p[i]] -= a[n+1];
        }

        result += a[n+1];
    }

    return result;
}

int main()
{
	std::ios::sync_with_stdio(false);

    int x,y,z;
    int n, m, b, d;

    int num[105];

    while(cin >> n)
    {
    	memset(num, 0, sizeof(num));
        memset(cap,0,sizeof(cap));

        for(int i = 1;i <= n; i++)
        	cin >> num[i];

        cin >> m;

        for(int i = 0 ; i < m ; ++i)
        {
            cin >> x >> y >> z;
            cap[x][y] = z;
            cap[x][y] = min(cap[x][y], (num[x] > num[y] ? num[y] : num[x]));
        }


        cin >> b >> d;

        for(int i = 0 ; i < b ; ++i)
        {
            cin >> x;
            cap[0][x] = num[x];
        }


        for(int i = 0 ; i < d ; ++i)
        {
            cin >> x;
            cap[x][n+1] = num[x];
        }

        cout << Solve(n) << endl;
    }
}
