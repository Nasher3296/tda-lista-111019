#include "pa2m.h"
#include <string.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void prueba_insertar_lista(){
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();
	
	pa2m_afirmar(li != NULL, "Se crea correctamente la lista");

	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");

	lista_t *li_aux = lista_insertar(li, &PRIMERO);
	pa2m_afirmar(li_aux != NULL, "Se insertó sin errores");
	li = li_aux;
	pa2m_afirmar(lista_primero(li) == &PRIMERO, "El primer elemento insertado es correcto");


	li_aux = lista_insertar(li, NULL);
	pa2m_afirmar(li_aux == NULL, "No se puede insertar un elemento nulo");

	li_aux = lista_insertar(NULL, &PRIMERO);
	pa2m_afirmar(li_aux == NULL, "No se puede insertar en una lista nula");
	li_aux = li;

	li_aux = lista_insertar_en_posicion(li,&TERCERO,10);
	pa2m_afirmar(li_aux != NULL, "Se inserta un elemento en un indice mayor al ultimo");
	li = li_aux;

	li_aux = lista_insertar_en_posicion(li,&SEGUNDO,1);
	pa2m_afirmar(li_aux != NULL, "Se inserta un nuevo elemento entre otros");
	li = li_aux;

	pa2m_afirmar(lista_ultimo(li) == &TERCERO, "El ultimo elemento es correcto");
	pa2m_afirmar(lista_tamanio(li) == 3, "Se insertaron los 3 elementos");

	pa2m_afirmar(!lista_vacia(li), "La lista tiene elementos");

}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== LISTA ========================");
	
	prueba_insertar_lista();
	return pa2m_mostrar_reporte();
}
