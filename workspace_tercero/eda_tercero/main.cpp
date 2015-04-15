




#include <string>
#include <iosfwd>
#include <iostream>
#include <stdio.h>
using namespace std;
#include <string>
#include <iosfwd>
#ifndef __EXCEPCIONES_H
#define __EXCEPCIONES_H
/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string &msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e);

protected:
	std::string _msg;
};

inline std::ostream &operator<<(std::ostream &out, const ExcepcionTAD &e) {
	out << e._msg;
	return out;
}

// Macro para declarar las clases de tipo excepci?n
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepci?n generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EmptyStackException);

/**
 Excepci?n generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(FullStackException);

/**
 Excepci?n generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EmptyQueueException);

/**
 Excepci?n generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EmptyDequeException);

/**
 Excepci?n generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EmptyListException);

/**
 Excepci?n generada por accesos incorrectos a las listas
 (tanto a un n?mero de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(InvalidAccessException);

#endif // __EXCEPCIONES_H

/**
  @file DCola.h

  Implementaci?n del TAD doble cola, utilizando una
  lista doblemente enlazada con nodo fantasma o
  cabecera.

  Estructura de Datos y Algoritmos
  Facultad de Inform?tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G?mez Mart?n, 2012
*/
#ifndef __DCOLA_H
#define __DCOLA_H


#include <cassert>

/**
 Implementaci?n del TAD Doble Cola utilizando una lista doblemente
 enlazada circular y con nodo fantasma.

 Las operaciones son:

 - EmptyDeque: -> Deque. Generadora implementada en el
   constructor sin par?metros.
 - Push_back: Deque, Elem -> Deque. Generadora
 - push_front: Deque, Elem -> Deque. Modificadora.
 - pop_front: Deque - -> Deque. Modificadora parcial
 - pop_back: Deque - -> Deque. Modificadora parcial
 - front: Deque - -> Elem. Observadora parcial
 - back: Deque - -> Elem. Observadora parcial
 - empty: Deque -> Bool. Observadora

 @author Marco Antonio G?mez Mart?n
 */
template <class T>
class Deque {
public:

	/** Constructor; operaci?n EmptyDeque. */
	Deque() {
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;
	}

	/** Destructor; elimina la lista doblemente enlazada. */
	~Deque() {
		libera();
	}

	/**
	 A?ade un elemento por la parte de atr?s de la cola.
	 Es una operaci?n generadora.
	*/
	void push_back(const T &e) {
		insertaElem(e, _fantasma->_ant, _fantasma);
		_numElems++;
	}

	/**
	 Devuelve el primer elemento de la cola; es una operaci?n
	 observadora parcial, pues es un error preguntar por
	 el primer elemento de una doble cola vac?a.

	 primero(Push_back(elem, EmptyDeque)) = elem
	 primero(Push_back(elem, xs)) = primero(xs) si !empty(xs)
	 error: primero(EmptyDeque)
	 */
	const T &front() const {
		if (empty())
			throw EmptyDequeException();
		return _fantasma->_sig->_elem;
	}


	/**
	 Elimina el primer elemento de la doble cola.
	 Operaci?n modificadora parcial, que falla si
	 est? vac?a.

	 pop_front(Push_back(elem, EmptyDeque)) = EmptyDeque
	 pop_front(Push_back(elem, xs)) = Push_back(elem, pop_front(xs)) si !empty(xs)
	 error: pop_front(EmptyDeque)
	*/
	void pop_front() {
		if (empty())
			throw EmptyDequeException();

		borraElem(_fantasma->_sig);
		--_numElems;
	}

	/**
	 A?ade un elemento a la parte delantera de una doble cola.
	 Operaci?n modificadora.

	 push_front(elem, EmptyDeque) = Push_back(elem, EmptyDeque)
	 push_front(elem, Push_back(x, xs)) =
		Push_back(x, push_front(elem, xs))

	 @param e Elemento que se a?ade
	 */
	void push_front(const T &e) {
		insertaElem(e, _fantasma, _fantasma->_sig);
		++_numElems;
	}

	/**
	 Devuelve el ?ltimo elemento de la doble cola. Es
	 un error preguntar por el ?ltimo de una doble cola vac?a.

	 back(Push_back(x, xs)) = x
	 error: back(EmptyDeque)

	 @return ?ltimo elemento de la cola.
	 */
	const T &back() const {
		if (empty())
			throw EmptyDequeException();
		return _fantasma->_ant->_elem;
	}

	/**
	 Elimina el ?ltimo elemento de la doble cola. Es
	 un error quitar el ?ltimo de una doble cola vac?a.

	 pop_back(Push_back(x, xs)) = xs
	 error: pop_back(EmptyDeque)
	 */
	void pop_back() {
		if (empty())
			throw EmptyDequeException();

		borraElem(_fantasma->_ant);
		--_numElems;
	}

	/**
	 Operaci?n observadora para saber si una doble cola
	 tiene o no elementos.

	 empty(EmptyDeque) = true
	 empty(Push_back(x, xs)) = false

	 @return true si la doble cola no tiene elementos.
	 */
	bool empty() const {
		return _fantasma->_sig == _fantasma;
		/* return _numElems == 0; */
	}

	/**
	 Devuelve el n?mero de elementos que hay en la
	 doble cola.
	 size(EmptyDeque) = 0
	 size(Push_back(elem, p)) = 1 + size(p)

	 @return N?mero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// M?TODOS DE "FONTANER?A" DE C++ QUE HACEN VERS?TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Deque(const Deque<T> &other) : _fantasma(NULL) {
		copia(other);
	}

	/** Operador de asignaci?n */
	Deque<T> &operator=(const Deque<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci?n. */
	bool operator==(const Deque<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		Nodo *p1 = _fantasma->_sig;
		Nodo *p2 = rhs._fantasma->_sig;
		while ((p1 != _fantasma) && (p2 != rhs._fantasma)) {
			if (p1->_elem != p2->_elem)
				return false;
			p1 = p1->_sig;
			p2 = p2->_sig;
		}

		return (p1 == _fantasma) && (p2 == rhs._fantasma);
	}

	bool operator!=(const Deque<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void libera() {
		// Usamos libera(nodo), pero antes quitamos
		// la circularidad para evitar bucle
		// infinito...
		_fantasma->_ant->_sig = NULL;
		_fantasma->_ant = NULL;
		libera(_fantasma);
		_fantasma = NULL;
	}

	void copia(const Deque<T> &other) {
		// En vez de trabajar con punteros en la inserci?n,
		// usamos ponDetras.
		_fantasma = new Nodo();
		_fantasma->_sig = _fantasma;
		_fantasma->_ant = _fantasma;
		_numElems = 0;

		Nodo *act = other._fantasma->_sig;
		while (act != other._fantasma) {
			push_back(act->_elem);
			act = act->_sig;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y dos punteros, uno al nodo anterior y otro al nodo siguiente.
	 Ambos punteros podr?an ser NULL si el nodo es el primero
	 y/o ?ltimo de la lista enlazada.
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
	 o despu?s, actualiza sus punteros anterior y siguiente.
	 Caso general: hay nodos anterior y siguiente.
	 Casos especiales: algunos de los nodos (anterior o siguiente
	 a n) no existen.
	*/
	static void borraElem(Nodo *n) {
		if (n == NULL)
			return;

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
	 primer nodo se pasa como par?metro.
	 Se admite que el nodo sea NULL (no habr? nada que
	 liberar). En caso de pasarse un nodo v?lido,
	 su puntero al nodo anterior debe ser NULL (si no,
	 no ser?a el primero de la lista!).
	 */
	static void libera(Nodo *prim) {
		if (prim == NULL)
			return;

		assert(!prim || !prim->_ant);

		while (prim != NULL) {
			Nodo *aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	// Puntero al nodo fantasma
	Nodo *_fantasma;

	// N?mero de elementos
	unsigned int _numElems;
};

#endif // __DCOLA_H


/*
  Definici?n de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Inform?tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G?mez Mart?n, 2012
*/









/**
  @file Stack.h

  Implementaci?n del TAD Pila utilizando un
  vector din?mico cuyo tama?o va creciendo si
  es necesario.

  Estructura de Datos y Algoritmos
  Facultad de Inform?tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G?mez Mart?n, 2012
*/
#ifndef __STACK_H
#define __STACK_H



/**
 Implementaci?n del TAD Pila utilizando vectores din?micos.

 Las operaciones son:

 - EmptyStack: -> Stack. Generadora implementada en el
   constructor sin par?metros.
 - Push: Stack, Elem -> Stack. Generadora
 - pop: Stack - -> Stack. Modificadora parcial.
 - top: Stack - -> Elem. Observadora parcial.
 - empty: Stack -> Bool. Observadora.
 - size: Stack -> Entero. Observadora.

 @author Marco Antonio G?mez Mart?n
 */
template <class T>
class Stack {
public:

	/** Tama?o inicial del vector din?mico. */
	static const int TAM_INICIAL = 10;

	/** Constructor; operaci?n EmptyStack */
	Stack() {
		inicia();
	}

	/** Destructor; elimina el vector. */
	~Stack() {
		libera();
	}

	/**
	 Apila un elemento. Operaci?n generadora.

	 @param elem Elemento a apilar.
	*/
	void push(const T &elem) {
		_v[_numElems] = elem;
		_numElems++;
		if (_numElems == _tam)
			amplia();
	}

	/**
	 Desapila un elemento. Operaci?n modificadora parcial,
	 que falla si la pila est? vac?a.

	 pop(Push(elem, p)) = p
	 error: pop(EmptyStack)
	*/
	void pop() {
		if (empty())
			throw EmptyStackException();
		--_numElems;
	}


	/**
	 Devuelve el elemento en la cima de la pila. Operaci?n
	 observadora parcial, que falla si la pila est? vac?a.

	 top(Push(elem, p) = elem
	 error: top(EmptyStack)

	 @return Elemento en la cima de la pila.
	 */
	const T &top() const {
		if (empty())
			throw EmptyStackException();
		return _v[_numElems - 1];
	}

	/**
	 Devuelve true si la pila no tiene ning?n elemento.

	 empty(EmptyStack) = true
	 empty(Push(elem, p)) = false

	 @return true si la pila no tiene ning?n elemento.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el n?mero de elementos que hay en la
	 pila.
	 size(EmptyStack) = 0
	 size(Push(elem, p)) = 1 + size(p)

	 @return N?mero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// M?TODOS DE "FONTANER?A" DE C++ QUE HACEN VERS?TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Stack(const Stack<T> &other) {
		copia(other);
	}

	/** Operador de asignaci?n */
	Stack<T> &operator=(const Stack<T> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci?n. */
	bool operator==(const Stack<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		return true;
	}

	bool operator!=(const Stack<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void inicia() {
		_v = new T[TAM_INICIAL];
		_tam = TAM_INICIAL;
		_numElems = 0;
	}

	void libera() {
		delete []_v;
		_v = NULL;
	}

	void copia(const Stack &other) {
		_tam = other._numElems + TAM_INICIAL;
		_numElems = other._numElems;
		_v = new T[_tam];
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

	void amplia() {
		T *viejo = _v;
		_tam *= 2;
		_v = new T[_tam];

		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = viejo[i];

		delete []viejo;
	}

private:

	/** Puntero al array que contiene los datos. */
	T *_v;

	/** Tama?o del vector _v. */
	unsigned int _tam;

	/** N?mero de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __STACK_H


bool esVocal(char c)
{
	return (c=='a' || c=='o' || c=='i' || c=='u' || c=='e');
}


string decodifica (string& msg)
{
	Stack<char> unStack;
	Deque<char> unaCola;
	Stack<char> otroStack;
	string msgSeg="";
	string unMsg="";
	string msgPrim="";





//primeraFase
	int i=0;
	while (i<msg.length())
	{

		while (!esVocal (msg[i]) && i<msg.length())
			{
				unStack.push(msg[i]);
				i++;
			}

		while (!unStack.empty())
		{
			msgPrim+=unStack.top();
			unStack.pop();

		}

		if (i<msg.length())
			msgPrim+=msg[i];

		i++;


}


for (int m=msgPrim.length()-1;m>=0;m--)
unaCola.push_front(msgPrim[m]);

//segunda fase
bool flip=true;
while (!unaCola.empty() )
{
	if (flip) {
		msgSeg+=unaCola.front();
		unaCola.pop_front();
		flip=!flip;
		}
	else
	{
		msgSeg+=unaCola.back();
		unaCola.pop_back();
		flip=!flip;
	};


}



	return msgSeg;
}


bool resuelve(){




	string msg;
	getline(cin,msg);
	if (!cin)
		return false;
	cout << msg
			<< "=>"
			<<decodifica(msg)
			<<endl;

	return true;

}


int main()
{
while (resuelve()){};
	return 0;
}

