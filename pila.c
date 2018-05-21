#include "pila.h"
#include <stdlib.h>

#define TAMANIO_PILA 10
#define COEF_CANT_MINIMA 4
#define COEF_REDIM 2
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

bool pila_redimensionar(pila_t *pila,size_t nueva_capacidad){

  void* aux = realloc(pila->datos,sizeof(void*) * nueva_capacidad);
  if(aux==NULL){
    return false;
  }
  pila->datos = aux;
  pila->capacidad = nueva_capacidad;

  return true;
}

pila_t* pila_crear(void){

  pila_t* pila = malloc(sizeof(pila_t));
  if(pila==NULL){
    return NULL;
    }

  pila->cantidad = 0;
  pila->capacidad = TAMANIO_PILA;

  pila->datos=malloc((pila->capacidad) * sizeof(void*));
  if (pila->datos == NULL){
    free(pila);
    return NULL;
  }

  return pila;
}

void pila_destruir(pila_t *pila){
  free(pila->datos);
  free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
  return pila->cantidad==0;
}

bool pila_apilar(pila_t *pila, void* valor){
  if (pila->cantidad == pila->capacidad){
    if(!pila_redimensionar(pila,(pila->capacidad)*COEF_REDIM)){
      return false;
    }
  }
  pila->datos[pila->cantidad]=valor;
  pila->cantidad++;

  return true;
}

void* pila_ver_tope(const pila_t *pila){
  if(pila_esta_vacia(pila)){
    return NULL;
  }
  void* tope =pila->datos[pila->cantidad-1];

  return tope;
}

void* pila_desapilar(pila_t *pila){
  if(pila_esta_vacia(pila)){
    return NULL;
  }

  void* pop = pila->datos[pila->cantidad-1];
  pila->cantidad --;

  if(pila->cantidad < pila->capacidad/COEF_CANT_MINIMA){
    pila_redimensionar(pila,pila->capacidad/COEF_REDIM);
  }

  return pop;
}
