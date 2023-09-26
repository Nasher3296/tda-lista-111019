#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
};

struct lista_iterador {
	//y acá?
	int sarasa;
};

/**
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t *lista_crear()
{
	lista_t *li = malloc(sizeof(lista_t));

	if(!li)
		return NULL;
	
	li->nodo_inicio = NULL;
	li->nodo_final = NULL;

	return li;
}

/**
 * Inserta un elemento al final de la lista.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(!lista || !elemento) 
		return NULL;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if(!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;

	if(!lista->nodo_inicio && lista->nodo_final)
		printf("\nALERTA ROJA ESTO NO DEBERIA HABER PASADO XD\n");

	if(!lista->nodo_inicio) //No puede tener nodo_final == NULL si nodo_inicio == NULL.
		lista->nodo_inicio = nuevo_nodo;
	else
		lista->nodo_final->siguiente = nuevo_nodo;
	

	lista->nodo_final = nuevo_nodo;


	return lista;
}
/*
 *Busca el nodo anterior al numero n. En caso de no existir retorna NULL
*/
nodo_t *buscar_nodo_anterior_n(nodo_t *nodo_actual, int n)
{
	if(!nodo_actual|| n <= 0)
		return NULL;

	if(n == 1)
		return nodo_actual;
	
	return	nodo_actual->siguiente ? 
			buscar_nodo_anterior_n(nodo_actual->siguiente, --n) :
			NULL;
}

lista_t *lista_insertar_despues(lista_t *lista, nodo_t *nodo_anterior, void *elemento)
{
	if(!lista || !nodo_anterior || !elemento) //Si elemento es null quiza deberia retornar la lista(?
		return NULL;

	if(!lista->nodo_inicio)
		return lista_insertar(lista, elemento);

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if(!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nuevo_nodo;

	if(!nuevo_nodo->siguiente)
		lista->nodo_final = nuevo_nodo;

	return lista;
}

/**
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(!lista || !elemento) //Entiendo que posicion < 0 se considera como posicion que no existe y no como error
		return NULL;


	nodo_t *nodo_anterior = buscar_nodo_anterior_n(lista->nodo_inicio, posicion);

	if(!nodo_anterior)
		return lista_insertar(lista, elemento);

	return lista_insertar_despues(lista, nodo_anterior, elemento);


}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

/**
 * Devuelve el primer elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_primero(lista_t *lista)
{
	return lista != NULL && lista->nodo_inicio != NULL ? lista->nodo_inicio->elemento : NULL;
}

/**
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_ultimo(lista_t *lista)
{
	return lista != NULL && lista->nodo_final != NULL ? lista->nodo_final->elemento : NULL;
}

/**
 * Devuelve true si la lista está vacía (o no existe) o false en caso contrario.
 */
bool lista_vacia(lista_t *lista)
{
	return lista == NULL || lista ->nodo_inicio == NULL;
}

size_t lista_tamanio(lista_t *lista)
{
	return lista ? lista->tamanio : NULL;
}

void lista_destruir(lista_t *lista)
{
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
