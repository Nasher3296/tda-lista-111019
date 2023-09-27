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

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) == &PRIMERO, "El primer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) == &SEGUNDO, "El segundo elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) == &TERCERO, "El tercer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 3) == NULL, "Null si buscamos fuera del rango");

	li_aux = lista_insertar_en_posicion(li,&TERCERO,0);
	pa2m_afirmar(li_aux != NULL, "Se inserta un nuevo elemento al principio");
	li = li_aux;

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) != &PRIMERO, "El primer elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) != &SEGUNDO, "El segundo elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) != &TERCERO, "El tercer elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 3) == &TERCERO, "El llamado TERCERO ahora esta en la 4ta pos");
	
}

void prueba_insertar_entre(){
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();
	
	pa2m_afirmar(li != NULL, "Se crea correctamente la lista");
	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");
	pa2m_afirmar(lista_insertar_en_posicion(li, &TERCERO, 10) != NULL && lista_elemento_en_posicion(li, 0) == &TERCERO, "Insercion correcta");
	pa2m_afirmar(lista_insertar_en_posicion(li, &PRIMERO, 0) != NULL && lista_elemento_en_posicion(li, 0) == &PRIMERO, "Insercion correcta");
	pa2m_afirmar(lista_insertar_en_posicion(li, &SEGUNDO, 1) != NULL && lista_elemento_en_posicion(li, 1) == &SEGUNDO, "Insercion correcta");

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) == &PRIMERO, "El primer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) == &SEGUNDO, "El segundo elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) == &TERCERO, "El tercer elemento es correcto");
	
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== LISTA ========================");
	
	// prueba_insertar_lista();
	prueba_insertar_entre();
	return pa2m_mostrar_reporte();
}
