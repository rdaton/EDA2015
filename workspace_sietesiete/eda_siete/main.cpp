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
#include "Arbin.h"
using namespace std ;

typedef Arbin<int> tArbin ;
typedef List<int> tLista;

tLista lee (bool& error)
{
	tLista ret;
int r;
cin >> r;

	while (r!=-1)
	{
		ret.push_back(r);
		cin >> r ;
	};
error=(r==-1 && ret.size()<1);
return ret;
}



tArbin balanceaAux (tLista unaLista,int start,int end)
{
	int r=0;
	int mitad=0;
	tArbin hijoIz;
	tArbin hijoDr;
	try{
	    if (unaLista.size()==1) return tArbin(tArbin(),unaLista.cbegin().elem(),tArbin());
		if (start==end) return tArbin(tArbin(),unaLista.at(start),tArbin());
		if (end<start) return tArbin();

		 mitad= ((end+start) / 2);

		if ((mitad%2)!=0) mitad++;

		r=unaLista.at(mitad);

		  hijoIz=balanceaAux(unaLista,start,mitad-1);
		  hijoDr=balanceaAux(unaLista,mitad+1,end);
	}
			 catch (InvalidAccessException& e) {cout << e <<"\n";};
		 return tArbin(hijoIz,r,hijoDr);

}

tArbin balancea(tLista unaLista)
{


	return balanceaAux(unaLista,0,unaLista.size()-1);

}

bool mostrar (const tArbin& a)
{
	//saco lista de nodos
	tLista unaLista=a.preorden();
	tLista otraLista=a.postorden();
	//si arbol vacío
	if (unaLista.empty()) return true;

	tLista::ConstIterator unIterador=unaLista.cbegin();
	tLista::ConstIterator unFin=unaLista.cend();

	while(unIterador!=unFin)
	{
		cout << unIterador.elem();
		unIterador.next();
		if (unIterador!=unFin)
			cout <<" "; //en serio, no sé por qué debo poner esto
	}

	cout << "\n";
	tLista::ConstIterator otroIterador=otraLista.cbegin();
		tLista::ConstIterator otroFin=otraLista.cend();

		while(otroIterador!=otroFin)
		{
			cout << otroIterador.elem();
			otroIterador.next();
			if (otroIterador!=otroFin)
				cout <<" "; //en serio, no sé por qué debo poner esto
		}

	cout << "\n";
	return false;
}

int main ()
{
bool error=false;

List<int> a;
tArbin c;
while (!error)
{
a=lee(error);
if (error) break;
c=balancea(a);
mostrar (c);
cout << "\n";
};
return 0;
}
