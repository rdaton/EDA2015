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
using namespace std;


TreeMap<string,int> cuenta(const List<List<string> > &unTexto)
{
TreeMap<string,int>	 resultado;

List<List<string> >::ConstIterator unIterador=unTexto.cbegin();
List<List<string> >::ConstIterator fin=unTexto.cend();

while (unIterador!=fin)
{
	List<string>::ConstIterator otroIterador=unIterador.elem().cbegin();
	List<string>::ConstIterator otroFin=unIterador.elem().cend();
	while(otroIterador!=otroFin)
	{
	if (resultado.contains(otroIterador.elem()))
				resultado[otroIterador.elem()]=resultado[otroIterador.elem()]+1;
	else
		resultado[otroIterador.elem()]=1;
	otroIterador.next();
}
unIterador.next();
}



return resultado;

}


List<List<string> > lee()
		{
	List<List<string> > unTexto;
		string unaLinea;
		while (getline(cin,unaLinea))
		{
			if (unaLinea=="") break;
			List<string> unaLineaDeTexto;
			istringstream churroPalabras(unaLinea);
			string unaPalabra;
			while (churroPalabras>>unaPalabra)
			{
				unaLineaDeTexto.push_back(unaPalabra);
			};
			unTexto.push_back(unaLineaDeTexto);
		}
return unTexto;

		}


void muestra (const TreeMap<string,int> &unArbolTexto)
{
TreeMap<string,int>::ConstIterator unIterador=unArbolTexto.cbegin();
TreeMap<string,int>::ConstIterator fin=unArbolTexto.cend();

while (unIterador!=fin)
{
	cout << unIterador.key();
	cout << " ";
	cout <<unIterador.value();
	cout <<"\n";
	unIterador.next();
};


}

int main()
{

	List<List<string> > unTexto=lee();


	TreeMap<string,int> unArbolTexto=cuenta(unTexto);

	muestra(unArbolTexto);






	return 0;

}

