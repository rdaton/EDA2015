/**
  @file StaticPila.h

  Implementaci�n del TAD Pila utilizando un
  array est�tico.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Antonio S�nchez Ruiz-Granados, Marco Antonio G�mez Mart�n, 2013
*/
#ifndef __STATIC_STACK_H
#define __STATIC_STACK_H

#include "Exceptions.h"

/**
 Implementaci�n del TAD Pila utilizando un array est�tico.

 Las operaciones son:

 - EmptyStack: -> Stack. Generadora implementada en el
   constructor sin par�metros.
 - Push: Stack, Elem -> Stack. Generadora
 - pop: Stack - -> Stack. Modificadora parcial.
 - top: Stack - -> Elem. Observadora parcial.
 - empty: Stack -> Bool. Observadora.
 - size: Stack -> Entero. Observadora.

 @author Antonio S�nchez Ruiz-Granados
 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class StaticStack {
public:
	/** N�mero m�ximo de elementos. */
	static const int TAM_MAX = 100;

	/** Constructor; operaci�n PilaVacia */
	StaticStack() : _numElems(0) {	}

	/** Destructor. */
	~StaticStack() { }

	/**
	 Apila un elemento. Operaci�n generadora parcial.

	 @param elem Elemento a apilar.
	 error: push(p) cuando size(p) == TAM_MAX
	*/
	void push(const T &elem) {
		if (_numElems == TAM_MAX)
			throw FullStackException();
		
		_v[_numElems] = elem;
		_numElems++;
	}
	
	/**
	 Desapila un elemento. Operaci�n modificadora parcial,
	 que falla si la pila est� vac�a.

	 pop(Push(elem, p)) = p
	 error: pop(EmptyStack)
	*/
	void pop() {
		if (empty())
			throw EmptyStackException();
		_numElems--;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operaci�n
	 observadora parcial, que falla si la pila est� vac�a.

	 top(Push(elem, p) = elem
	 error: top(EmptyStack)

	 @return Elemento en la cima de la pila.
	 */
	const T &top() const {
		if (empty())
			throw EmptyStackException();
		return _v[_numElems-1];
	}

	/**
	 Devuelve true si la pila no tiene ning�n elemento.

	 empty(EmptyStack) = true
	 empty(Push(elem, p)) = false

	 @return true si la pila no tiene ning�n elemento.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 pila.
	 size(EmptyStack) = 0
	 size(Push(elem, p)) = 1 + size(p)

	 @return N�mero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	StaticStack(const StaticStack<T> &other) {
		copia(other);
	}

	/** Operador de asignaci�n */
	StaticStack<T> &operator=(const StaticStack<T> &other) {
		if (this != &other) 
			copia(other);
		
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const StaticStack<T> &rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		
		for (unsigned int i = 0; i < _numElems; ++i)
			if (_v[i] != rhs._v[i])
				return false;
		
		return true;
	}

	bool operator!=(const StaticStack<T> &rhs) const {
		return !(*this == rhs);
	}

protected:

	void copia(const StaticStack<T> &other) {
		_numElems = other._numElems;
		for (unsigned int i = 0; i < _numElems; ++i)
			_v[i] = other._v[i];
	}

private:

	/** Array de elementos. */
	T _v[TAM_MAX];

	/** N�mero de elementos almacenados en la pila. */
	unsigned int _numElems;
};

#endif // __STATIC_STACK_H
