/*
 * Dictionary.cpp
 *
 *  Created on: 2016. 3. 9.
 *      Author: Park
 */

#include<iostream>
#include<stdio.h>
#include<set>

using namespace std;

int main(void)
{

	std::ios::sync_with_stdio(false);

	set<string> set_str;

	char input;

	string str = "\0";

	while((input = cin.get()) != EOF){

		if(input >= 'a' && input <= 'z')			// 대문자 일 때,
		{
			str += input;
		}
		else if(input >= 'A' && input <= 'Z')		// 소문자 일 때,
		{
			input += 32;

			str += input;
		}
		else
		{
			set<string>::iterator pos;

			bool exist = false;

			for(pos = set_str.begin() ; pos != set_str.end() ; ++pos){	// 있는지 검사

				if(str.compare(*pos) == 0)
				{
					exist = true;

					break;
				}
			}

			if(!exist)		// 없다면
			{
				set_str.insert(str);
			}

			str = "\0";
		}
	}

	set<string>::iterator pos;

	int i = 0;

	set_str.erase("\0");

	for(pos = set_str.begin() ; pos != set_str.end() ; pos++){
		cout << *pos << endl;
	}
}


