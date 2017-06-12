/*
 * Omok.cpp
 *
 *  Created on: 2016. 3. 9.
 *      Author: Park
 */

#include<iostream>

using namespace std;

int winner, win_x, win_y;

void whether_win(int** pan, int x, int y)
{
	int width = x;
	int height = y;

	int count = 0;

	// 세로
	for(; width < x+5 && width < 20 ; width++)
	{
		if(pan[x][y] == pan[width][y])
			++count;
	}

	if(count == 5)
	{
		if(x == 1)
		{
			if(pan[x+5][y] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if(x == 15)
		{
			if(pan[x-1][y] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if(x-1 > 0 && x+5 < 20)
		{
			if(pan[x-1][y] != pan[x][y] && pan[x+5][y] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
	}

	width = x;
	count = 0;

	// 가로
	for( ; height < y+5 && height < 20 ; height++)
	{
		if(pan[x][y] == pan[x][height])
			++count;
	}

	if(count == 5)
	{
		if(y == 1)
		{
			if(pan[x][y+5] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if(y == 15)
		{
			if(pan[x][y-1] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if(y-1 > 0 && y+5 < 20)
		{
			if(pan[x][y-1] != pan[x][y] && pan[x][y+5] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
	}

	height = y;
	count = 0;

	// 아래 대각선
	for( ; width < x+5 && width < 20 && height < y+5 && height < 20; height++, width++)
	{
		if(pan[x][y] == pan[width][height])
			++count;
	}

	if(count == 5)
	{
		if((x == 1 && y < 15) || (y == 1 && x < 15))
		{
			if(pan[x][y] != pan[x+5][y+5])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if((x == 15 && y > 1 && y <= 15) || (y == 15 && x > 1 && x <= 15))
		{
			if(pan[x][y] != pan[x-1][y-1])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if((x == 15 && y == 1) || (x == 1 && y == 15)){

			winner = pan[x][y];

			win_x = x;
			win_y = y;
		}
		else
		{
			if(pan[x-1][y-1] != pan[x][y] && pan[x+5][y+5] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
	}

	width = x;
	height = y;
	count = 0;

	// 위 대각선
	for( ; width > x-5 && width > 0 && height < y+5 && height < 20 ; width--, height++)
	{
		if(pan[x][y] == pan[width][height])
			++count;
	}

	if(count == 5)
	{
		if((y == 1 && x <= 19 && x > 5) || (x == 19 && y < 15 && y >= 1))
		{
			if(pan[x-5][y+5] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if((x == 5 && y > 1 && y <= 15) || (y == 15 && x >= 5 && x < 19))
		{
			if(pan[x+1][y-1] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
		else if((x == 5 && y == 1) || (x == 19 && y == 15))
		{
			winner = pan[x][y];

			win_x = x;
			win_y = y;
		}
		else
		{
			if(pan[x+1][y-1] != pan[x][y] && pan[x-5][y+5] != pan[x][y])
			{
				winner = pan[x][y];

				win_x = x;
				win_y = y;
			}
		}
	}
}

int main(void)
{
	winner = 0;

	int** pan;

	pan = new int*[20];

	for(int i = 1 ; i < 20 ; ++i)
		pan[i] = new int[20];

	for(int i = 1 ; i < 20 ; ++i)
		for(int j = 1 ; j < 20 ; ++j)
			cin >> pan[i][j];

	for(int i = 1 ; i < 20 ; ++i)
		for(int j = 1 ; j < 20 ; ++j)
		{
			if(pan[i][j] != 0)
				whether_win(pan, i, j);
		}

	if(winner != 0)
	{
		cout << winner << endl;

		cout << win_x << " " << win_y;
	}
	else
		cout << "0";
}
