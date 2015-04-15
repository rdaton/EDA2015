/*
 * main.cpp
 *
 *  Created on: 06/03/2015
 *      Author: barfelix
 */
#include <iostream>
#include <stdio.h>
#include "LinkedListStack.h"
using namespace std;




void unaSuma (int r)
{
	if (r==0)
	{
		cout << "0 = 0"<<"\n";
		return;
	}
LinkedListStack<int>  unStack;
int cifra=0;
int resto=r;

while (resto>0)
{
	cifra=resto % 10;
	resto=resto /10;
	unStack.push(cifra);
}

cifra=0;
resto=0;



while (!unStack.empty())
{
	cifra=unStack.top();
	unStack.pop();
	resto+=cifra;
	if (!unStack.empty())
	cout << cifra << " + ";
	else
	cout << cifra;
};
cout << " = "<<resto <<"\n";
}
int main()
{
	int num=0;

	 cin >> num;

	while (num>-1)
	{
		unaSuma (num);
		cin >> num;
	};




	return 0;
}



