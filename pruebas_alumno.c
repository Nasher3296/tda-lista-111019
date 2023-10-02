#include "pa2m.h"
#include <string.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"


void li_insertar()
{
		a2m_nuevo_grupo(
		"\n===================== Insert ordenado =====================");
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();

	pa2m_afirmar(li != NULL, "Se crea correctamente la lista");

	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");

	lista_t *li_aux = lista_insertar(li, &PRIMERO);
	pa2m_afirmar(li_aux != NULL, "Se insertó sin errores");
	li = li_aux;
	pa2m_afirmar(lista_primero(li) == &PRIMERO,
		     "El primer elemento insertado es correcto");

	li_aux = lista_insertar(li, NULL);
	pa2m_afirmar(li_aux != NULL, "Se puede insertar un elemento nulo");

	li_aux = lista_quitar(li);
	pa2m_afirmar(li_aux == NULL, "Se puede eliminar un NULL");

	li_aux = lista_insertar(NULL, &PRIMERO);
	pa2m_afirmar(li_aux == NULL, "No se puede insertar en una lista nula");
	li_aux = li;

	li_aux = lista_insertar_en_posicion(li, &TERCERO, 10);
	pa2m_afirmar(li_aux != NULL,
		     "Se inserta un elemento en un indice mayor al ultimo");
	li = li_aux;

	li_aux = lista_insertar_en_posicion(li, &SEGUNDO, 1);
	pa2m_afirmar(li_aux != NULL,
		     "Se inserta un nuevo elemento entre otros");
	li = li_aux;

	pa2m_afirmar(lista_ultimo(li) == &TERCERO,
		     "El ultimo elemento es correcto");
	pa2m_afirmar(lista_tamanio(li) == 3, "Se insertaron los 3 elementos");

	pa2m_afirmar(!lista_vacia(li), "La lista tiene elementos");

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) == &PRIMERO,
		     "El primer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) == &SEGUNDO,
		     "El segundo elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) == &TERCERO,
		     "El tercer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 3) == NULL,
		     "Null si buscamos fuera del rango");

	li_aux = lista_insertar_en_posicion(li, &TERCERO, 0);
	pa2m_afirmar(li_aux != NULL,
		     "Se inserta un nuevo elemento al principio");
	li = li_aux;

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) != &PRIMERO,
		     "El primer elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) != &SEGUNDO,
		     "El segundo elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) != &TERCERO,
		     "El tercer elemento se desplazo");
	pa2m_afirmar(lista_elemento_en_posicion(li, 3) == &TERCERO,
		     "El llamado TERCERO ahora esta en la 4ta pos");
	lista_destruir(li);
}


void li_insertar_entre()
{
	a2m_nuevo_grupo(
		"\n===================== Inserto desordenado =====================");
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();

	pa2m_afirmar(li != NULL, "Se crea correctamente la lista");
	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");
	pa2m_afirmar(lista_insertar_en_posicion(li, &TERCERO, 10) != NULL &&
			     lista_elemento_en_posicion(li, 0) == &TERCERO,
		     "Insercion correcta");
	pa2m_afirmar(lista_insertar_en_posicion(li, &PRIMERO, 0) != NULL &&
			     lista_elemento_en_posicion(li, 0) == &PRIMERO,
		     "Insercion correcta");
	pa2m_afirmar(lista_insertar_en_posicion(li, &SEGUNDO, 1) != NULL &&
			     lista_elemento_en_posicion(li, 1) == &SEGUNDO,
		     "Insercion correcta");

	pa2m_afirmar(lista_elemento_en_posicion(li, 0) == &PRIMERO,
		     "El primer elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 1) == &SEGUNDO,
		     "El segundo elemento es correcto");
	pa2m_afirmar(lista_elemento_en_posicion(li, 2) == &TERCERO,
		     "El tercer elemento es correcto");
	lista_destruir(li);
}

void li_quitar_uno()
{
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();

	lista_insertar_en_posicion(li, &TERCERO, 10);
	lista_insertar_en_posicion(li, &PRIMERO, 0);
	lista_insertar_en_posicion(li, &SEGUNDO, 1);
	void *e = lista_quitar(li);
	pa2m_afirmar(e == &TERCERO, "Elemento quitado == TERCERO");
	lista_destruir(li);
}

void li_quitar_en_fn()
{
	pa2m_nuevo_grupo(
		"\n===================== Saco ordenado con posicion =====================");
	char PRIMERO = 'A'; //0
	char SEGUNDO = 'B'; //1
	char TERCERO = 'C'; //2
	char CUARTO = 'D'; //3
	char QUINTO = 'E'; //4
	lista_t *li = lista_crear();

	lista_insertar_en_posicion(li, &PRIMERO, 0);
	lista_insertar_en_posicion(li, &SEGUNDO, 1);
	lista_insertar_en_posicion(li, &TERCERO, 3);
	lista_insertar_en_posicion(li, &CUARTO, 3);
	lista_insertar_en_posicion(li, &QUINTO, 4);
	void *a = lista_elemento_en_posicion(li, 0);
	void *b = lista_elemento_en_posicion(li, 1);
	void *c = lista_elemento_en_posicion(li, 2);
	void *d = lista_elemento_en_posicion(li, 3);
	void *e = lista_elemento_en_posicion(li, 4);

	pa2m_afirmar(lista_quitar_de_posicion(li, 4) == e, "Saco QUINTO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 3) == d, "Saco CUARTO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 2) == c, "Saco TERCERO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 1) == b, "Saco SEGUNDO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 0) == a, "Saco PRIMERO");

	pa2m_afirmar(e == &QUINTO, "e se conserva");

	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");
	pa2m_afirmar(lista_quitar_de_posicion(li, 0) == NULL,
		     "No se puede quitar de lista vacia");
	pa2m_afirmar(lista_quitar_de_posicion(li, 32) == NULL,
		     "No se puede quitar de lista vacia x2");

	lista_destruir(li);
}

void li_eliminar_desordenado()
{
	pa2m_nuevo_grupo(
		"\n===================== Saco desordenado con posicion =====================");
	char PRIMERO = 'A'; //0
	char SEGUNDO = 'B'; //1
	char TERCERO = 'C'; //2
	char CUARTO = 'D'; //3
	char QUINTO = 'E'; //4
	lista_t *li = lista_crear();

	lista_insertar_en_posicion(li, &TERCERO, 10);
	lista_insertar_en_posicion(li, &PRIMERO, 0);
	lista_insertar_en_posicion(li, &SEGUNDO, 1);
	lista_insertar_en_posicion(li, &CUARTO, 4);
	lista_insertar_en_posicion(li, &QUINTO, 42);
	void *a = lista_elemento_en_posicion(li, 0);
	void *b = lista_elemento_en_posicion(li, 1);
	void *c = lista_elemento_en_posicion(li, 2);
	void *d = lista_elemento_en_posicion(li, 3);
	void *e = lista_elemento_en_posicion(li, 4);

	pa2m_afirmar(lista_quitar_de_posicion(li, 10) == e, "Saco QUINTO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 1) == b, "Saco SEGUNDO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 0) == a, "Saco PRIMERO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 3) == d, "Saco CUARTO");
	pa2m_afirmar(lista_quitar_de_posicion(li, 1) == c, "Saco TERCERO");
	pa2m_afirmar(e == &QUINTO, "e se conserva");

	pa2m_afirmar(lista_vacia(li), "La lista esta vacia");

	lista_destruir(li);
}

int li_comparador(void *e, void *c)
{
	return e != c;
}

void li_buscar_elemento_y_demas()
{
	pa2m_nuevo_grupo(
		"\n===================== Elimino grupo, busco primero y ultimo =====================");
	char PRIMERO = 'A'; //0
	char SEGUNDO = 'B'; //1
	char TERCERO = 'C'; //2
	char CUARTO = 'D'; //3
	char QUINTO = 'E'; //4
	lista_t *li = lista_crear();

	lista_insertar_en_posicion(li, &PRIMERO, 0);
	lista_insertar_en_posicion(li, &SEGUNDO, 1);
	lista_insertar_en_posicion(li, &TERCERO, 2);
	lista_insertar_en_posicion(li, &CUARTO, 3);
	lista_insertar_en_posicion(li, &QUINTO, 4);

	pa2m_afirmar(lista_elemento_en_posicion(li,0) == &PRIMERO, "Se busca el primer elemento");
	pa2m_afirmar(lista_buscar_elemento(li, li_comparador,lista_elemento_en_posicion(li,0)) == &PRIMERO, "Se busca el primer elemento");
	pa2m_afirmar(lista_buscar_elemento(li, li_comparador,lista_elemento_en_posicion(li,1)) == &SEGUNDO, "Se busca el segundo elemento");

	pa2m_afirmar(lista_primero(li) == &PRIMERO, "Devuelve el primer elemento");
	pa2m_afirmar(lista_ultimo(li) == &QUINTO, "Devuelve el ultimo elemento");

	lista_destruir_todo(li,NULL);
}


void funciones_lista()
{
	// li_insertar();
	// li_insertar();
	// li_insertar_entre();
	// li_quitar_uno();
	// li_quitar_en_fn();
	// li_eliminar_desordenado();
	li_buscar_elemento_y_demas();
}
void funciones_pila()
{
}
void funciones_cola()
{
}
int main()
{
	pa2m_nuevo_grupo(
		"\n========================       ========================\n======================== LISTA ========================\n\n");
	funciones_lista();
	pa2m_nuevo_grupo(
		"\n========================       ========================\n======================== PILA  ========================\n\n");
	funciones_pila();
	pa2m_nuevo_grupo(
		"\n========================       ========================\n======================== COLA  ========================\n\n");
	funciones_cola();

	return pa2m_mostrar_reporte();
}
