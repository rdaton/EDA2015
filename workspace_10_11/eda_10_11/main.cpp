/*
 * main.cpp
 *
 *  Created on: 08/05/2015
 *      Author: barfelix
 */



# include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "bundleEDA.h"
#include <string.h>
using namespace std;

typedef Arbin<char> arbolLetras;
typedef List <char> listaLetras;
typedef List<char>::ConstIterator iteradorLetras;



arbolLetras reconstruirAux(iteradorLetras& unIterador,iteradorLetras& fin )
{
//si se me ha acabado la lista, mando un arbol vacío
if (unIterador==fin) return arbolLetras();
//leo elemento del nodo actual
char unaLetra = unIterador.elem();
//avanzo en la lista
unIterador.next();
//si es espacio, devuelvo arbol vacío
if (unaLetra == ' ') return arbolLetras();
else
{
	//creo hio izquierdo (ojo, este avanza la lista)
	arbolLetras hijoIz=reconstruirAux(unIterador,fin);
	//creo hio derecho (ojo, este avanza la lista)
	arbolLetras hijoDr=reconstruirAux(unIterador,fin);
	//devuelvo arbol , con hijo izquierdo, elemento e hijo derecho
	return arbolLetras(hijoIz,unaLetra,hijoDr);
}
}

void fronteraAux(arbolLetras& unArbol, listaLetras& unaLista)
{

	if (unArbol.esVacio()) return;
	if (unArbol.hijoDr().esVacio() && unArbol.hijoIz().esVacio())
		unaLista.push_back(unArbol.raiz());
	else
	{
		arbolLetras izq=unArbol.hijoIz();
		fronteraAux(izq,unaLista);

		arbolLetras der=unArbol.hijoDr();
		fronteraAux(der,unaLista);

	}


}

listaLetras frontera(arbolLetras& unArbol)
{
	listaLetras unaLista;

	fronteraAux(unArbol,unaLista);




	return unaLista;


}

arbolLetras reconstruir (const listaLetras& unaLista)
{
	arbolLetras unArbolLetras;
	iteradorLetras inicio=unaLista.cbegin();
	iteradorLetras fin=unaLista.cend();

	unArbolLetras = reconstruirAux(inicio, fin);



	return unArbolLetras;
}


//construye el arbol y nos da su frontera
listaLetras dameListaFrontera (const string& line)
{
	arbolLetras unArbolLetras;
	listaLetras unaLista;
	listaLetras otraLista;

	//leo linea
	for (int i=0; i<line.length();i++)
	unaLista.push_back(line[i]);
	//y reconstruyo arbol
	unArbolLetras=reconstruir(unaLista);
	//genero frontera y la devuelvo
	otraLista=frontera(unArbolLetras);
	return otraLista;
}

//muestra en pantalla una lista de char
void mostrar(listaLetras& otraLista)
{
	for (int i=0; i<otraLista.size();i++)
				cout << otraLista.at(i);
			cout <<"\n";
}

int main()
{

	listaLetras otraLista;
	string line="";
	while (getline(cin,line))
	{
	if (line=="") break;
	otraLista=dameListaFrontera(line);
	mostrar(otraLista);
	};
}
