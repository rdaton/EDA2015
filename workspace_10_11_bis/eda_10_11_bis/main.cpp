/*
 * main.cpp
 *
 *  Created on: 21/05/2015
 *      Author: barfelix
 */



//List<List<string>>
#include "bundleEDA.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;


TreeMap<string,int> cuenta(const List<string>  &unTexto)
{
TreeMap<string,int>	 resultado;


	List<string>::ConstIterator otroIterador=unTexto.cbegin();
	List<string>::ConstIterator otroFin=unTexto.cend();
	while(otroIterador!=otroFin)
	{
	if (resultado.contains(otroIterador.elem()))
				resultado[otroIterador.elem()]=resultado[otroIterador.elem()]+1;
	else
		resultado[otroIterador.elem()]=1;
	otroIterador.next();

}



return resultado;

}


void  lee(int m, List<string>& a, List<string>& b )
		{


	for (int i=0;i<m;i++)
	{
	List<string>  unTexto;
		string unaLinea;
		string otraLinea;

		getline(cin,unaLinea);
		getline(cin,otraLinea);
		if (otraLinea=="CORRECTO")
			a.push_back(unaLinea);
		else if (otraLinea=="INCORRECTO")
			b.push_back(unaLinea);



		}
		}

void muestra (const TreeMap<string,int> &unArbolTexto)
{
TreeMap<string,int>::ConstIterator unIterador=unArbolTexto.cbegin();
TreeMap<string,int>::ConstIterator fin=unArbolTexto.cend();

while (unIterador!=fin)
{
	if (unIterador.value()!=0)
	{
	cout << unIterador.key();
	cout << ", ";
	cout <<unIterador.value();
	cout <<"\n";

	};
	unIterador.next();
};


}

TreeMap<string,int> resta (const TreeMap<string,int> a, const TreeMap<string,int> b )
{
	TreeMap<string,int> unReturn;
	TreeMap<string,int>::ConstIterator unIterador=a.cbegin();
	TreeMap<string,int>::ConstIterator unFin=a.cend();

	while (unIterador!=unFin)
	{
		string unaClave=unIterador.key();
		if (unReturn.contains(unaClave))
			unReturn.insert(unaClave,unIterador.value()+unReturn.find(unaClave).value());
		else
			unReturn.insert(unaClave,unIterador.value());
		unIterador.next();
	}

	TreeMap<string,int>::ConstIterator otroIterador=b.cbegin();
	TreeMap<string,int>::ConstIterator otroFin=b.cend();

	while(otroIterador!=otroFin)
	{
		string otraClave=otroIterador.key();
		if (unReturn.contains(otraClave))
			unReturn.insert(otraClave,a.find(otraClave).value()-otroIterador.value());
		else
			unReturn.insert(otraClave,-otroIterador.value());
		otroIterador.next();

	}





	return unReturn;
}


int main()
{
	int r=1;
	int i=0;
	string unaLinea;
	cin>>i;
	cin.ignore();
	while (i>0)
	{

	List<string> unTexto;
	List<string> otroTexto;


	lee(i,unTexto,otroTexto);

	TreeMap<string,int> unArbolTexto=cuenta(unTexto);
	TreeMap<string,int> otroArbolTexto=cuenta(otroTexto);



	TreeMap<string,int> tercerArbol=resta(unArbolTexto,otroArbolTexto);
	cout << "Asignatura " << r <<"\n";
	muestra(tercerArbol);
	r++;
	cin>>i;
	cin.ignore();
	};


	return 0;

}

