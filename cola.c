#include <stdlib.h>
#include "cola.h"


typedef struct nodo{
  void* dato;
  struct nodo *prox;
} nodo_t;

struct cola{
  nodo_t *prim;
  nodo_t *ult;
};

nodo_t* nodo_crear(void){
  nodo_t* nodo = malloc(sizeof(nodo_t));
  if (nodo==NULL){
    return NULL;
  }

  nodo->prox=NULL;

  return nodo;
}

cola_t* cola_crear(void){
  cola_t* cola = malloc(sizeof(cola_t));
  if(cola==NULL) return NULL;
  cola->prim = NULL;
  cola->ult = NULL;
  return cola;
}

bool cola_esta_vacia(const cola_t *cola){
  return (cola->prim==NULL);
}

bool cola_encolar(cola_t *cola, void* valor){

  nodo_t* nodo = nodo_crear();
  if (nodo == NULL) return false;
  
  nodo->dato = valor;
  
  if(cola_esta_vacia(cola)){
    cola->prim = nodo;
  }
  else{
  cola->ult->prox = nodo;
  }

  cola->ult = nodo;
  return true;
}

void* cola_ver_primero(const cola_t *cola){
  if (cola_esta_vacia(cola)) return NULL;
  return cola->prim->dato;
}

void* cola_desencolar(cola_t* cola){
  if (cola_esta_vacia(cola)) return NULL;
  nodo_t* nodo_aux;
  nodo_aux = cola->prim;
  void* dato = nodo_aux->dato;

  cola->prim = cola->prim->prox;


  if(cola->prim == NULL){
    cola->ult = NULL;
  }
  free(nodo_aux);
  return (dato);
}

void cola_destruir(cola_t* cola, void destruir_dato(void*)){

  while(!cola_esta_vacia(cola)){

    nodo_t* nodo = cola->prim;

    if (destruir_dato){
      destruir_dato(nodo->dato);
    }

    cola->prim = cola->prim->prox;
    free(nodo);
  }
  free(cola);
}
