/**
  @file StaticPila.h

  Implementación del TAD Pila utilizando un
  array estático.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Antonio Sánchez Ruiz-Granados, Marco Antonio Gómez Martín, 2013
*/
#ifndef __STATIC_STACK_H
#define __STATIC_STACK_H

#include "Exceptions.h"

/**
 Implementación del TAD Pila utilizando un array estático.

 Las operaciones son:

 - EmptyStack: -> Stack. Generadora implementada en el
   constructor sin parámetros.
 - Push: Stack, Elem -> Stack. Generadora
 - pop: Stack - -> Stack. Modificadora parcial.
 - top: Stack - -> Elem. Observadora parcial.
 - empty: Stack -> Bool. Observadora.
 - size: Stack -> Entero. Observadora.

 @author Antonio Sánchez Ruiz-Granados
 @author Marco Antonio Gómez Martín
 */
template <class T>
class StaticStack {
public:
	/** Número máximo de elementos. */
	static const int TAM_MAX = 100;

	/** Constructor; operación PilaVacia */
	StaticStack() : _numElems(0) {	}

	/** Destructor. */
	~StaticStack() { }

	/**
	 Apila un elemento. Operación generadora parcial.

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
	 Desapila un elemento. Operación modificadora parcial,
	 que falla si la pila está vacía.

	 pop(Push(elem, p)) = p
	 error: pop(EmptyStack)
	*/
	void pop() {
		if (empty())
			throw EmptyStackException();
		_numElems--;
	}

	/**
	 Devuelve el elemento en la cima de la pila. Operación
	 observadora parcial, que falla si la pila está vacía.

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
	 Devuelve true si la pila no tiene ningún elemento.

	 empty(EmptyStack) = true
	 empty(Push(elem, p)) = false

	 @return true si la pila no tiene ningún elemento.
	 */
	bool empty() const {
		return _numElems == 0;
	}

	/**
	 Devuelve el número de elementos que hay en la
	 pila.
	 size(EmptyStack) = 0
	 size(Push(elem, p)) = 1 + size(p)

	 @return Número de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// MÉTODOS DE "FONTANERÍA" DE C++ QUE HACEN VERSÁTIL
	// A LA CLASE
	// //

	/** Constructor copia */
	StaticStack(const StaticStack<T> &other) {
		copia(other);
	}

	/** Operador de asignación */
	StaticStack<T> &operator=(const StaticStack<T> &other) {
		if (this != &other) 
			copia(other);
		
		return *this;
	}

	/** Operador de comparación. */
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

	/** Número de elementos almacenados en la pila. */
	unsigned int _numElems;
};

#endif // __STATIC_STACK_H
