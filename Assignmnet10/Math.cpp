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

array in[12];
Word word[12];

int size;
int index;
int visited[12];
int count = 0;
int max_length;
int result = 0;

bool promising()
{
    bool whe = false;

    for(int i = 0 ; i < 10 ; ++i)
    {
        if(word[i].len == max_length)
        {
            if(word[i].num == 9)
            {
                whe = true;
            }
        }
    }

    for(int i = index-1 ; i > 0 ; --i)
    {
        for(int j = 0 ; j < i ; ++j)
        {
            if(word[i].len < word[j].len)
                if(word[i].num > word[j].num)
                {
                	return false;
                }
        }
    }

    return whe;
}

void tracking(int k)
{
    if(k == index && promising())
    {
        count++;

        int maxi;
        int temp = 0;

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

            temp += re;

        }

        result = max(temp, result);

        return;
    }


    for(int i = 9 ; i > 9 - index ; --i)
    {
        if(visited[i] == 0)
        {
            visited[i] = 1;
            word[k].num = i;
            tracking(k+1);
            visited[i] = 0;
        }
    }
}


int main()
{
    std::ios::sync_with_stdio(false);

    cin >> size;

    max_length = 0;


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

    index = 0;

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
                        word[k].len = in[i].length-j;

                    break;
                }

                if(word[k].w == '\0')
                    break;
            }

            if(!whe)
            {
                word[index].w = in[i].str[j];
                word[index].len = in[i].length-j;
                ++index;
            }
        }
    }

    tracking(0);

    cout << result;
}
