#include "tConjunto.h"
#include <iostream>
#include <cassert>
using namespace std ;

int main() {
Conjunto<int> vacio;
Conjunto<int> c;
//tras insertar un elemento, el elemento existe
c.inserta(21);
assert(c.contiene(21));
//y se puede borrar
c.elimina(21);
//y después ya no existe
assert( ! c.contiene(21));
// y si intento borrarlo se produce un error
bool error=false;
try{
	c.elimina(12);
}
catch (ElementoInvalido& e)
{
	error=true;
}
};
