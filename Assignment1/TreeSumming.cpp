/*
 * TreeSumming.cpp
 *
 *  Created on: 2016. 3. 8.
 *      Author: Park
 */

#include<iostream>

using namespace std;

bool found;

typedef struct tree{	// Ʈ�������� ���� �� ������ ����ü

	int node;
	tree* left;
	tree* right;

}tree;

tree* make_tree()
{
	tree* binary_tree = '\0';

	char whether;	// �Է� buffer , char�� ó��

	cin >> whether;		// ( ó��

	cin.clear();	// buffer �ʱ�ȭ

	int value;

	if(cin >> value)
	{
		binary_tree = new tree;

		binary_tree -> node = value;
		binary_tree -> left = make_tree();
		binary_tree -> right = make_tree();
	}

	cin.clear();

	while(cin >> whether)
	{
		if(whether == ')')
		{
			return binary_tree;

			break;
		}
	}
}

void whether_respect(tree* binary_tree, int expect, int sum)
{
	if(binary_tree -> left == '\0' && binary_tree -> right == '\0')
	{
		sum += binary_tree -> node;

		if(expect == sum)
			found = true;
	}

	if(binary_tree -> left != '\0')
	{
		whether_respect(binary_tree -> left, expect, sum + binary_tree -> node);
	}

	if(binary_tree -> right != '\0')
	{
		whether_respect(binary_tree -> right, expect, sum + binary_tree -> node);
	}
}

int main(void)
{

	std::ios::sync_with_stdio(false);

	int expect;			// ����ϴ� sum ��

	while(cin >> expect){

		found = false;

		tree* main_tree;

		main_tree = make_tree();

		if(main_tree != '\0')
		{
			whether_respect(main_tree, expect, 0);

			if(found)
				cout << "yes" << endl;
			else
				cout << "no" << endl;
		}else
			cout << "no" << endl;
	}
}
