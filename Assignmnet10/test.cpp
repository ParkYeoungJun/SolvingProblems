/*
 * Math.cpp
 *
 *  Created on: 2016. 5. 26.
 *      Author: Park
 */

#include<iostream>
#include<stdlib.h>

using namespace std;

struct array
{
	char str[12];
	int length;
	char tonum[12];
};

struct Word
{
	char w;
	int num;
	int len;
};

int cmp(const void* a, const void* b)
{
	Word x = *(Word *) a;
	Word y = *(Word *) b;

	if(x.len > y.len)
		return -1;
	else if(x.len < y.len)
		return 1;
	else
	{
//		if(x.num > y.num)
//			return -1;
//		else if(x.num < y.num)
//			return 1;
//		else
			return 0;
	}
}

//int Solve(Word* word, array* in, int index, int size)
//{
//	int maxi;
//	int result = 0;
//
//	for(int i = 0 ; i < size ; ++i)
//	{
//		maxi = in[i].length;
//
//		for(int j = 0 ; j < maxi ; ++j)
//		{
//			for(int d = 0 ; d < index ; ++d)
//			{
//				if(word[d].w == in[i].str[j])
//				{
//					in[i].tonum[j] = word[d].num + '0';
//				}
//			}
//		}
//
//		int re = 0;
//
//		for(int z = 0 ; z < in[i].length ; ++z)
//		{
//			re = 10 * re + in[i].tonum[z] - '0';
//		}
//
//		result += re;
//	}
//	return result;
//}

array in[12];
Word word[12];

int visited[12] = {};

int main()
{
	std::ios::sync_with_stdio(false);

//	array in[12];
//	Word word[12];

	int index = 0;
	int size;
//	int visited[12];
	int max_length = 0;

	cin >> size;

	for(int i = 0 ; i < size ; ++i)
	{
		cin >> in[i].str;

		int com = 0;

		for(int j = 0 ; j < 10 ; ++j)
		{
			if(in[i].str[j] == '\0')
			{
				break;
			}

			++com;
		}

		in[i].length = com;

		if(max_length < in[i].length)
			max_length = in[i].length;
	}

	int max;

	for(int i = 0 ; i < size ; ++i)
	{
		max = in[i].length;

		for(int j = 0 ; j < max; ++j)
		{
			bool whe = false;

			for(int k = 0 ;  ; ++k)
			{
				if(word[k].w == '\0')
					break;

				if(in[i].str[j] == word[k].w)
				{
					whe = true;

					if(word[k].len < in[i].length-j)
						word[k].len += in[i].length-j;

					break;
				}
			}

			if(!whe)
			{
				word[index].w = in[i].str[j];
				word[index].len = in[i].length-j;
				++index;
			}
		}
	}

	qsort(word, index, sizeof(Word), cmp);

	int c = 9;

	for(int i = 0 ; i < index ; ++i)
	{
		word[i].num = c;
		--c;
	}

	for(int i = 0 ; i < index ; ++i)
	{
		cout << "w : " << word[i].w << endl;
		cout << "num : " << word[i].num << endl;
		cout << "len : " << word[i].len << endl;
	}

	int maxi;
	int result = 0;

	for(int i = 0 ; i < size ; ++i)
	{
		maxi = in[i].length;

		for(int j = 0 ; j < maxi ; ++j)
		{
			for(int d = 0 ; d < index ; ++d)
			{
				if(word[d].w == in[i].str[j])
				{
					in[i].tonum[j] = word[d].num + '0';
				}
			}
		}

		int re = 0;

		for(int z = 0 ; z < in[i].length ; ++z)
		{
			re = 10 * re + in[i].tonum[z] - '0';
		}

		result += re;
	}

	cout << result;
}

