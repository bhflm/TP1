#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pila.c"

#define FIN_LINEA '\0'
#define APOSTROFE '\''
#define COMILLAS '"'
const char PARENTESIS_A = '(', PARENTESIS_B = ')';
const char LLAVE_A = '{', LLAVE_B = '}';
const char CORCHETE_A = '[', CORCHETE_B = ']';


bool verificar_claves(pila_t* pila,char linea){
  if(!pila_esta_vacia(pila)){
    char* p_clave_act = pila_ver_tope(pila);
    char clave_act = *p_clave_act;
    if((linea==LLAVE_B && clave_act == LLAVE_A)||(linea==PARENTESIS_B && clave_act==PARENTESIS_A)||(linea==CORCHETE_B && clave_act==CORCHETE_A)){
      pila_desapilar(pila);
      return true;
    }
    else return false;
  }
  return false;
}


bool syntax_linea(char* linea){
  size_t i=0;
  pila_t* pila = pila_crear();
  bool encontro_prox;
  while(linea[i]!=FIN_LINEA){

    if(linea[i]==PARENTESIS_A || linea[i]==LLAVE_A || linea[i]==CORCHETE_A){
      pila_apilar(pila,&linea[i]);
    }

    else if(linea[i]==PARENTESIS_B || linea[i]==LLAVE_B || linea[i]== CORCHETE_B){
      if (!verificar_claves(pila,linea[i])){
        pila_destruir(pila);
        return false;
      }
    }

    else if(linea[i]==APOSTROFE){
      size_t pos=i;
      encontro_prox = false;
      while(linea[pos+1]!=FIN_LINEA && !encontro_prox){
        pos++;
        if(linea[pos]==APOSTROFE){
          i=pos;
          encontro_prox=true;
        }
      }
      if(!encontro_prox){
        pila_destruir(pila);
        return false;
      }
    }
    i++;
  }
    if(pila_esta_vacia(pila)){
      pila_destruir(pila);
      return true;
    }
    else{
      pila_destruir(pila);
      return false;
    }
}


int main(int argc,char* argv[]){
  if(argc !=1){
    fprintf(stderr, "Cantidad de parametros erronea\n");
    return 1;
  }
  char* linea = NULL;
  size_t capacidad = 0;
  while(getline(&linea,&capacidad,stdin)!=EOF){
    if(syntax_linea(linea)) fprintf(stdout,"OK\n");
    else fprintf(stdout,"ERROR\n");
  }
  free(linea);
  return 0;
}
