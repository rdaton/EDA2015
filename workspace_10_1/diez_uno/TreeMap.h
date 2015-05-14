/**
  @file TreeMap.h

  Implementaci�n din�mica del TAD Dictionary utilizando
  �rboles de b�squeda.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __TREEMAP_H
#define __TREEMAP_H

#include "Exceptions.h"

#include "Stack.h" // Usado internamente por los iteradores

/**
 Implementaci�n din�mica del TAD Dictionary utilizando 
 �rboles de b�squeda (no auto-balanceados).

 Las operaciones son:

 - TreeMapVacio: operaci�n generadora que construye
 un �rbol de b�squeda vac�o.

 - Insert(clave, valor): generadora que a�ade una 
 nueva pareja (clave, valor) al �rbol. Si la
 clave ya estaba se sustituye el valor.

 - erase(clave): operaci�n modificadora. Elimina la
 clave del �rbol de b�squeda.  Si la clave no est�,
 la operaci�n no tiene efecto.

 - at(clave): operaci�n observadora que devuelve
 el valor asociado a una clave. Es un error preguntar
 por una clave que no existe.

 - contains(clave): operaci�n observadora. Sirve para
 averiguar si se ha introducido una clave en el
 �rbol.

 - empty(): operacion observadora que indica si
 el �rbol de b�squeda tiene alguna clave introducida.

 @author Marco Antonio G�mez Mart�n
 */
template <class Clave, class Valor>
class TreeMap {
private:
	/**
	 Clase nodo que almacena internamente la pareja (clave, valor)
	 y los punteros al hijo izquierdo y al hijo derecho.
	 */
	class Nodo {
	public:
		Nodo() : _iz(NULL), _dr(NULL) {}
		Nodo(const Clave &clave, const Valor &valor) 
			: _clave(clave), _valor(valor), _iz(NULL), _dr(NULL) {}
		Nodo(Nodo *iz, const Clave &clave, const Valor &valor, Nodo *dr)
			: _clave(clave), _valor(valor), _iz(iz), _dr(dr) {}

		Clave _clave;
		Valor _valor;
		Nodo *_iz;
		Nodo *_dr;
	};

public:

	/** Constructor; operacion EmptyTreeMap */
	TreeMap() : _ra(NULL) {
	}

	/** Destructor; elimina la estructura jer�rquica de nodos. */
	~TreeMap() {
		libera();
		_ra = NULL;
	}

	/**
	 Operaci�n generadora que a�ade una nueva clave/valor
	 a un �rbol de b�squeda.
	 @param clave Clave nueva.
	 @param valor Valor asociado a esa clave. Si la clave
	 ya se hab�a insertado previamente, sustituimos el valor
	 viejo por el nuevo.
	 */
	void insert(const Clave &clave, const Valor &valor) {
		_ra = insertaAux(clave, valor, _ra);
	}

	/**
	 Operaci�n modificadora que elimina una clave del �rbol.
	 Si la clave no exist�a la operaci�n no tiene efecto.

	   erase(elem, EmptyTreeMap) = TreeMapVacio
	   erase(e, insert(c, v, arbol)) = 
	                     inserta(c, v, erase(e, arbol)) si c != e
	   erase(e, insert(c, v, arbol)) = erase(e, arbol) si c == e

	 @param clave Clave a eliminar.
	 */
	void erase(const Clave &clave) {
		_ra = borraAux(_ra, clave);
	}

	/**
	 Operaci�n observadora que devuelve el valor asociado
	 a una clave dada.

	 at(e, insert(c, v, arbol)) = v si e == c
	 at(e, insert(c, v, arbol)) = at(e, arbol) si e != c
	 error at(EmptyTreeMap)

	 @param clave Clave por la que se pregunta.
	 */
	const Valor &at(const Clave &clave) const {
		Nodo *p = buscaAux(_ra, clave);
		if (p == NULL)
			throw EClaveErronea();

		return p->_valor;
	}

	/**
	 Operaci�n observadora que permite averiguar si una clave
	 determinada est� o no en el �rbol de b�squeda.

	 contains(e, EmptyTreeMap) = false
	 contains(e, insert(c, v, arbol)) = true si e == c
	 contains(e, insert(c, v, arbol)) = contains(e, arbol) si e != c

	 @param clave Clave por la que se pregunta.
	 @return true si el diccionario contiene un valor asociado
	 a esa clave.
	 */
	bool contains(const Clave &clave) const {
		return (buscaAux(_ra, clave) != NULL) ? true : false;
	}

	/**
	 Operaci�n observadora que devuelve si el �rbol
	 es vac�o (no contiene elementos) o no.

	 empty(EmptyTreeMap) = true
	 empty(insert(c, v, arbol)) = false
	 */
	bool empty() const {
		return _ra == NULL;
	}

	/**
	 Sobrecarga del operador [] que permite acceder
	 al valor asociado a una clave y modificarlo.
	 Si el elemento buscado no estaba, se inserta uno
	 con el valor por defecto del tipo Valor.
	 */
	Valor &operator[](const Clave &clave) {
		// Buscamos. Ser�a mejor hacerlo in-line; as� en
		// caso de no encontrarlo no hace falta buscar otra
		// vez d�nde insertar la clave.
		Nodo * ret = buscaAux(_ra, clave);
		if (ret == NULL) {
			// No est�, lo a�adimos y vemos d�nde
			// qued�. Hay formas m�s eficientes para evitar
			// recorridos por el �rbol.
			insert(clave, Valor());
			ret = buscaAux(_ra, clave);
		}

		return ret->_valor;
	}

	// //
	// ITERADOR CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	 Clase interna que implementa un iterador sobre
	 la lista que permite recorrer el �rbol pero no
	 permite modificarlo.
	 */
	class ConstIterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr!=NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est� vac�a, no quedan
				// ascendientes por visitar
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		const Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const ConstIterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const ConstIterator &other) const {
			return !(this->operator==(other));
		}

		ConstIterator &operator++() {
			next();
			return *this;
		}

		ConstIterator operator++(int) {
			ConstIterator ret(*this);
			operator++();
			return ret;
		}

	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class TreeMap;

		ConstIterator() : _act(NULL) {}
		ConstIterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		 Busca el primer elemento en inorden de
		 la estructura jer�rquica de nodos pasada
		 como par�metro; va apilando sus ascendientes
		 para poder "ir hacia atr�s" cuando sea necesario.
		 @param p Puntero a la ra�z de la subestructura.
		 */
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo *_act;

		// Ascendientes del nodo actual
		// a�n por visitar
		Stack<Nodo*> _ascendientes;
	};
	
	/**
	 Devuelve el iterador constante al principio del
	 diccionario (clave m�s peque�a).
	 @return iterador al principio del recorrido;
	 coincidir� con cend() si el diccionario est� vac�o.
	 */
	ConstIterator cbegin() const {
		return ConstIterator(_ra);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de �ste).
	 */
	ConstIterator cend() const {
		return ConstIterator(NULL);
	}

	ConstIterator find(const Clave &c) const {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			} else
				p = p->_dr;
		}
		ConstIterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}

	// //
	// ITERADOR NO CONSTANTE Y FUNCIONES RELACIONADAS
	// //

	/**
	 Clase interna que implementa un iterador sobre
	 la �rbol de b�squeda que permite recorrer la lista e incluso
	 alterar el valor de sus elementos.
	 */
	class Iterator {
	public:
		void next() {
			if (_act == NULL) throw InvalidAccessException();

			// Si hay hijo derecho, saltamos al primero
			// en inorden del hijo derecho
			if (_act->_dr!=NULL)
				_act = primeroInOrden(_act->_dr);
			else {
				// Si no, vamos al primer ascendiente
				// no visitado. Para eso consultamos
				// la pila; si ya est� vac�a, no quedan
				// ascendientes por visitar
				if (_ascendientes.empty())
					_act = NULL;
				else {
					_act = _ascendientes.top();
					_ascendientes.pop();
				}
			}
		}

		const Clave &key() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_clave;
		}

		Valor &value() const {
			if (_act == NULL) throw InvalidAccessException();
			return _act->_valor;
		}

		bool operator==(const Iterator &other) const {
			return _act == other._act;
		}

		bool operator!=(const Iterator &other) const {
			return !(this->operator==(other));
		}

		Iterator &operator++() {
			next();
			return *this;
		}

		Iterator operator++(int) {
			Iterator ret(*this);
			operator++();
			return ret;
		}


	protected:
		// Para que pueda construir objetos del
		// tipo iterador
		friend class TreeMap;

		Iterator() : _act(NULL) {}
		Iterator(Nodo *act) {
			_act = primeroInOrden(act);
		}

		/**
		 Busca el primer elemento en inorden de
		 la estructura jer�rquica de nodos pasada
		 como par�metro; va apilando sus ascendientes
		 para poder "ir hacia atr�s" cuando sea necesario.
		 @param p Puntero a la ra�z de la subestructura.
		 */
		Nodo *primeroInOrden(Nodo *p) {
			if (p == NULL)
				return NULL;

			while (p->_iz != NULL) {
				_ascendientes.push(p);
				p = p->_iz;
			}
			return p;
		}

		// Puntero al nodo actual del recorrido
		// NULL si hemos llegado al final.
		Nodo *_act;

		// Ascendientes del nodo actual
		// a�n por visitar
		Stack<Nodo*> _ascendientes;
	};
	
	/**
	 Devuelve el iterador al principio de la lista.
	 @return iterador al principio de la lista;
	 coincidir� con final() si la lista est� vac�a.
	 */
	Iterator begin() {
		return Iterator(_ra);
	}

	/**
	 @return Devuelve un iterador al final del recorrido
	 (fuera de �ste).
	 */
	Iterator end() const {
		return Iterator(NULL);
	}

	Iterator find(const Clave &c) {
		Stack<Nodo*> ascendientes;
		Nodo *p = _ra;
		while ((p != NULL) && (p->_clave != c)) {
			if (p->_clave > c) {
				ascendientes.push(p);
				p = p->_iz;
			} else
				p = p->_dr;
		}
		Iterator ret;
		ret._act = p;
		if (p != NULL)
			ret._ascendientes = ascendientes;
		return ret;
	}


	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	TreeMap(const TreeMap<Clave, Valor> &other) : _ra(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	TreeMap<Clave, Valor> &operator=(const TreeMap<Clave, Valor> &other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

protected:

	/**
	 Constructor protegido que crea un �rbol
	 a partir de una estructura jer�rquica de nodos
	 previamente creada.
	 Se utiliza en hijoIz e hijoDr.
	 */
	TreeMap(Nodo *raiz) : _ra(raiz) {
	}

	void libera() {
		libera(_ra);
	}

	void copia(const TreeMap &other) {
		_ra = copiaAux(other._ra);
	}

private:

	/**
	 Elimina todos los nodos de una estructura arb�rea
	 que comienza con el puntero ra.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar).
	 */
	static void libera(Nodo *ra) {
		if (ra != NULL) {
			libera(ra->_iz);
			libera(ra->_dr);
			delete ra;
		}
	}

	/**
	 Copia la estructura jer�rquica de nodos pasada
	 como par�metro (puntero a su raiz) y devuelve un
	 puntero a una nueva estructura jer�rquica, copia
	 de anterior (y que, por tanto, habr� que liberar).
	 */
	static Nodo *copiaAux(Nodo *ra) {
		if (ra == NULL)
			return NULL;

		return new Nodo(copiaAux(ra->_iz),
						ra->_clave, ra->_valor,
						copiaAux(ra->_dr));
	}

	/**
	 Inserta una pareja (clave, valor) en la estructura
	 jer�rquica que comienza en el puntero pasado como par�metro.
	 Ese puntero se admite que sea NULL, por lo que se crear�
	 un nuevo nodo que pasar� a ser la nueva ra�z de esa
	 estructura jer�rquica. El m�todo devuelve un puntero a la
	 ra�z de la estructura modificada. En condiciones normales
	 coincidir� con el par�metro recibido; s�lo cambiar� si
	 la estructura era vac�a.
	 @param clave Clave a insertar. Si ya aparec�a en la
	 estructura de nodos, se sobreescribe el valor.
	 @param valor Valor a insertar.
	 @param p Puntero al nodo ra�z donde insertar la pareja.
	 @return Nueva ra�z (o p si no cambia).
	 */
	static Nodo *insertaAux(const Clave &clave, const Valor &valor, Nodo *p) {

		if (p == NULL) {
			return new Nodo(clave, valor);
		} else if (p->_clave == clave) {
			p->_valor = valor;
			return p;
		} else if (clave < p->_clave) {
			p->_iz = insertaAux(clave, valor, p->_iz);
			return p;
		} else { // (clave > p->_clave)
			p->_dr = insertaAux(clave, valor, p->_dr);
			return p;
		}
	}

	/**
	 Busca una clave en la estructura jer�rquica de
	 nodos cuya ra�z se pasa como par�metro, y devuelve
	 el nodo en la que se encuentra (o NULL si no est�).
	 @param p Puntero a la ra�z de la estructura de nodos
	 @param clave Clave a buscar
	 */
	static Nodo *buscaAux(Nodo *p, const Clave &clave) {
		if (p == NULL)
			return NULL;

		if (p->_clave == clave)
			return p;

		if (clave < p->_clave)
			return buscaAux(p->_iz, clave);
		else
			return buscaAux(p->_dr, clave);
	}

	/**
	 Elimina (si existe) la clave/valor de la estructura jer�rquica
	 de nodos apuntada por p. Si la clave aparec�a en la propia ra�z,
	 �sta cambiar�, por lo que se devuelve la nueva ra�z. Si no cambia
	 se devuelve p.

	 @param p Ra�z de la estructura jer�rquica donde borrar la clave.
	 @param clave Clave a borrar.
	 @return Nueva ra�z de la estructura, tras el borrado. Si la ra�z
	 no cambia, se devuelve el propio p.
	*/
	static Nodo *borraAux(Nodo *p, const Clave &clave) {

		if (p == NULL)
			return NULL;

		if (clave == p->_clave) {
			return borraRaiz(p);
		} else if (clave < p->_clave) {
			p->_iz = borraAux(p->_iz, clave);
			return p;
		} else { // clave > p->_clave
			p->_dr = borraAux(p->_dr, clave);
			return p;
		}
	}

	/**
	 Borra la ra�z de la estructura jer�rquica de nodos
	 y devuelve el puntero a la nueva ra�z que garantiza
	 que la estructura sigue siendo v�lida para un �rbol de
	 b�squeda (claves ordenadas).
	 */
	static Nodo *borraRaiz(Nodo *p) {

		Nodo *aux;

		// Si no hay hijo izquierdo, la ra�z pasa a ser
		// el hijo derecho
		if (p->_iz == NULL) {
			aux = p->_dr;
			delete p;
			return aux;
		} else
		// Si no hay hijo derecho, la ra�z pasa a ser
		// el hijo izquierdo
		if (p->_dr == NULL) {
			aux = p->_iz;
			delete p;
			return aux;
		} else {
		// Convertimos el elemento m�s peque�o del hijo derecho
		// en la ra�z.
			return mueveMinYBorra(p);
		}
	}

	/**
	 M�todo auxiliar para el borrado; recibe un puntero a la
	 ra�z a borrar. Busca el elemento m�s peque�o del hijo derecho
	 que se convertir� en la ra�z (que devolver�), borra la antigua
	 ra�z (p) y "cose" todos los punteros, de forma que ahora:

	   - El m�nimo pasa a ser la ra�z, cuyo hijo izquierdo y
	     derecho eran los hijos izquierdo y derecho de la ra�z
	     antigua.
	   - El hijo izquierdo del padre del elemento m�s peque�o
	     pasa a ser el antiguo hijo derecho de ese m�nimo.
	 */
	static Nodo *mueveMinYBorra(Nodo *p) {

		// Vamos bajando hasta que encontramos el elemento
		// m�s peque�o (aquel que no tiene hijo izquierdo).
		// Vamos guardando tambi�n el padre (que ser� null
		// si el hijo derecho es directamente el elemento
		// m�s peque�o).
		Nodo *padre = NULL;
		Nodo *aux = p->_dr;
		while (aux->_iz != NULL) {
			padre = aux;
			aux = aux->_iz;
		}

		// aux apunta al elemento m�s peque�o.
		// padre apunta a su padre (si el nodo es hijo izquierdo)

		// Dos casos dependiendo de si el padre del nodo con 
		// el m�nimo es o no la ra�z a eliminar
		// (=> padre != NULL)
		if (padre != NULL) {
			padre->_iz = aux->_dr;
			aux->_iz = p->_iz;
			aux->_dr = p->_dr;
		} else {
			aux->_iz = p->_iz;
		}

		delete p;
		return aux;
	}

	/** 
	 Puntero a la ra�z de la estructura jer�rquica
	 de nodos.
	 */
	Nodo *_ra;

	//hoja 10, ejercicio 1
			/**
			 * recibe un iterador y elimina la pareja (clave,valor) del diccionario, devolviendo
			un iterador al siguiente elemento en el recorrido.
			 *
			 */
			Iterator erase(const Iterator& it)
			{
				//asumo que Iterador no es null

				//recupero clave a borrar
				Clave unaClave=it.key();

				//recupero clave siguiente (otraClave)
				it++;
				Clave otraClave=it.key();

				//le digo al árbol que borre unaClave
				erase(unaClave);

				//me creo un nuevo iterador consistente y lo recorro
				//hasta encontrar otraClave
				//y devuelvo el nuevo iterdor creado
				Iterator unIterador=this->Iterator();
				Iterator fin=this->end();

				bool enc=false;
				while (!enc && unIterador != fin)
				{
					enc=(unIterador.key()==otraClave);
					if (!enc) unIterador.next();
				}

				return unIterador;

			}
			/**
			 *   The following algorithm was invented by Colin Day and later refined
		 *   by Quentin F. Stout and Bette L. Warren: hence, DSW. It takes an
		 *   ordinary BST and transforms it into a perfectly balanced BST. A BST
		 *   is perfectly balanced if the leaves are on the same level or one
		 *   level apart. The algorithm goes as follows:
		 *
		 *   1] Using right-rotation operations, turn the tree into a linked list
		 *      (a.k.a. backbone or vine)
		 *   2] Rotate every second node of the backbone about its parent to turn
		 *      the backbone into a perfectly balanced BST. Voila!
		 *
		 **************************************************************************/

public : void balancea()
{
	 if (! this->empty()) {
	    createBackbone();// effectively: createBackbone( root)
	    createPerfectBST();//effectively: createPerfectBST( root)
	 };
}
/**
 * Time complexity: O(n)
 */
/**
 *  Node grandParent = null;
  Node parent = root;
  Node leftChild;

  while (null != parent) {
    leftChild = parent.left;
    if (null != leftChild) {
      grandParent = rotateRight(grandParent, parent, leftChild);
      parent = leftChild;
    } else {
      grandParent = parent;
      parent = parent.right;
    }
  }
 */
private : void createBackbone() {
Nodo* abuelo=NULL;
Nodo* padre=this->_ra;
Nodo* hijoIz;
while (NULL != padre) {
	hijoIz=padre->_iz;
	if (NULL!=hijoIz)
	{
		abuelo= rotateRight(abuelo, padre, hijoIz);
		padre=hijoIz;
	}
	else {
		abuelo=padre;
		padre=padre->_dr;


}
}
}
/************************************************************************
 *   Before      After
 *    Gr          Gr
 *     \           \
 *     Par         Ch
 *    /  \        /  \
 *   Ch   Z      X   Par
 *  /  \            /  \
 * X    Y          Y    Z
 ***********************************************************************/
/**private Node rotateRight(Node grandParent, Node parent, Node leftChild) {
  if (null != grandParent) {
    grandParent.right = leftChild;
  } else {
    root = leftChild;
  }
  parent.left = leftChild.right;
  leftChild.right = parent;
  return grandParent;
}
**/

private:
Nodo* rotateRight(Nodo* abuelo, Nodo* padre, Nodo* hijoIz)
{
	if (NULL != abuelo) {
		abuelo->_dr=hijoIz;
	} else {
		this->_ra=hijoIz;
	}
	padre->_iz=hijoIz->_dr;
	hijoIz->_dr=padre;
	return abuelo;

}

/**
 * Time complexity: O(n)
 */
/**
private void createPerfectBST() {
  int n = 0;
  for (Node tmp = root; null != tmp; tmp = tmp.right) {
    n++;
  }
  //m = 2^floor[lg(n+1)]-1, ie the greatest power of 2 less than n: minus 1
  int m = greatestPowerOf2LessThanN(n + 1) - 1;
  makeRotations(n - m);

  while (m > 1) {
    makeRotations(m /= 2);
  }
}
**/
private:
 void createPerfectBST() {
	int n=0;
	Nodo* tmp= this->_ra;

	while (tmp!=NULL)
	{
		n++;
		tmp=tmp->_dr;
	}
int m = greatestPowerOf2LessThanN(n+1)-1;
	makeRotations (n-m);
	while (m> 1) {
		makeRotations (m /=2);
	}

}
 /**
  * Time complexity: log(n)
  */
private: int greatestPowerOf2LessThanN(int n) {
   int x = MSB(n);//MSB
   return (1 << x);//2^x
 }

/**
 * Time complexity: log(n)
 * return the index of most significant set bit: index of
 * least significant bit is 0
 */
private: int MSB(int n) {
  int ndx = 0;
  while (1 < n) {
    n = (n >> 1);
    ndx++;
  }
  return ndx;
}



/**
 * private void makeRotations(int bound) {
  Node grandParent = null;
  Node parent = root;
  Node child = root.right;
  for (; bound > 0; bound--) {
    try {
      if (null != child) {
        rotateLeft(grandParent, parent, child);
        grandParent = child;
        parent = grandParent.right;
        child = parent.right;
      } else {
        break;
      }
    } catch (NullPointerException convenient) {
      break;
    }
  }
  }
 */

private : void makeRotations (int bound)
{
	Nodo* abuelo=NULL;
	Nodo* padre =this->_ra;
	Nodo* hijo=this->_ra->_dr;
	for(;bound>0;bound--){
		try {
			if (NULL != hijo) {
			        rotateLeft(abuelo, padre, hijo);
			        abuelo = hijo;
			        padre = abuelo->_dr;
			        hijo = padre->_dr;
			      } else {
			        break;
			      }
			}
		catch (std::exception& e) {
		      break;
		    }
}
}
/*
private void rotateLeft(Node grandParent, Node parent, Node rightChild) {
  if (null != grandParent) {
    grandParent.right = rightChild;
  } else {
    root = rightChild;
  }
  parent.right = rightChild.left;
  rightChild.left = parent;
}
*/
private: void rotateLeft(Nodo* abuelo, Nodo* padre,Nodo* hijoDr) {
	if (NULL!= abuelo)
	{
		abuelo->_dr=hijoDr;
	} else {
		this->_ra=hijoDr;
	}
	padre->_dr=hijoDr->_iz;
	hijoDr->_iz=padre;
}




};
#endif // __TREEMAP_H
