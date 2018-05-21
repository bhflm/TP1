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
  char* linea = NULL;
  size_t capacidad = 0; ssize_t leidos;

  for(size_t i=0;i<n;i++){
    getline(&linea,&capacidad,stdin);
    cola_encolar(cola,linea);
    linea=NULL;
  }
  while(getline(&linea,&capacidad,stdin)!=EOF){
      cola_desencolar(cola);
      cola_encolar(cola,linea);
      linea=NULL;
  }
  //mandar la cola por stdout
  while(!cola_esta_vacia(cola)){
    printf("%s \n",(char*)cola_desencolar(cola));
  }
  free(linea);
  return 0;
}
