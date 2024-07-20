#include "definations.c"

void Error(char *str){
    printf("ERROR: %s\n",str);
    exit(-1);
}

void Log(char *str){
    printf("LOG: %s\n",str);
}