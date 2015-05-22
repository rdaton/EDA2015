/*
 * Conjunto.h
 *
 *  Created on: 21/05/2015
 *      Author: barfelix
 */
#include "bundleEDA.h"
#include <string>
#ifndef CONJUNTO_H_
#define CONJUNTO_H_
using namespace std;
class Conjunto
{

private:
HashMap<char,int> _data;



public:

Conjunto()
{
	ConjuntoVacio();
}

List<char> dameListaElementos()
{
	List <char> unaListaElementos;
	HashMap<char,int>::ConstIterator unIterador=_data.cbegin();
	HashMap<char,int>::ConstIterator fin=_data.cend();
	while(unIterador!=fin)
	{
		char unaClave=unIterador.key();
		unaListaElementos.push_back(unaClave);
		unIterador.next();
	}
	return unaListaElementos;

};

void ConjuntoVacio()
{
	_data=HashMap<char,int>();

}
void inserta(const char &unElem)
{
	_data.insert(unElem,1);


}
void borra(const char &unElem)
{
	_data.erase(unElem);

}

bool esta(const char &unElem)
{
	bool enc=_data.contains(unElem);
	return enc;
}

Conjunto _union( Conjunto  a,  Conjunto b)
{
Conjunto unConjunto;
List<char> unaLista=a.dameListaElementos();
List<char> otraLista=b.dameListaElementos();
List<char>::ConstIterator unIterador=unaLista.cbegin();
List<char>::ConstIterator unFin=unaLista.cend();
List<char>::ConstIterator otroIterador=otraLista.cbegin();
List<char>::ConstIterator otroFin=otraLista.cend();

while(unIterador!=unFin)
{
	char unaLetra=unIterador.elem();
	if (!unConjunto.esta(unaLetra))
		unConjunto.inserta(unaLetra);
	unIterador.next();
}

while(otroIterador!=otroFin)
{
	char unaLetra=otroIterador.elem();
	if(!unConjunto.esta(unaLetra))
		unConjunto.inserta(unaLetra);
	otroIterador.next();
}
return unConjunto;
}

Conjunto interseccion( Conjunto a,  Conjunto b)
{
	Conjunto unConjunto;
	List<char> unaLista=a.dameListaElementos();
	List<char>::ConstIterator unIterador=unaLista.cbegin();
	List<char>::ConstIterator unFin=unaLista.cend();
	while(unIterador!=unFin)
	{
		char unaLetra=unIterador.elem();
		if (a.esta(unaLetra)&&b.esta(unaLetra))
			unConjunto.inserta(unaLetra);
		unIterador.next();
	}
	return unConjunto;
}
// a / b
Conjunto diferencia( Conjunto a,  Conjunto b)
{
	Conjunto unConjunto;
	List<char> unaLista=a.dameListaElementos();
		List<char>::ConstIterator unIterador=unaLista.cbegin();
		List<char>::ConstIterator unFin=unaLista.cend();

		while(unIterador!=unFin)
		{
			char unaLetra=unIterador.elem();
			if (!b.esta(unaLetra))
				unConjunto.inserta(unaLetra);
			unIterador.next();
		}


		return unConjunto;
}

// Fowler/Noll/Vo (FNV) -- adaptada de http://bretmulvey.com/hash/6.html
inline unsigned int hash(string clave) {
	const unsigned int p = 16777619; // primo grande
	unsigned int hash = 2166136261;  // valor inicial
	for (unsigned int i=0; i<clave.size(); i++)
		hash = (hash ^ clave[i]) * p; // ^ es xor binario
	// mezcla final
	hash += hash << 13;
	hash ^= hash >> 7;
	hash += hash << 3;
	hash ^= hash >> 17;
	hash += hash << 5;
	return hash;
}

unsigned int hash()
{
	string unString;
	List<char> unaLista=this->dameListaElementos();
	List<char>::ConstIterator unIterador= unaLista.cbegin();
	List<char>::ConstIterator fin= unaLista.cend();

	while (unIterador!=fin)
	{
		char unaLetra=unIterador.elem();
		unString+=unaLetra;
		unIterador.next();

	}
	return hash(unString);
}





};


#endif /* CONJUNTO_H_ */
