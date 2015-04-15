/**
  @file ListaEnlazada.h

  Implementación de la clase ListaEnlazada. No es un TAD,
  sino que se utiliza en los apuntes para explicar las
  distintas estructuras de datos o contenedores.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __LISTA_ENLAZADA_H
#define __LISTA_ENLAZADA_H

#include <iostream>


template <class T>
class ListaEnlazada {
public:

	ListaEnlazada() : _prim(NULL) {}

	~ListaEnlazada() {
		libera(_prim);
		_prim = NULL;
	}


	// Para test
	void ponDelante(const T &elem) {
		_prim = insertaElem(elem, NULL, _prim);
	}

	// Para test
	void borraSegundo() {
		borraElem(_prim->_sig);
	}

	// Para test
	void print() {

		Nodo *aux;
		Nodo *ult = NULL;
		aux = _prim;

		int elems = 0;
		std::cout << "Recorrido hacia delante: " << std::endl;
		while (aux != NULL) {
			std::cout << aux->_elem << " ";
			ult = aux;
			aux = aux->_sig;
		}

		std::cout << std::endl;

		std::cout << "Recorrido hacia atrás: " << std::endl;
		aux = ult;
		while (aux != NULL) {
			std::cout << aux->_elem << " ";
			aux = aux->_ant;
		}
		std::cout << std::endl;
		std::cout << " Numero de elementos: " << elems << std::endl;
	}


private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podrían ser NULL si el nodo es el primero
	 y/o último de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
		Nodo(Nodo *ant, const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig), _ant(ant) {}

		T _elem;
		Nodo *_sig;
		Nodo *_ant;
	};

	/**
	 Inserta un elemento entre el nodo1 y el nodo2.
	 Devuelve el puntero al nodo creado.
	 Caso general: los dos nodos existen.
	    nodo1->_sig == nodo2
	    nodo2->_ant == nodo1
	 Casos especiales: alguno de los nodos no existe
	    nodo1 == NULL y/o nodo2 == NULL
	*/
	static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
		Nodo *nuevo = new Nodo(nodo1, e, nodo2);
		if (nodo1 != NULL)
			nodo1->_sig = nuevo;
		if (nodo2 != NULL)
			nodo2->_ant = nuevo;
		return nuevo;
	}

	/**
	 Elimina el nodo n. Si el nodo tiene nodos antes
	 o después, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		assert(n != NULL);
		Nodo *ant = n->_ant;
		Nodo *sig = n->_sig;
		if (ant != NULL)
			ant->_sig = sig;
		if (sig != NULL)
			sig->_ant = ant;
		delete n;
	}

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como parámetro.
	 Se admite que el nodo sea NULL (no habrá nada que
	 liberar). En caso de pasarse un nodo válido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no sería el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al primer elemento
	Nodo *_prim;
};

#endif // __LISTA_ENLAZADA_H
