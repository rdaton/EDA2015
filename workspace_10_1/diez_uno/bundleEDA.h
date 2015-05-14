#include <string>
#include <iosfwd>
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
class EmptyStackException : public ExcepcionTAD { public: EmptyStackException() {}; EmptyStackException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class FullStackException : public ExcepcionTAD { public: FullStackException() {}; FullStackException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class EmptyQueueException : public ExcepcionTAD { public: EmptyQueueException() {}; EmptyQueueException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class EmptyDequeException : public ExcepcionTAD { public: EmptyDequeException() {}; EmptyDequeException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class EmptyListException : public ExcepcionTAD { public: EmptyListException() {}; EmptyListException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class InvalidAccessException : public ExcepcionTAD { public: InvalidAccessException() {}; InvalidAccessException(const std::string &msg) : ExcepcionTAD(msg) {} };;
class EArbolVacio : public ExcepcionTAD { public: EArbolVacio() {}; EArbolVacio(const std::string &msg) : ExcepcionTAD(msg) {} };;
class EClaveErronea : public ExcepcionTAD { public: EClaveErronea() {}; EClaveErronea(const std::string &msg) : ExcepcionTAD(msg) {} };;
template <class T>
class Stack {
public:
 static const int TAM_INICIAL = 10;
 Stack() {
  inicia();
 }
 ~Stack() {
  libera();
 }
 void push(const T &elem) {
  _v[_numElems] = elem;
  _numElems++;
  if (_numElems == _tam)
   amplia();
 }
 void pop() {
  if (empty())
   throw EmptyStackException();
  --_numElems;
 }
 const T &top() const {
  if (empty())
   throw EmptyStackException();
  return _v[_numElems - 1];
 }
 bool empty() const {
  return _numElems == 0;
 }
 int size() const {
  return _numElems;
 }
 Stack(const Stack<T> &other) {
  copia(other);
 }
 Stack<T> &operator=(const Stack<T> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
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
 T *_v;
 unsigned int _tam;
 unsigned int _numElems;
};
template <class T>
class Queue {
public:
 Queue() : _prim(NULL), _ult(NULL), _numElems(0) {
 }
 ~Queue() {
  libera();
  _prim = _ult = NULL;
 }
 void push_back(const T &elem) {
  Nodo *nuevo = new Nodo(elem, NULL);
  if (_ult != NULL)
   _ult->_sig = nuevo;
  _ult = nuevo;
  if (_prim == NULL)
   _prim = nuevo;
  _numElems++;
 }
 void pop_front() {
  if (empty())
   throw EmptyQueueException();
  Nodo *aBorrar = _prim;
  _prim = _prim->_sig;
  delete aBorrar;
  --_numElems;
  if (_prim == NULL)
   _ult = NULL;
 }
 const T &front() const {
  if (empty())
   throw EmptyQueueException();
  return _prim->_elem;
 }
 bool empty() const {
  return _prim == NULL;
 }
 int size() const {
  return _numElems;
 }
 Queue(const Queue<T> &other) : _prim(NULL), _ult(NULL) {
  copia(other);
 }
 Queue<T> &operator=(const Queue<T> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
 bool operator==(const Queue<T> &rhs) const {
  if (_numElems != rhs._numElems)
   return false;
  Nodo *p1 = _prim;
  Nodo *p2 = rhs._prim;
  while ((p1 != NULL) && (p2 != NULL)) {
   if (p1->_elem != p2->_elem)
    return false;
   p1 = p1->_sig;
   p2 = p2->_sig;
  }
  return (p1 == NULL) && (p2 == NULL);
 }
 bool operator!=(const Queue<T> &rhs) const {
  return !(*this == rhs);
 }
protected:
 void libera() {
  libera(_prim);
 }
 void copia(const Queue &other) {
  if (other.empty()) {
   _prim = _ult = NULL;
   _numElems = 0;
  } else {
   Nodo *act = other._prim;
   Nodo *ant;
   _prim = new Nodo(act->_elem);
   ant = _prim;
   while (act->_sig != NULL) {
    act = act->_sig;
    ant->_sig = new Nodo(act->_elem);
    ant = ant->_sig;
   }
   _ult = ant;
   _numElems = other._numElems;
  }
 }
private:
 class Nodo {
 public:
  Nodo() : _sig(NULL) {}
  Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
  Nodo(const T &elem, Nodo *sig) :
      _elem(elem), _sig(sig) {}
  T _elem;
  Nodo *_sig;
 };
 static void libera(Nodo *prim) {
  while (prim != NULL) {
   Nodo *aux = prim;
   prim = prim->_sig;
   delete aux;
  }
 }
 Nodo *_prim;
 Nodo *_ult;
 int _numElems;
};
#include <cassert>
template <class T>
class Deque {
public:
 Deque() {
  _fantasma = new Nodo();
  _fantasma->_sig = _fantasma;
  _fantasma->_ant = _fantasma;
  _numElems = 0;
 }
 ~Deque() {
  libera();
 }
 void push_back(const T &e) {
  insertaElem(e, _fantasma->_ant, _fantasma);
  _numElems++;
 }
 const T &front() const {
  if (empty())
   throw EmptyDequeException();
  return _fantasma->_sig->_elem;
 }
 void pop_front() {
  if (empty())
   throw EmptyDequeException();
  borraElem(_fantasma->_sig);
  --_numElems;
 }
 void push_front(const T &e) {
  insertaElem(e, _fantasma, _fantasma->_sig);
  ++_numElems;
 }
 const T &back() const {
  if (empty())
   throw EmptyDequeException();
  return _fantasma->_ant->_elem;
 }
 void pop_back() {
  if (empty())
   throw EmptyDequeException();
  borraElem(_fantasma->_ant);
  --_numElems;
 }
 bool empty() const {
  return _fantasma->_sig == _fantasma;
 }
 int size() const {
  return _numElems;
 }
 Deque(const Deque<T> &other) : _fantasma(NULL) {
  copia(other);
 }
 Deque<T> &operator=(const Deque<T> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
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
  _fantasma->_ant->_sig = NULL;
  _fantasma->_ant = NULL;
  libera(_fantasma);
  _fantasma = NULL;
 }
 void copia(const Deque<T> &other) {
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
 static Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
  Nodo *nuevo = new Nodo(nodo1, e, nodo2);
  if (nodo1 != NULL)
   nodo1->_sig = nuevo;
  if (nodo2 != NULL)
   nodo2->_ant = nuevo;
  return nuevo;
 }
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
 Nodo *_fantasma;
 unsigned int _numElems;
};
#include <cassert>
template <class T>
class List {
private:
 class Nodo {
 public:
  Nodo() : _sig(NULL), _ant(NULL) {}
  Nodo(const T &elem) : _elem(elem), _sig(NULL), _ant(NULL) {}
  Nodo(Nodo *ant, const T &elem, Nodo *sig) :
      _elem(elem), _sig(sig), _ant(ant) {}
  T _elem;
  Nodo *_sig;
  Nodo *_ant;
 };
public:
 List() : _prim(NULL), _ult(NULL), _numElems(0) {}
 ~List() {
  libera();
 }
 void push_front(const T &elem) {
  _prim = insertaElem(elem, NULL, _prim);
  if (_ult == NULL)
   _ult = _prim;
 }
 void push_back(const T &elem) {
  _ult = insertaElem(elem, _ult, NULL);
  if (_prim == NULL)
   _prim = _ult;
 }
 const T &front() const {
  if (empty())
   throw EmptyListException();
  return _prim->_elem;
 }
 const T &back() const {
  if (empty())
   throw EmptyListException();
  return _ult->_elem;
 }
 void pop_front() {
  if (empty())
   throw EmptyListException();
  Nodo *aBorrar = _prim;
  _prim = _prim->_sig;
  borraElem(aBorrar);
  if (_prim == NULL)
   _ult = NULL;
 }
 void pop_back() {
  if (empty())
   throw EmptyListException();
  Nodo *aBorrar = _ult;
  _ult = _ult->_ant;
  borraElem(aBorrar);
  if (_ult == NULL)
   _prim = NULL;
 }
 bool empty() const {
  return _prim == NULL;
 }
 unsigned int size() const {
  return _numElems;
 }
 const T &at(unsigned int idx) const {
  if (idx >= _numElems)
   throw InvalidAccessException();
  Nodo *aux = _prim;
  for (int i = 0; i < idx; ++i)
   aux = aux->_sig;
  return aux->_elem;
 }
 class ConstIterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   _act = _act->_sig;
  }
  const T &elem() const {
   if (_act == NULL) throw InvalidAccessException();
   return _act->_elem;
  }
  bool operator==(const ConstIterator &other) const {
   return _act == other._act;
  }
  bool operator!=(const ConstIterator &other) const {
   return !(this->operator==(other));
  }
  const T& operator*() const {
   return elem();
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
  friend class List;
  ConstIterator() : _act(NULL) {}
  ConstIterator(Nodo *act) : _act(act) {}
  Nodo *_act;
 };
 class Iterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   _act = _act->_sig;
  }
  const T &elem() const {
   if (_act == NULL) throw InvalidAccessException();
   return _act->_elem;
  }
  void set(const T &elem) const {
   if (_act == NULL) throw InvalidAccessException();
   _act->_elem = elem;
  }
  bool operator==(const Iterator &other) const {
   return _act == other._act;
  }
  bool operator!=(const Iterator &other) const {
   return !(this->operator==(other));
  }
  const T& operator*() const {
   return elem();
  }
  T& operator*() {
   if (_act == NULL) throw InvalidAccessException();
   return _act->_elem;
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
  friend class List;
  Iterator() : _act(NULL) {}
  Iterator(Nodo *act) : _act(act) {}
  Nodo *_act;
 };
 ConstIterator cbegin() const {
  return ConstIterator(_prim);
 }
 ConstIterator cend() const {
  return ConstIterator(NULL);
 }
 Iterator begin() {
  return Iterator(_prim);
 }
 Iterator end() const {
  return Iterator(NULL);
 }
 Iterator erase(const Iterator &it) {
  if (it._act == NULL)
   throw InvalidAccessException();
  if (it._act == _prim) {
   pop_front();
   return Iterator(_prim);
  } else if (it._act == _ult) {
   pop_back();
   return Iterator(NULL);
  } else {
   Nodo *sig = it._act->_sig;
   borraElem(it._act);
   return Iterator(sig);
  }
 }
 void insert(const T &elem, const Iterator &it) {
  if (_prim == it._act) {
   push_front(elem);
  } else
  if (it._act == NULL) {
   push_back(elem);
  }
  else {
   insertaElem(elem, it._act->_ant, it._act);
  }
 }
 List(const List<T> &other) : _prim(NULL), _ult(NULL) {
  copia(other);
 }
 List<T> &operator=(const List<T> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
 bool operator==(const List<T> &rhs) const {
  if (_numElems != rhs._numElems)
   return false;
  Nodo *p1 = _prim;
  Nodo *p2 = rhs._prim;
  while ((p1 != NULL) && (p2 != NULL)) {
   if (p1->_elem != p2->_elem)
    return false;
   p1 = p1->_sig;
   p2 = p2->_sig;
  }
  return (p1 == NULL) && (p2 == NULL);
 }
 bool operator!=(const List<T> &rhs) const {
  return !(*this == rhs);
 }
protected:
 void libera() {
  libera(_prim);
  _prim = NULL;
  _ult = NULL;
 }
 void copia(const List<T> &other) {
  _prim = 0;
  _numElems = 0;
  Nodo *act = other._prim;
  while (act != NULL) {
   push_back(act->_elem);
   act = act->_sig;
  }
 }
private:
 Nodo *insertaElem(const T &e, Nodo *nodo1, Nodo *nodo2) {
  Nodo *nuevo = new Nodo(nodo1, e, nodo2);
  if (nodo1 != NULL)
   nodo1->_sig = nuevo;
  if (nodo2 != NULL)
   nodo2->_ant = nuevo;
  _numElems ++;
  return nuevo;
 }
 void borraElem(Nodo *n) {
  assert(n != NULL);
  Nodo *ant = n->_ant;
  Nodo *sig = n->_sig;
  if (ant != NULL)
   ant->_sig = sig;
  if (sig != NULL)
   sig->_ant = ant;
  _numElems --;
  delete n;
 }
 static void libera(Nodo *prim) {
  assert(!prim || !prim->_ant);
  while (prim != NULL) {
   Nodo *aux = prim;
   prim = prim->_sig;
   delete aux;
  }
 }
 Nodo *_prim, *_ult;
 unsigned int _numElems;
};
template <class T>
class Arbin {
public:
 Arbin() : _ra(NULL) {
 }
 Arbin(const Arbin &iz, const T &elem, const Arbin &dr) :
  _ra(new Nodo(iz._ra, elem, dr._ra)) {
  _ra->addRef();
 }
 Arbin(const T &elem) :
  _ra(new Nodo(NULL, elem, NULL)) {
  _ra->addRef();
 }
 ~Arbin() {
  libera();
  _ra = NULL;
 }
 const T &raiz() const {
  if (esVacio())
   throw EArbolVacio();
  return _ra->_elem;
 }
 Arbin hijoIz() const {
  if (esVacio())
   throw EArbolVacio();
  return Arbin(_ra->_iz);
 }
 Arbin hijoDr() const {
  if (esVacio())
   throw EArbolVacio();
  return Arbin(_ra->_dr);
 }
 bool esVacio() const {
  return _ra == NULL;
 }
 List<T> preorden() const {
  List<T> ret;
  preordenAcu(_ra, ret);
  return ret;
 }
 List<T> inorden() const {
  List<T> ret;
  inordenAcu(_ra, ret);
  return ret;
 }
 List<T> postorden() const {
  List<T> ret;
  postordenAcu(_ra, ret);
  return ret;
 }
 List<T> niveles() const {
  if (esVacio())
   return List<T>();
  List<T> ret;
  Queue<Nodo*> porProcesar;
  porProcesar.push_back(_ra);
  while (!porProcesar.empty()) {
   Nodo *visita = porProcesar.front();
   porProcesar.pop_front();
   ret.push_back(visita->_elem);
   if (visita->_iz!=NULL)
    porProcesar.push_back(visita->_iz);
   if (visita->_dr!=NULL)
    porProcesar.push_back(visita->_dr);
  }
  return ret;
 }
 unsigned int numNodos() const {
  return numNodosAux(_ra);
 }
 unsigned int talla() const {
  return tallaAux(_ra);
 }
 unsigned int numHojas() const {
  return numHojasAux(_ra);
 }
 Arbin(const Arbin<T> &other) : _ra(NULL) {
  copia(other);
 }
 Arbin<T> &operator=(const Arbin<T> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
 bool operator==(const Arbin<T> &rhs) const {
  return comparaAux(_ra, rhs._ra);
 }
 bool operator!=(const Arbin<T> &rhs) const {
  return !(*this == rhs);
 }
protected:
 class Nodo {
 public:
  Nodo() : _iz(NULL), _dr(NULL), _numRefs(0) {}
  Nodo(Nodo *iz, const T &elem, Nodo *dr) :
   _elem(elem), _iz(iz), _dr(dr), _numRefs(0) {
   if (_iz != NULL)
    _iz->addRef();
   if (_dr != NULL)
    _dr->addRef();
  }
  void addRef() { assert(_numRefs >= 0); _numRefs++; }
  void remRef() { assert(_numRefs > 0); _numRefs--; }
  T _elem;
  Nodo *_iz;
  Nodo *_dr;
  int _numRefs;
 };
 Arbin(Nodo *raiz) : _ra(raiz) {
  if (_ra != NULL)
   _ra->addRef();
 }
 void libera() {
  libera(_ra);
 }
 void copia(const Arbin &other) {
  assert(this != &other);
  _ra = other._ra;
  if (_ra != NULL)
   _ra->addRef();
 }
 static void preordenAcu(Nodo *ra, List<T> &acu) {
  if (ra == NULL)
   return;
  acu.push_back(ra->_elem);
  preordenAcu(ra->_iz, acu);
  preordenAcu(ra->_dr, acu);
 }
 static void inordenAcu(Nodo *ra, List<T> &acu) {
  if (ra == NULL)
   return;
  inordenAcu(ra->_iz, acu);
  acu.push_back(ra->_elem);
  inordenAcu(ra->_dr, acu);
 }
 static void postordenAcu(Nodo *ra, List<T> &acu) {
  if (ra == NULL)
   return;
  postordenAcu(ra->_iz, acu);
  postordenAcu(ra->_dr, acu);
  acu.push_back(ra->_elem);
 }
 static unsigned int numNodosAux(Nodo *ra) {
  if (ra == NULL)
   return 0;
  return 1 + numNodosAux(ra->_iz) + numNodosAux(ra->_dr);
 }
 static unsigned int tallaAux(Nodo *ra) {
  if (ra == NULL)
   return 0;
  int tallaiz = tallaAux(ra->_iz);
  int talladr = tallaAux(ra->_dr);
  if (tallaiz > talladr)
   return 1 + tallaiz;
  else
   return 1 + talladr;
 }
 static unsigned int numHojasAux(Nodo *ra) {
  if (ra == NULL)
   return 0;
  if ((ra->_iz == NULL) && (ra->_dr == NULL))
   return 1;
  return numHojasAux(ra->_iz) + numHojasAux(ra->_dr);
 }
private:
 static void libera(Nodo *ra) {
  if (ra != NULL) {
   ra->remRef();
   if (ra->_numRefs == 0) {
    libera(ra->_iz);
    libera(ra->_dr);
    delete ra;
   }
  }
 }
 static bool comparaAux(Nodo *r1, Nodo *r2) {
  if (r1 == r2)
   return true;
  else if ((r1 == NULL) || (r2 == NULL))
   return false;
  else {
   return (r1->_elem == r2->_elem) &&
    comparaAux(r1->_iz, r2->_iz) &&
    comparaAux(r1->_dr, r2->_dr);
  }
 }
protected:
 Nodo *_ra;
};
template <class Clave, class Valor>
class TreeMap {
private:
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
 TreeMap() : _ra(NULL) {
 }
 ~TreeMap() {
  libera();
  _ra = NULL;
 }
 void insert(const Clave &clave, const Valor &valor) {
  _ra = insertaAux(clave, valor, _ra);
 }
 void erase(const Clave &clave) {
  _ra = borraAux(_ra, clave);
 }
 const Valor &at(const Clave &clave) const {
  Nodo *p = buscaAux(_ra, clave);
  if (p == NULL)
   throw EClaveErronea();
  return p->_valor;
 }
 bool contains(const Clave &clave) const {
  return (buscaAux(_ra, clave) != NULL) ? true : false;
 }
 bool empty() const {
  return _ra == NULL;
 }
 Valor &operator[](const Clave &clave) {
  Nodo * ret = buscaAux(_ra, clave);
  if (ret == NULL) {
   insert(clave, Valor());
   ret = buscaAux(_ra, clave);
  }
  return ret->_valor;
 }
 class ConstIterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   if (_act->_dr!=NULL)
    _act = primeroInOrden(_act->_dr);
   else {
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
  friend class TreeMap;
  ConstIterator() : _act(NULL) {}
  ConstIterator(Nodo *act) {
   _act = primeroInOrden(act);
  }
  Nodo *primeroInOrden(Nodo *p) {
   if (p == NULL)
    return NULL;
   while (p->_iz != NULL) {
    _ascendientes.push(p);
    p = p->_iz;
   }
   return p;
  }
  Nodo *_act;
  Stack<Nodo*> _ascendientes;
 };
 ConstIterator cbegin() const {
  return ConstIterator(_ra);
 }
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
 class Iterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   if (_act->_dr!=NULL)
    _act = primeroInOrden(_act->_dr);
   else {
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
  friend class TreeMap;
  Iterator() : _act(NULL) {}
  Iterator(Nodo *act) {
   _act = primeroInOrden(act);
  }
  Nodo *primeroInOrden(Nodo *p) {
   if (p == NULL)
    return NULL;
   while (p->_iz != NULL) {
    _ascendientes.push(p);
    p = p->_iz;
   }
   return p;
  }
  Nodo *_act;
  Stack<Nodo*> _ascendientes;
 };
 Iterator begin() {
  return Iterator(_ra);
 }
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
 TreeMap(const TreeMap<Clave, Valor> &other) : _ra(NULL) {
  copia(other);
 }
 TreeMap<Clave, Valor> &operator=(const TreeMap<Clave, Valor> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
protected:
 TreeMap(Nodo *raiz) : _ra(raiz) {
 }
 void libera() {
  libera(_ra);
 }
 void copia(const TreeMap &other) {
  _ra = copiaAux(other._ra);
 }
private:
 static void libera(Nodo *ra) {
  if (ra != NULL) {
   libera(ra->_iz);
   libera(ra->_dr);
   delete ra;
  }
 }
 static Nodo *copiaAux(Nodo *ra) {
  if (ra == NULL)
   return NULL;
  return new Nodo(copiaAux(ra->_iz),
      ra->_clave, ra->_valor,
      copiaAux(ra->_dr));
 }
 static Nodo *insertaAux(const Clave &clave, const Valor &valor, Nodo *p) {
  if (p == NULL) {
   return new Nodo(clave, valor);
  } else if (p->_clave == clave) {
   p->_valor = valor;
   return p;
  } else if (clave < p->_clave) {
   p->_iz = insertaAux(clave, valor, p->_iz);
   return p;
  } else {
   p->_dr = insertaAux(clave, valor, p->_dr);
   return p;
  }
 }
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
 static Nodo *borraAux(Nodo *p, const Clave &clave) {
  if (p == NULL)
   return NULL;
  if (clave == p->_clave) {
   return borraRaiz(p);
  } else if (clave < p->_clave) {
   p->_iz = borraAux(p->_iz, clave);
   return p;
  } else {
   p->_dr = borraAux(p->_dr, clave);
   return p;
  }
 }
 static Nodo *borraRaiz(Nodo *p) {
  Nodo *aux;
  if (p->_iz == NULL) {
   aux = p->_dr;
   delete p;
   return aux;
  } else
  if (p->_dr == NULL) {
   aux = p->_iz;
   delete p;
   return aux;
  } else {
   return mueveMinYBorra(p);
  }
 }
 static Nodo *mueveMinYBorra(Nodo *p) {
  Nodo *padre = NULL;
  Nodo *aux = p->_dr;
  while (aux->_iz != NULL) {
   padre = aux;
   aux = aux->_iz;
  }
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
 Nodo *_ra;
};
#include <string>
inline unsigned int hash(unsigned int clave) {
 return clave;
}
inline unsigned int hash(int clave) {
 return (unsigned int) clave;
}
inline unsigned int hash(char clave) {
 return clave;
}
inline unsigned int hash(std::string clave) {
 const unsigned int p = 16777619;
 unsigned int hash = 2166136261;
 for (unsigned int i=0; i<clave.size(); i++)
  hash = (hash ^ clave[i]) * p;
 hash += hash << 13;
 hash ^= hash >> 7;
 hash += hash << 3;
 hash ^= hash >> 17;
 hash += hash << 5;
 return hash;
}
template<class C>
unsigned int hash(const C &clave) {
 return clave.hash();
}
template <class Clave, class Valor>
class HashMap {
private:
 class Nodo {
 public:
  Nodo(const Clave &clave, const Valor &valor) :
  _clave(clave), _valor(valor), _sig(NULL) {};
  Nodo(const Clave &clave, const Valor &valor, Nodo *sig) :
  _clave(clave), _valor(valor), _sig(sig) {};
  Clave _clave;
  Valor _valor;
  Nodo *_sig;
 };
public:
 static const int TAM_INICIAL = 8;
 HashMap() : _v(new Nodo*[TAM_INICIAL]), _tam(TAM_INICIAL), _numElems(0) {
  for (unsigned int i=0; i<_tam; ++i) {
   _v[i] = NULL;
  }
 }
 ~HashMap() {
  libera();
 }
 void insert(const Clave &clave, const Valor &valor) {
  float ocupacion = 100 * ((float) _numElems) / _tam;
  if (ocupacion > MAX_OCUPACION)
   amplia();
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  if (nodo != NULL) {
   nodo->_valor = valor;
  } else {
   _v[ind] = new Nodo(clave, valor, _v[ind]);
   _numElems++;
  }
 }
 void erase(const Clave &clave) {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *act = _v[ind];
  Nodo *ant = NULL;
  buscaNodo(clave, act, ant);
  if (act != NULL) {
   if (ant != NULL) {
    ant->_sig = act->_sig;
   } else {
    _v[ind] = act->_sig;
   }
   delete act;
   _numElems--;
  }
 }
 const Valor &at(const Clave &clave) const {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  if (nodo == NULL)
   throw EClaveErronea();
  return nodo->_valor;
 }
 bool contains(const Clave &clave) const {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  return nodo != NULL;
 }
 bool empty() const {
  return _numElems == 0;
 }
 Valor &operator[](const Clave &clave) {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  if (nodo == NULL) {
   insert(clave, Valor());
   ind = ::hash(clave) % _tam;
   nodo = buscaNodo(clave, _v[ind]);
  }
  return nodo->_valor;
 }
 class ConstIterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   _act = _act->_sig;
   while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
    ++_ind;
    _act = _tabla->_v[_ind];
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
  friend class HashMap;
  ConstIterator(const HashMap* tabla, Nodo* act, unsigned int ind)
   : _tabla(tabla), _act(act), _ind(ind) { }
  const HashMap *_tabla;
  Nodo* _act;
  unsigned int _ind;
 };
 ConstIterator cbegin() const {
  unsigned int ind = 0;
  Nodo *act = _v[0];
  while (ind < _tam-1 && act == NULL) {
   act = _v[ind ++];
  }
  return ConstIterator(this, act, ind);
 }
 ConstIterator cend() const {
  return ConstIterator(this, NULL, 0);
 }
 ConstIterator find(const Clave &clave) const {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  return ConstIterator(this, nodo, ind);
 }
 class Iterator {
 public:
  void next() {
   if (_act == NULL) throw InvalidAccessException();
   _act = _act->_sig;
   while ((_act == NULL) && (_ind < _tabla->_tam - 1)) {
    ++_ind;
    _act = _tabla->_v[_ind];
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
  friend class HashMap;
  Iterator(const HashMap* tabla, Nodo* act, unsigned int ind)
  : _tabla(tabla), _act(act), _ind(ind) { }
  const HashMap *_tabla;
  Nodo* _act;
  unsigned int _ind;
 };
 Iterator begin() {
  unsigned int ind = 0;
  Nodo *act = _v[0];
  while (ind < _tam-1 && act == NULL) {
   act = _v[ind ++];
  }
  return Iterator(this, act, ind);
 }
 Iterator end() const {
  return Iterator(this, NULL, 0);
 }
 Iterator find(const Clave &clave) {
  unsigned int ind = ::hash(clave) % _tam;
  Nodo *nodo = buscaNodo(clave, _v[ind]);
  return Iterator(this, nodo, ind);
 }
 HashMap(const HashMap<Clave, Valor> &other) {
  copia(other);
 }
 HashMap<Clave, Valor> &operator=(const HashMap<Clave, Valor> &other) {
  if (this != &other) {
   libera();
   copia(other);
  }
  return *this;
 }
private:
 friend class Iterador;
 void libera() {
  for (unsigned int i=0; i<_tam; i++) {
   liberaNodos(_v[i]);
  }
  if (_v != NULL) {
   delete[] _v;
   _v = NULL;
  }
 }
 static void liberaNodos(Nodo *prim) {
  while (prim != NULL) {
   Nodo *aux = prim;
   prim = prim->_sig;
   delete aux;
  }
 }
 void copia(const HashMap<Clave,Valor> &other) {
  _tam = other._tam;
  _numElems = other._numElems;
  _v = new Nodo*[_tam];
  for (unsigned int i=0; i<_tam; ++i) {
   _v[i] = NULL;
   Nodo *act = other._v[i];
   while (act != NULL) {
    _v[i] = new Nodo(act->_clave, act->_valor, _v[i]);
    act = act->_sig;
   }
  }
 }
 void amplia() {
  Nodo **vAnt = _v;
  unsigned int tamAnt = _tam;
  _tam *= 2;
  _v = new Nodo*[_tam];
  for (unsigned int i=0; i<_tam; ++i)
   _v[i] = NULL;
  for (unsigned int i=0; i<tamAnt; ++i) {
   Nodo *nodo = vAnt[i];
   while (nodo != NULL) {
    Nodo *aux = nodo;
    nodo = nodo->_sig;
    unsigned int ind = ::hash(aux->_clave) % _tam;
    aux->_sig = _v[ind];
    _v[ind] = aux;
   }
  }
  delete[] vAnt;
 }
 static void buscaNodo(const Clave &clave, Nodo* &act, Nodo* &ant) {
  ant = NULL;
  bool encontrado = false;
  while ((act != NULL) && !encontrado) {
   if (act->_clave == clave) {
    encontrado = true;
   } else {
    ant = act;
    act = act->_sig;
   }
  }
 }
 static Nodo* buscaNodo(const Clave &clave, Nodo* prim) {
  Nodo *act = prim;
  Nodo *ant = NULL;
  buscaNodo(clave, act, ant);
  return act;
 }
 static const unsigned int MAX_OCUPACION = 80;
 Nodo **_v;
 unsigned int _tam;
 unsigned int _numElems;
};
