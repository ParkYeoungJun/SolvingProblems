/*
 * Marvelous.cpp
 *
 *  Created on: 2016. 3. 8.
 *      Author: Park
 */

#include<iostream>
#include<stdio.h>

using namespace std;

int main(void){

    std::ios::sync_with_stdio(false);

	char input, before;
	int num = 0;

	while((input = cin.get()) != EOF){

		if(input >= '0' && input <= '9')
		{
			num += input - '0';
		}
		else if((input >= 'A' && input <= 'Z') || input == '*')
		{
			for(int i = 0 ; i < num ; ++i)
				cout << input;

			num = 0;
		}
		else if(input == 'b')
		{
			for(int i = 0 ; i < num ; ++i)
				cout << " ";

			num = 0;
		}
		else if(input == '!')
		{
			cout << endl;
		}
		else if(input == '\n')
		{
			cout << input;
		}

		before = input;
	}
}


