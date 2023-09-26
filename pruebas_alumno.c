#include "pa2m.h"
#include <string.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

prueba_insertar_lista(){
	char PRIMERO = 'A';
	lista_t *li = lista_crear();
	
	pa2m_afirmar(li, "Se crea correctamente la lista");

	lista_t *li_aux = lista_insertar(li, PRIMERO);
	pa2m_afirmar(li_aux, "Se insertó sin errores");
	li = li_aux;

	pa2m_afirmar(lista_primero(li) == PRIMERO, "El primer elemento insertado es correcto");

}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== LISTA ========================");
	
	prueba_insertar_lista();
	return pa2m_mostrar_reporte();
}
