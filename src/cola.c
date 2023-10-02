#include "cola.h"
#include "lista.h"

/**
 * Crea una cola vacía y la devuelve.
 *
 * En caso de error devuelve NULL
 */
cola_t *cola_crear()
{
	return (cola_t *)(lista_crear());
}

/**
 * Acola un elemento en la cola.
 *
 * Devuelve la cola o NULL en caso de error.
 */
cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	return (cola_t *)lista_insertar((lista_t *)cola, elemento); //O(1)
}
/**
 * Desacola un elemento de la cola y lo devuelve.
 *
 * Devuelve NULL en caso de error.
 */
void *cola_desencolar(cola_t *cola)
{
	return lista_quitar_de_posicion((lista_t *)cola, 0); //O(1)
}
/**
 * Devuelve el elemento en el tope de la cola o NULL en caso de que no exista.
 */
void *cola_frente(cola_t *cola)
{
	return lista_primero((lista_t *)cola);
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((lista_t *)cola);
}

bool cola_vacia(cola_t *cola)
{
	return lista_vacia((lista_t *)cola);
}

void cola_destruir(cola_t *cola)
{
	lista_destruir((lista_t *)cola);
}
