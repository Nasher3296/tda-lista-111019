#include "pila.h"
#include "lista.h"
/**
 * Crea una pila vacía y la devuelve.
 *
 * En caso de error devuelve NULL
 */
pila_t *pila_crear()
{
	return (pila_t *)(lista_crear());
}

/**
 * Apila un elemento en la pila.
 *
 * Devuelve la pila o NULL en caso de error.
 */
pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	return (pila_t *)lista_insertar((lista_t *)pila, elemento); //O(1)
}
/**
 * Desapila un elemento de la pila y lo devuelve.
 *
 * Devuelve NULL en caso de error.
 */
void *pila_desapilar(pila_t *pila)
{
	return lista_quitar_de_posicion((lista_t *)pila,0); //O(1)
}
/**
 * Devuelve el elemento en el tope de la pila o NULL en caso de que no exista.
 */
void *pila_tope(pila_t *pila)
{
	return lista_ultimo((lista_t *)pila);
}

size_t pila_tamanio(pila_t *pila)
{
	return lista_tamanio((lista_t *)pila);
}

bool pila_vacia(pila_t *pila)
{
	return lista_vacia((lista_t *)pila);
}

void pila_destruir(pila_t *pila)
{
	lista_destruir((lista_t *)pila);
}
