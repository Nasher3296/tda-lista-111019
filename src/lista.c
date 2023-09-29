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
	size_t tamanio; //Con esto reduzco el costo de lista_tamanio a O(1). 
};

struct lista_iterador {
	lista_t *lista;
	nodo_t *actual;
};

/**
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t *lista_crear()
{
	lista_t *li = calloc(1, sizeof(lista_t));

	if(!li)
		return NULL;
	
	li->nodo_inicio = NULL;
	li->nodo_final = NULL;
	li->tamanio = 0; //El calloc ya hace esto
	return li;
}

nodo_t *nuevo_nodo_cargado(void *elemento, nodo_t *siguiente){
	// if(!elemento)
	// 	return NULL;

	nodo_t *nuevo_nodo = calloc(1, sizeof(nodo_t));

	if(!nuevo_nodo)
		return NULL;

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = siguiente;
	return nuevo_nodo;
}

lista_t *insertar_primer_lugar(lista_t *li, void *elemento){
	if(!li)// || !elemento)
		return NULL;
	
	nodo_t *nuevo_nodo = nuevo_nodo_cargado(elemento, li->nodo_inicio);

	if(!nuevo_nodo)
		return NULL;

	if(!li->nodo_final)
		li->nodo_final = nuevo_nodo;

	li->nodo_inicio = nuevo_nodo;
	li->tamanio++;
	
	return li;
}
/**
 * Inserta un elemento al final de la lista.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */
lista_t *lista_insertar(lista_t *lista, void *elemento)
{	
	if(!lista)// || !elemento) 
		return NULL;

	if(lista->tamanio == 0)
		return insertar_primer_lugar(lista, elemento);
	
	nodo_t *nuevo_nodo = nuevo_nodo_cargado(elemento, NULL);

	if(!nuevo_nodo)
		return NULL;

	lista->nodo_final->siguiente = nuevo_nodo;
	lista->nodo_final = nuevo_nodo;
	lista->tamanio++;

	return lista;
}



lista_t *insertar_entre(lista_t *li, nodo_t *nodo_anterior, void *elemento){
	if(!li || !nodo_anterior)// || !elemento)
		return NULL;
	
	nodo_t *nuevo_nodo = nuevo_nodo_cargado(elemento, nodo_anterior->siguiente);

	if(!nuevo_nodo)
		return NULL;

	nodo_anterior->siguiente = nuevo_nodo;
	li->tamanio++;

	return li;	
}
/**
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 *
 * Devuelve NULL si no pudo insertar el elemento a causa de un error, o la lista en caso de exito.
 */

nodo_t *nodo_anterior_a_n(lista_t *li, size_t posicion){
	if(lista_vacia(li) || posicion >= li->tamanio || posicion == 0) //No hay anterior al primero
		return NULL;

	nodo_t *nodo_anterior = li->nodo_inicio;
	size_t i = 0;
	while(++i < posicion)
		nodo_anterior = nodo_anterior->siguiente;
	return nodo_anterior;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if(!lista)// || !elemento)
		return NULL;
	if(posicion >= lista->tamanio)
		return lista_insertar(lista, elemento);

	if(posicion == 0)
		return insertar_primer_lugar(lista,elemento);

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);
	
	return insertar_entre(lista, nodo_anterior, elemento);
}



void *quitar_primero(lista_t *li){
	if(lista_vacia(li))
		return NULL;
	nodo_t *nodo_eliminar = li->nodo_inicio;
	void *elemento = nodo_eliminar->elemento;

	if(li->nodo_inicio == li->nodo_final)
		li->nodo_final = NULL;
	

	li->nodo_inicio = li->nodo_inicio->siguiente;
	li->tamanio--;
	free(nodo_eliminar);
	return elemento;
}

// void imprimir_direccion_nodo(void *txt, nodo_t *n){
// 	printf("%s: %p\n",txt,(void *)n);
// }
/**
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 */
void *lista_quitar(lista_t *lista)
{
	if(lista_vacia(lista))
		return NULL;

	if(lista->tamanio == 1)
		return quitar_primero(lista);

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, lista->tamanio - 1);

	if(!nodo_anterior)
		return NULL;

	void *elemento = nodo_anterior->siguiente->elemento;

	lista->tamanio--;
	nodo_anterior->siguiente = NULL;
	free(lista->nodo_final);
	lista->nodo_final = nodo_anterior; 
	return elemento;	
}

//Esto es para mis pruebas y no deberia estar en la entrega final. Si por alguna razon entregue esto boca no va a ganar la 7ma
void interar_toda_la_lista(lista_t *li){
	if(lista_vacia(li))
		return;
	nodo_t *nodo_actual = li->nodo_inicio;
	while(nodo_actual){
		nodo_actual = nodo_actual->siguiente;
	}
}
/**
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento de la lista.
 *
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.
 *
 * Devuelve el elemento removido de la lista o NULL en caso de error.
 *
 */
void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(lista_vacia(lista))
		return NULL;

	if(posicion == 0)
		return quitar_primero(lista);

	if(posicion >= lista->tamanio)
		return lista_quitar(lista); 

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);
	if(!nodo_anterior)
		return NULL;
	
	nodo_t *nodo_eliminar = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_eliminar->siguiente;
	void *elemento = nodo_eliminar->elemento; //Guardar memoria(?
	free(nodo_eliminar);
	lista->tamanio--;
	return elemento;	
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(lista_vacia(lista) || posicion >= lista->tamanio)
		return NULL;
	
	if(posicion == 0)
		return lista->nodo_inicio->elemento;

	nodo_t *nodo_anterior = nodo_anterior_a_n(lista, posicion);
	

	return nodo_anterior->siguiente->elemento;
}

/**
 * Devuelve el primer elemento de la lista que cumple la condición
 * comparador(elemento, contexto) == 0.
 *
 * Si no existe el elemento devuelve NULL.
 */
void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if(lista_vacia(lista) || !comparador || !contexto)
		return NULL;
	
	nodo_t *nodo_actual = lista->nodo_inicio;
	while(nodo_actual && comparador(nodo_actual->elemento, contexto) != 0)
		nodo_actual = nodo_actual->siguiente;
	
	return nodo_actual->elemento;
}

/**
 * Devuelve el primer elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_primero(lista_t *lista)
{
	return !(lista_vacia(lista)) ? lista->nodo_inicio->elemento : NULL;
}

/**
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía o no existe.
 */
void *lista_ultimo(lista_t *lista)
{
	return !(lista_vacia(lista)) ? lista->nodo_final->elemento : NULL;
}

/**
 * Devuelve true si la lista está vacía (o no existe) o false en caso contrario.
 */
bool lista_vacia(lista_t *lista)
{
	return !(lista && lista ->nodo_inicio);
}

/**
 * Devuelve la cantidad de elementos almacenados en la lista.
 * Una lista que no existe no puede tener elementos.
 */
size_t lista_tamanio(lista_t *lista)
{
	return lista ? lista->tamanio : 0;
}

/**
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

/**
 * Libera la memoria reservada por la lista pero además aplica la función
 * destructora dada (si no es NULL) a cada uno de los elementos presentes en la
 * lista.
 */
void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(!lista)
		return;
	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *nodo_pivote;
	//lista_con_cada_elemento usar esto
	while(nodo_actual){
		if(funcion)
			funcion(nodo_actual->elemento);
		
		nodo_pivote = nodo_actual;
		nodo_actual = nodo_actual->siguiente;
		free(nodo_pivote);
	}
	free(lista);
}

/**
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista). 
 *
 * Al momento de la creación, el iterador queda listo para devolver el
 * primer elemento utilizando lista_iterador_elemento_actual.
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(!lista)
		return NULL;
	
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->actual = lista->nodo_inicio;

	return iterador;
}	



bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return iterador && iterador->actual;
}

/**
 * Avanza el iterador al siguiente elemento.
 * Devuelve true si pudo avanzar el iterador o false en caso de
 * que no queden elementos o en caso de error.
 *
 * Una vez llegado al último elemento, si se invoca a
 * lista_iterador_elemento_actual, el resultado siempre será NULL.
 */
bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(!lista_iterador_tiene_siguiente(iterador))
		return  false;
		
	iterador->actual = iterador->actual->siguiente;
	return iterador->actual;	
}

/**
 * Devuelve el elemento actual del iterador o NULL en caso de que no
 * exista dicho elemento o en caso de error.
 */
void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return iterador && iterador->actual ? iterador->actual->elemento : NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

/**
 * Iterador interno. Recorre la lista e invoca la funcion con cada elemento de
 * la misma como primer parámetro. Dicha función puede devolver true si se deben
 * seguir recorriendo elementos o false si se debe dejar de iterar elementos.
 *
 * El puntero contexto se pasa como segundo argumento a la función del usuario.
 *
 * La función devuelve la cantidad de elementos iterados o 0 en caso de error
 * (errores de memoria, función o lista NULL, etc).
 *
 */
size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if(lista_vacia(lista) || !funcion)
		return 0;
		
	size_t i = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;
	while(nodo_actual && funcion(nodo_actual, contexto)){
		nodo_actual = nodo_actual->siguiente;
		i++;
	}	

	return i;
}
