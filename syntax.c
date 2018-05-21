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


bool chequear_apostrofe(char* linea,size_t *pos){
  bool encontro_prox=false;
  while(linea[*pos]!=FIN_LINEA && !encontro_prox){
    printf("Pos: %zu \n",*pos);

    if(linea[*pos+1]==APOSTROFE) encontro_prox = true;
    *pos++;
  }
  return encontro_prox;
}


bool verificar_claves(pila_t* pila,char linea){
  if(!pila_esta_vacia(pila)){
    //Esto es una clave que cierra.
    char* p_clave_act = pila_ver_tope(pila);
    //Esta de aca es con la que tiene que coincidir.
    char clave_act = *p_clave_act;
    printf("Clave actual:%c, linea:%c \n",clave_act,linea);
    if(linea==LLAVE_B && clave_act == LLAVE_A){
      printf("Desapilo\n");
      pila_desapilar(pila);
      return true;
    }
    else if(linea==PARENTESIS_B && clave_act==PARENTESIS_A){
      pila_desapilar(pila);
      printf("Desapilo\n");
      return true;
    }
    else if(linea==CORCHETE_B && clave_act==CORCHETE_A){
      pila_desapilar(pila);
      printf("Desapilo\n");
      return true;
    }
    else{
      printf("No desapilo\n");
      return false;
    }
  }
  return false;
}

bool syntax_linea(char* linea){
  size_t i=0;
  pila_t* pila = pila_crear();
  bool encontro_prox = false;
  while(linea[i]!=FIN_LINEA){
    if(linea[i]==PARENTESIS_A || linea[i]==LLAVE_A || linea[i]==CORCHETE_A){
      printf("Apilo %c\n",linea[i]);
      pila_apilar(pila,&linea[i]);
    }
    else if(linea[i]==PARENTESIS_B || linea[i]==LLAVE_B || linea[i]== CORCHETE_B){
      if (!verificar_claves(pila,linea[i])) return false;
    }
    else if(linea[i]==APOSTROFE){
      while(!encontro_prox && linea[i+1]!=FIN_LINEA){
        if(linea[i+1]==APOSTROFE) encontro_prox=true;
        else i++;
      }

      if(!encontro_prox){
          printf("No encontro prox\n");
          return false;
      }

    }
    i++;
  }
  if(pila_esta_vacia(pila)){
    printf("Pila vacia\n");
    return true;
  }
  else{
    printf("Pila NO vacia \n");
    return false;
  }
}


int main(int argc,char* argv[]){
  if(argc !=1){
    fprintf(stderr, "Cantidad de parametros erronea\n");
    return 1;
  }
  char* linea = NULL;
  size_t capacidad = 0; ssize_t leidos;
  int i =0;
  while(getline(&linea,&capacidad,stdin)!=EOF){
    printf("LINEA: %s\n",linea);
    if(syntax_linea(linea)) printf("OK\n\n");
    else printf("ERROR \n\n");
  }
  free(linea);
  return 0;
}
