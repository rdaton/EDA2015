/*
 * @file tConjunto.h
 * @author manuel.freire@fdi.ucm.es
 * @date 2014-02-12
 * @brief Conjunto sencillo
 */

#ifndef TCONJUNTO_H_
#define TCONJUNTO_H_

//Excepción de Conjunto Lleno
class ConjuntoLleno {};
//Excepción de Elemento Inexistente
class ElementoInvalido{};

template < class E>
class Conjunto {
protected:
	static const int MAX = 100; /**< max  de elementos */
	int _tam;
	E _elementos[MAX]; /**< vector estatico de elementos */

public:
	/**
	 * Inicializa un conjunto vacío (constructor)
	 */
	Conjunto(){_tam=0;}

	/**
	 * Inserta un elemento en el conjunto
	 * (mutador parcial: si se llena, lanza ConjuntoLLeno).
	 * @param e elemento a insertar
	 */
	void inserta(const E &e)
	{
		if (_tam == MAX) throw  ConjuntoLleno();
		_elementos[_tam] = e;
		_tam++;
	}

	/**
	 * Borra un elemento del conjunto
	 * (mutador parcial: si no existe, lanza  ElementoInvalido)
	 */

	void elimina(const E &e)
	{
		bool esta=false;
		int i=0;
		while (i<_tam)
		{
			if(_elementos[i]==e){
				_elementos[i]=_elementos[_tam-1];
				esta=true;
				_tam--;}
			//paso el ultimo elemento en su lugar
			else i++;
		};
		if (!esta) throw ElementoInvalido();
		}

	/**
	 * Devuelve true si el elemento está contenido en el conjunto
	 * (observador)
	 */
	bool contiene (const E &e) const {
		bool esta=false;
		int i=0;
		while (i<_tam && !esta)
		{esta = (_elementos[i]==e);
		i++;
		};
		return esta;
	}


};



#endif /* TCONJUNTO_H_ */
