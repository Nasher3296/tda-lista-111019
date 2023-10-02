<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA Lista

## Repositorio de Ignacio Fernández - 111019 - iafernandez@fi.uba.ar

- Para compilar:

```bash
gcc -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g src/*.c pruebas_chanutron.o -o pruebas_chanutron
```

- Para ejecutar:

```bash
./pruebas_chanutron
```

- Para ejecutar con valgrind:
```bash
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./pruebas_chanutron

```
---
##  Funcionamiento


---

## Respuestas a las preguntas teóricas
### ¿Que es una Lista (simplemente enlazada)?
Una lista es una estructura de datos que almacena los mismos en nodos. Cada uno de estos nodos guarda su respectivo dato y apunta al siguiente, diseñada para  recorrerse  en el orden en el que los datos fueron ingresados, pero no al reves, saltando de un nodo a su siguiente hasta encontrar que el siguiente del nodo actual es NULL, o sea, no tiene siguiente y por ende es el último.
[diagrama]
### ¿Que es una Cola?
Una cola es una implementación de una lista, por lo que es tambien una estructura de datos. La característica de la cola es que respeta el concepto FIFO. Esto significa que la cola fue diseñada para que los datos se accedan y eliminen de la cola en el orden que fueron ingresados. Si se ingresa A-B-C, la salida va a ser en el orden A, luego B y luego C.
[diagrama]
### ¿Que es una Pila?
Al igual que la cola, una pila es una implementacion de una lista y por ende una estructura de datos. Se diferencia de la cola ya que en lugar de utilizar el concepto FIFO, utiliza LIFO. O sea, el último elemento ingresado es el más próximo a salir. En un ingreso A-B-C, la salida será C, luego B y luego A.
[diagrama]

### Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones

* Simplemente enlazada:
* * Insertar en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada
* * Obtener en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada
* * Eliminar en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada. Una vez en el nodo, la accion es O(1) porque no necesitan desplazarse los nodos siguientes. O sea, el costo está dado por la búsqueda del nodo.


* Doblemente enlazada:
* * Insertar en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada
* * Obtener en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada
* * Eliminar en el medio: O(n), ya que se debe iterar desde el inicio de la lista la cantidad de "siguientes nodos" hasta alcanzar la posicion deseada. Una vez en el nodo, la accion es O(1) porque no necesitan desplazarse los nodos siguientes. O sea, el costo está dado por la búsqueda del nodo.

* Vec. dinámico:
* * Insertar en el medio: O(n). El acceso a la posición es directo (O(1)), pero luego se debe "desplazar" todo el resto del vector hacia adelante (O(n), se itera por cada posición delante de donde se inserta)
* * Obtener en el medio: O(1), el acceso es directo al subindice que se indica.
* * Eliminar en el medio: O(n). El acceso a la posición es directo (O(1)), pero luego se debe "desplazar" todo el resto del vector hacia atras (O(n), se itera por cada posición delante de donde se inserta)


Hago un parentesis por las dudas. Si la pregunta se refería a que dado un Nodo debo hacer alguna de las acciones, en lugar de dada una lista (ej, se me pasa la direccion del 3er nodo, en lugar de darme la lista y yo tener que buscar el 3er nodo), el costo de eliminar en el medio para la lista doblemente enlazada sería O(1), ya que desde el nodo conocemos a su nodo anterior para modificar el siguiente del mismo.
Siguiendo con esta suposicion, los costos de inserción y obtención, tanto para la lista simple como la doble, serían O(1) también.
### Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.
Todos los métodos implementados en mi trabajo de pila y cola tiene una complejidad de O(1).
Los métodos interesantes a análizar son:
* Apilar: Para mantener un costo de O(1), al apilar en la cola utilizamos el método de lista `lista_insertar_en_posicion`, indicando la posicion 0. Esta es la primer posicion de la lista, por lo que agregar o eliminar nodos no demanda recorrer la estructura, solamente accedemos a la primer posicion. De plantearse al reves la lista, considerando nuestro tope la última posicion y haciendo las inserciones en la misma, en `Apilar` no representa un problema ya que conocemos de antemano cual es el último nodo.
* Despilar: Similar a Apilar, pero utilizando el método `lista_quitar_de_posicion`, tambien indicando la posicion 0. La implementación inversa, donde el tope es la última y no la primera posicion, no es eficiente a la hora de desapilar (a diferencia de apilar). Al desapilar, al eliminar la última posicion luego debe recorrerse toda la estructura (costo O(N)) hasta llegar a la nueva ultima posicion (anteultima antes de la eliminacion) para modificar su siguiente y que ahora apunte a NULL. Por esto es por lo que utilizamos como tope la primer posicion y no hacemos la inserción a la última como podría parecer más intuitivo.
* Encolar: Para encolar, y con un costo de O(1), utilizamos `lista_insertar`. Al ser conocida la última posicion de la lista, agregar un nodo a la misma no demanda recorrer la estructura. Siendo que cada nuevo nodo es insertado al final de la cola, nuestro frente de cola tiene que ser la primer posicion, que es la más alejada del último nodo insertado. Esta posicion tambien es conocida por lo que no demanda recorrer la estructura.
* Desencolar: Para desencolar, por la mísma lógica que en `Desapilar`, el nodo a eliminar debe ser el primero de la estructura para así evitar recorrerla y mantener el costo de O(1). Planteando la cola al reves (Frente en la última posicion, encolar a la primera), desencolar requeriría recorrer la estructura entera para poder modificar al segundo elemento de la cola y que pase a ser el primero (o sea, eso implicaría un costo O(n)).

--Estos son comunes a pila y cola
* Creación: O(1), ya que solo se reserva la memoria de la lista, pero no de los nodos (no existen nodos al moemnto de crearla).
* Destrucción: O(n), ya que debe iterarse item por item de la lista para liberar la memoria.
