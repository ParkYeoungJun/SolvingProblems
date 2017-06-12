/*
 * Useless.cpp
 *
 *  Created on: 2016. 4. 20.
 *      Author: Park
 */

#include<iostream>
#include<math.h>
#include<algorithm>
#include<stack>

using namespace std;

typedef struct position
{
	int x;
	int y;
	int dis;
}position;

position start_point;

double Convex_Area(position* pos, int size)
{
	double result = 0;

	pos[size] = pos[0];

	for(int i = 0 ; i < size ; ++i)
	{
		result += pos[i].x*pos[i+1].y - pos[i].y*pos[i+1].x;
	}

	return fabs(result/2);
}

bool func_sort_area(position pos1, position pos2)
{
	if(pos1.x == pos2.x)
		return pos1.y < pos2.y;
	else
		return pos1.x < pos2.x;
}

int ccw(position pos1, position pos2, position pos3)
{
	return (pos2.x - pos1.x)*(pos3.y - pos1.y) - (pos2.y - pos1.y)*(pos3.x - pos1.x);
}

bool func_sort_degree(position pos1, position pos2)
{
	if(!ccw(start_point, pos1, pos2))
		return pos1.dis < pos2.dis;
	else
		return ccw(start_point, pos1, pos2) > 0;
}

int dist(position pos1, position pos2)
{
	return (pos1.x - pos2.x)*(pos1.x-pos2.x) + (pos1.y-pos2.y)*(pos1.y-pos2.y);
}

double Convex_Hull(position* pos, int size)
{
	if(size <= 3)
	{
		return Convex_Area(pos, size);
	}
	else
	{
		sort(pos, pos+size, func_sort_area);

		for(int i = 1 ; i < size ; ++i)
		{
			pos[i].dis = dist(pos[0], pos[i]);
		}

		start_point = pos[0];

		sort(pos+1, pos+size, func_sort_degree);

		int temp_size = 1;

		for(int i = 2 ; i < size ; ++i)
		{
			while( temp_size > 0 && ccw(pos[temp_size-1], pos[temp_size], pos[i]) <= 0)
				temp_size--;

			pos[++temp_size] = pos[i];
		}

		return Convex_Area(pos, temp_size+1);
	}



}

int main(void)
{
	std::ios::sync_with_stdio(false);
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);


	int size, count;
	double Area_tile, Area_container;

	count = 0;

	while(cin >> size)
	{
		if(size == 0)
			break;

		position* pos;
		pos = new position[size+2];

		for(int i = 0 ; i < size ; ++i)
			cin >> pos[i].x >> pos[i].y;

		Area_tile = Convex_Area(pos, size);

		Area_container = Convex_Hull(pos, size);

		cout << "Tile #" << ++count << endl;
		cout << "Wasted Space = " << (Area_container-Area_tile)/(Area_container)*100.0 << " %"
				<< endl << endl;

		delete pos;
	}
}


