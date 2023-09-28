#include "pa2m.h"
#include <string.h>
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void probar_en_lista_5(void *(*funcion)(void *, void *)){
	char PRIMERO = 'A'; //0
	char SEGUNDO = 'B';	//1
	char TERCERO = 'C';	//2
	char CUARTO = 'D';	//3
	char QUINTO = 'E';	//4
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

	pa2m_afirmar(a == &PRIMERO,"Elemento en pos 0 == PRIMERO");
	pa2m_afirmar(b == &SEGUNDO,"Elemento en pos 1 == SEGUNDO");
	pa2m_afirmar(c == &TERCERO,"Elemento en pos 2 == TERCERO");
	pa2m_afirmar(d == &CUARTO,"Elemento en pos 3 == CUARTO");
	pa2m_afirmar(e == &QUINTO,"Elemento en pos 4 == QUINTO");
	
	funcion(a,(void *)&PRIMERO);

	lista_destruir(li);
}
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
	lista_destruir(li);
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
	lista_destruir(li);
	
}

void prueba_quitar_uno(){
	char PRIMERO = 'A';
	char SEGUNDO = 'B';
	char TERCERO = 'C';
	lista_t *li = lista_crear();
	
	lista_insertar_en_posicion(li, &TERCERO, 10);
	lista_insertar_en_posicion(li, &PRIMERO, 0);
	lista_insertar_en_posicion(li, &SEGUNDO, 1);
	void *e = lista_quitar(li);	
	pa2m_afirmar(e == &TERCERO,"Elemento quitado == TERCERO");
	lista_destruir(li);

}

void *prueba_quitar_en_fn(void *elemento, void *COSO){
	pa2m_afirmar(elemento == COSO, "FUNCIONO XD");
	

	

	// pa2m_nuevo_grupo(
	// 	"\n===================== Quito de posicion desde ultimo =====================");
	// pa2m_afirmar(lista_quitar_de_posicion(li,4) == &QUINTO,"Quito QUINTO");
	// pa2m_afirmar(lista_quitar_de_posicion(li,3) == &CUARTO,"Quito CUARTO");
	// pa2m_afirmar(lista_quitar_de_posicion(li,2) == &TERCERO,"Quito TERCERO");
	// pa2m_afirmar(lista_quitar_de_posicion(li,1) == &SEGUNDO,"Quito SEGUNDO");
	// pa2m_afirmar(lista_quitar_de_posicion(li,0) == &PRIMERO,"Quito PRIMERO");
	
	// pa2m_afirmar(lista_vacia(li), "La lista esta vacia");
	// pa2m_afirmar(lista_quitar_de_posicion(li,0) == NULL,"No se puede quitar de lista vacia");
	// // pa2m_afirmar(lista_quitar_de_posicion(li,32) == NULL,"No se puede quitar de lista vacia x2");
	// pa2m_afirmar(lista_vacia(li), "La lista esta vacia");

	// lista_destruir(li);
	return NULL;
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== LISTA ========================");
	
	// prueba_insertar_lista();
	// prueba_insertar_entre();
	// prueba_quitar_uno();
	probar_en_lista_5(prueba_quitar_en_fn);
	return pa2m_mostrar_reporte();
}
