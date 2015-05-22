/*
 * main.cpp
 *
 *  Created on: 21/05/2015
 *      Author: barfelix
 */

#include "Conjunto.h"
#include <iostream>
#include <string>
using namespace std;


void lee(Conjunto& unConjunto)
{

string unaLinea;
getline(cin,unaLinea);

for (int i=0;i<unaLinea.length();i++)
{
char unaLetra=unaLinea[i];
if (!(unaLetra==' ' || unaLetra=='\b' || unaLetra=='\n')) unConjunto.inserta(unaLetra);
};
return;

}


void mostrar( Conjunto c)
{
	List<char> unaLista=c.dameListaElementos();

	for (int i=0;i<unaLista.size();i++)
	{
		char unaLetra=unaLista.at(i);

		cout << unaLetra;
		cout << " ";
	}
cout <<"\n";
}


//prueba untaria para ejercicio 7
int main()
{
Conjunto unConjunto;
Conjunto otroConjunto;
lee(unConjunto);
lee(otroConjunto);
mostrar (unConjunto);
mostrar (otroConjunto);
cout << "unión" <<"\n";
Conjunto tercerConjunto=tercerConjunto._union(unConjunto,otroConjunto);
mostrar(tercerConjunto);
cout << "diferencia" <<"\n";
Conjunto cuartoConjunto=cuartoConjunto.diferencia(unConjunto,otroConjunto);
mostrar (cuartoConjunto);
cout << "interseccion" <<"\n";
Conjunto quintoConjunto=quintoConjunto.interseccion(unConjunto,otroConjunto);
mostrar (quintoConjunto);




	return 0;
}