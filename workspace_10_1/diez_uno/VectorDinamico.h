/**
  @file VectorDinamico.h

  Implementación de la clase VectorDinamico. No es un TAD,
  sino que se utiliza en los apuntes para explicar las
  distintas estructuras de datos o contenedores.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __VECTOR_DINAMICO_H
#define __VECTOR_DINAMICO_H

#include <iostream>
#include <cassert>
#include <iterator>
#include <algorithm>

template <class T>
class VectorDinamico {
public:

	/** Tamaño inicial del vector dinámico. */
	enum { TAM_INICIAL = 10 };

	/** Constructor */
	VectorDinamico() : _v(new T[TAM_INICIAL]), _tam(TAM_INICIAL), _numElems(0) {
	}

	~VectorDinamico() {
		delete []_v;
	}

	// Para depuración
	void print() {
		std::cout << "Tam (real) vector: " << _tam << std::endl;
		std::cout << "Num elems: " << _numElems << std::endl;
		std::copy(_v, _v + _numElems, std::ostream_iterator<T>(std::cout, " "));
		std::cout << std::endl;
	}

	void add(const T &e) {
		_v[_numElems] = e;
		++_numElems;
		if (_numElems == _tam)
			amplia();
	}

protected:

	/**
	 Duplica el tamaño del vector.
	 */
	void amplia() {
		T *viejo = _v;
		_tam *= 2;
		_v = new T[_tam];

		for (int i = 0; i < _numElems; ++i)
			_v[i] = viejo[i];

		delete []viejo;
	}

	/**
	 Elimina un elemento del vector; compacta los elementos
	 al principio del vector.
	 @param pos En el intervalo 0..numElems-1.
	 */
	void quitaElem(int pos) {
		assert((0 <= pos) && (pos < _numElems));

		--_numElems;
		for (int i = pos; i < _numElems; ++i)
			_v[i] = _v[i+1];
	}

private:

	/** Puntero al array que contiene los datos. */
	T *_v;

	/** Tamaño del vector _v. */
	unsigned int _tam;

	/** Número de elementos reales guardados. */
	unsigned int _numElems;
};

#endif // __VECTOR_DINAMICO_H
