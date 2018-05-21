#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FIN_LINEA '\0'

char** split(const char* str, char sep){
  if (sep=='\0') return NULL;
  size_t i=0,j=0,k=0,cant=2; //Cant arranca en 2 porque es caso minimo ("Hola,si" + NULL)

  while(str[i]!=FIN_LINEA){
    if(str[i]==sep) cant++;
    i++;
  }
  char** strv=malloc(sizeof(char*)*cant);

  i=0;

  while(str[i]!=FIN_LINEA){
    if(str[i]==sep){
      strv[k]=strndup(&str[j],(i-j));
      j=i+1;
      k++;
    }
    i++;
    if(str[i]==FIN_LINEA){
      strv[k]=strndup(&str[j],(i-j));
      j=i+1;
      k++;
    }
  }
  strv[cant-1]=NULL;
  return strv;
}

char* join(char** strv, char sep){
  size_t i=0,j=0,k=0,len=0;
  while(strv[i]!=NULL){
    len+=strlen(strv[i])+1;
    i++;
  }
  char* str=malloc(sizeof(char)*(len));
  i=0;
  while(strv[i]!=NULL){
    if(strv[i][j]==FIN_LINEA){
      if(k+1==len) str[k]=FIN_LINEA;
      else str[k]=sep;
      j=0;
      i++,k++;
    }
    else{
      str[k]=strv[i][j];
      j++,k++;
    }
  }
  return str;
}

void free_strv(char* strv[]){
  size_t i=0;
  while(strv[i]!=NULL){
    free(strv[i]);
    i++;
  }
  free(strv);
}