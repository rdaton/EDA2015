/*
 * main.cpp
 *
 *  Created on: 10/04/2015
 *      Author: barfelix
 */
# include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Queue.h"
#include "List.h"
using namespace std ;

typedef List<int> tLista;


int dameMax (int a,int b)
{
	if (a>b) return a;
	else return b;
}
void resuelve (const tLista& a, tLista& b, int n)
{
//int punteros [1000000];
int max=a.at(0);
/*for (int i=0; i<n; i++)
{
max=dameMax(max,a.at(i));
if (i%n==0) punteros[i div n]=max;
}*/




}


int main ()
{
	tLista unaLista;
	tLista otraLista;
	int num=0;
	int total_sobres=0;
	int sobres_eleg=0;
	cin >> total_sobres;
	cin >> sobres_eleg;
	if  ( (total_sobres<=0) || (sobres_eleg<=0) || (total_sobres<sobres_eleg)) return -1;
	for (int i=0;i<total_sobres;i++)
	{

		cin>>num;
		if (num<=0) return -1;
	    unaLista.push_back(num);
	    }

	resuelve (unaLista,otraLista,sobres_eleg);
	return 0;

}
