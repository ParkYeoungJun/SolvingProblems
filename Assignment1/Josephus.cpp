/*
 * Josephus.cpp
 *
 *  Created on: 2016. 3. 7.
 *      Author: Park
 */

#include<iostream>

using namespace std;

typedef struct array{

	int num;
	bool checked;
	array* link;

}array;

int main(void){

    std::ios::sync_with_stdio(false);

    int size;
    int start;
    int jump;

    cin >> size;
    cin >> start;
    cin >> jump;

    array* arr;
    arr = new array[size+1];

    for(int i = 1 ; i < size ; ++i)
    {
    	arr[i].num = i;
    	arr[i].link = &arr[i+1];
    	arr[i].checked = false;
    }

    arr[size].num = size;
    arr[size].checked = false;
    arr[size].link = &arr[1];

    cout << start << " ";

    arr[start].checked = true;

    array* tum = &arr[start];

    int count = jump;

    while(size > 1)
    {
    	tum = tum->link;

		if(!tum->checked)
			--count;

		if(count == 0)
		{
			tum->checked = true;

			--size;

			if(size > 1)
				cout << tum->num << " ";
			else
				cout << tum->num;

			count = jump;
		}
    }
}


