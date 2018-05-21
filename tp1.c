#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


char** split(const char* str, char sep){ //MODULARIZAR LOS 2 IF
  if (sep=='\0') return NULL;
  size_t i=0,j=0,k=0,cant=1; //Arranca en +1 que es el null
  while(str[i]!='\0'){
    if(str[i]==sep) cant++;
    i++;
  }
  char** strv=malloc(sizeof(char*)*cant);
  i=0;
  while(str[i]!='\0'){
    if(str[i]==sep){
      strv[k]=strndup(&str[j],(i-j));
      j=i+1;
      k++;
    }
    i++;
    if(str[i]=='\0'){ //Si esta en el final
      strv[k]=strndup(&str[j],(i-j));
      j=i+1;
      k++;
    }
  }
  strv[cant]=NULL;
  return strv;
}

char* join(char** strv, char sep){
  size_t i=0,largo=0;
  while(strv[i]!=NULL){
    largo+= strlen(strv[i]);
    i++;
  }
  char* join = malloc(sizeof(char)*(largo+i));

  for(int j=0;j<i;j++){
  strcat(joint,strv[j]);
  if(strv[j+1]!=NULL) strcat(joint,&sep);
  }
  return join;
}

int main(){
  char *orig = "hola,como,va";
  char sep = ',';
  char bsep = ';';
  char** strv=split(orig,sep);
  char* joined = join(strv,bsep);
  printf("salida: %s\n",joined);
  return 0;
}
