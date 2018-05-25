#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cola.c"

int main(int argc,char* argv[]){
  if(argc !=2){
    fprintf(stderr, "Cantidad de parametros erronea\n");
    return 1;
  }
  cola_t* cola = cola_crear();
  if(!cola) return 1;

  size_t n = atoi(argv[1]);
  if(n==0){
    fprintf(stderr, "Tipo de parametro incorrecto\n");
  }
  char* linea = NULL;
  size_t capacidad = 0;

  for(size_t i=0;i<n;i++){
    getline(&linea,&capacidad,stdin);
    cola_encolar(cola,linea);
    linea=NULL;
  }
  while(getline(&linea,&capacidad,stdin)!=-1){
      free(cola_desencolar(cola));
      cola_encolar(cola,linea);
      linea=NULL;
  }

  while(!cola_esta_vacia(cola)){
    char* primero = cola_ver_primero(cola);
    printf("%s\n",primero);
    free(cola_desencolar(cola));
  }
  free(linea);
  cola_destruir(cola,NULL);
  return 0;
}
