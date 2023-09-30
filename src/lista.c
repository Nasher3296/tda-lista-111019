#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t tamanio;
};

struct lista_iterador {
	lista_t *lista;
	nodo_t *actual;
};

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

nodo_t *nuevo_nodo_cargado(void *elemento, nodo_t *siguiente)
{
	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if (!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = siguiente;
	return nuevo_nodo;
}

lista_t *insertar_primer_lugar(lista_t *li, void *elemento)
{
	if (!li)
		return NULL;

	nodo_t *nuevo_nodo = nuevo_nodo_cargado(elemento, li->nodo_inicio);

	if (!nuevo_nodo)
		return NULL;

	if (!li->nodo_final)
		li->nodo_final = nuevo_nodo;

	li->nodo_inicio = nuevo_nodo;
	li->tamanio++;

	return li;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	if (!lista->nodo_inicio)
		return insertar_primer_lugar(lista, elemento);

	nodo_t *nuevo_nodo = nuevo_nodo_cargado(elemento, NULL);

	if (!nuevo_nodo)
		return NULL;

	lista->nodo_final->siguiente = nuevo_nodo;
	lista->nodo_final = nuevo_nodo;
	lista->tamanio++;

	return lista;
}

lista_t *insertar_entre(lista_t *li, nodo_t *nodo_anterior, void *elemento)
{
	if (!li || !nodo_anterior)
		return NULL;

	nodo_t *nuevo_nodo =
		nuevo_nodo_cargado(elemento, nodo_anterior->siguiente);

	if (!nuevo_nodo)
		return NULL;

	nodo_anterior->siguiente = nuevo_nodo;
	li->tamanio++;

	return li;
}

nodo_t *nodo_anterior_a_n(lista_t *li, size_t posicion)
{
	if (lista_vacia(li) || posicion >= li->tamanio || !posicion)
		return NULL;

	nodo_t *nodo_anterior = li->nodo_inicio;
	size_t i = 0;
	while (++i < posicion)
		nodo_anterior = nodo_anterior->siguiente;
	return nodo_anterior;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;
	if (posicion >= lista->tamanio)
		return lista_insertar(lista, elemento);

	if (!posicion)
		return insertar_primer_lugar(lista, elemento);

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);

	return insertar_entre(lista, nodo_anterior, elemento);
}

void *quitar_primero(lista_t *li)
{
	if (lista_vacia(li))
		return NULL;

	nodo_t *nodo_eliminar = li->nodo_inicio;
	void *elemento = nodo_eliminar->elemento;

	if (li->nodo_inicio == li->nodo_final)
		li->nodo_final = NULL;

	li->nodo_inicio = nodo_eliminar->siguiente;
	li->tamanio--;
	free(nodo_eliminar);
	return elemento;
}

void *lista_quitar(lista_t *lista)
{
	if (lista_vacia(lista))
		return NULL;

	if (lista->nodo_inicio == lista->nodo_final)
		return quitar_primero(lista);

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, lista->tamanio - 1);

	if (!nodo_anterior)
		return NULL;

	void *elemento = nodo_anterior->siguiente->elemento;

	lista->tamanio--;
	nodo_anterior->siguiente = NULL;
	free(lista->nodo_final);
	lista->nodo_final = nodo_anterior;
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista))
		return NULL;

	if (!posicion)
		return quitar_primero(lista);

	if (posicion >= lista->tamanio)
		return lista_quitar(lista);

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);
	if (!nodo_anterior)
		return NULL;

	nodo_t *nodo_eliminar = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_eliminar->siguiente;
	void *elemento = nodo_eliminar->elemento;
	free(nodo_eliminar);
	lista->tamanio--;
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista_vacia(lista) || posicion >= lista->tamanio)
		return NULL;

	if (!posicion)
		return lista->nodo_inicio->elemento;

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);

	return nodo_anterior->siguiente->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (lista_vacia(lista) || !comparador)
		return NULL;
	nodo_t *nodo_actual = lista->nodo_inicio;
	while (nodo_actual && comparador(nodo_actual->elemento, contexto))
		nodo_actual = nodo_actual->siguiente;

	return nodo_actual ? nodo_actual->elemento : NULL;
}

void *lista_primero(lista_t *lista)
{
	return !(lista_vacia(lista)) ? lista->nodo_inicio->elemento : NULL;
}

void *lista_ultimo(lista_t *lista)
{
	return !(lista_vacia(lista)) ? lista->nodo_final->elemento : NULL;
}

bool lista_vacia(lista_t *lista)
{
	return !(lista && lista->nodo_inicio);
}

size_t lista_tamanio(lista_t *lista)
{
	return lista ? lista->tamanio : 0;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *nodo_pivote;

	while (nodo_actual) {
		if (funcion)
			funcion(nodo_actual->elemento);

		nodo_pivote = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
		free(nodo_pivote);
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->actual = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return iterador && iterador->actual;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!lista_iterador_tiene_siguiente(iterador))
		return false;

	iterador->actual = iterador->actual->siguiente;
	return iterador->actual;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return iterador && iterador->actual ? iterador->actual->elemento : NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista_vacia(lista) || !funcion)
		return 0;

	size_t i = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;

	while (nodo_actual && ++i && funcion(nodo_actual->elemento, contexto))
		nodo_actual = nodo_actual->siguiente;

	return i;
}
