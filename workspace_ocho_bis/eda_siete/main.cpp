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

int buscaIn (const tLista& inB, int valor)
{
	int s=0;
	try {
	while (inB.at(s)!=valor) s++;
	}
	catch (InvalidAccessException& e) {cout << e <<"\n";};
	return s;
}
/* Algorithm: reconstruyeAux()
1) Pick an element from Preorder. Increment a Preorder Index Variable (preIndex in below code) to pick next element in next recursive call.
2) Create a new tree node tNode with the data as picked element.
3) Find the picked element’s index in Inorder. Let the index be inIndex.
4) Call buildTree for elements before inIndex and make the built tree as left subtree of tNode.
5) Call buildTree for elements after inIndex and make the built tree as right subtree of tNode.
6) return tNode.
*/
tArbin reconstruyeAux ( const tLista& preA, const tLista& inB ,int inStrt, int inEnd )
{
	int r=0;
	static int preIndex = 0;
	int inIndex=0;

try{
if (inEnd==inStrt) return tArbin(tArbin(),preA.at(preIndex++),tArbin());
if (inEnd<inStrt) return tArbin();

 r = preA.at(preIndex);
 preIndex++;


 inIndex=buscaIn(inB,r);
 }

catch (InvalidAccessException& e) {cout << e <<"\n";};

tArbin hIz=reconstruyeAux(preA,inB,inStrt,inIndex-1);
tArbin hDr=reconstruyeAux(preA,inB,inIndex+1,inEnd);

return tArbin(hIz,r,hDr);




}

tArbin reconstruye(const tLista& preA, const tLista& inB, bool& error)
{

	tArbin unArbol;
	error=(preA.size()!=inB.size());
	if (error) return unArbol;

	unArbol=reconstruyeAux(preA,inB,0,preA.size()-1);


return unArbol;
}

bool mostrar (const tArbin& a)
{
	//saco lista de nodos
	tLista unaLista=a.postorden();

	//si arbol vacío
	if (unaLista.empty()) return true;

	tLista::ConstIterator unIterador=unaLista.cbegin();
	tLista::ConstIterator fin=unaLista.cend();

	while(unIterador!=fin)
	{
		cout << unIterador.elem();
		unIterador.next();
		if (unIterador!=fin)
			cout <<" "; //en serio, no sé por qué debo poner esto
	}

	cout << "\n";
	return false;
}

int main ()
{
bool error=false;

List<int> a;
List<int> b;
tArbin c;
while (!error)
{
a=lee(error);


b=lee(error);
if (error) break;
c=reconstruye(a,b,error);
error=mostrar (c);
};
return 0;
}
