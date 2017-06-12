/*
 * Tothemax.cpp
 *
 *  Created on: 2016. 3. 26.
 *      Author: Park
 */
#include<iostream>

using namespace std;

int main(void)
{
	std::ios::sync_with_stdio(false);

	int size;
	int result = -0x7d2b7500;

	cin >> size;

	int array[100][100];

	for(int i = 0 ; i < size ; ++i)
		for(int j = 0 ; j < size ; ++j)
			cin >> array[i][j];

	for(int i = 0 ; i < size ; ++i)
	{
		int* checkSum = new int[size];

		for(int j = i ; j < size ; ++j)
		{
			int temp_max = -0x7d2b7500;
			int temp = 0;

			for(int k = 0 ; k < size ; ++k)
			{
				// checkSum = �ش� row ��
				checkSum[k] += array[j][k];

				// �ʱ� column, row������ ��, ������������ �� ������ �����̹Ƿ� ����
				temp += checkSum[k];

				if(result < temp)
					result = temp;

				// ���� ���� ����
				if(temp < 0)
					temp = 0;
			}
		}
	}
	cout << result;
}
