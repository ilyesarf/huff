#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char letter;
    int occ;
} Symbol;

typedef struct{
    int val;
    Symbol* left;
    Symbol* right;
} Child;

typedef struct{
    int val;
    Child* left;
    Child* right;
} Parent;

void* append(void* array, int* n, void* v, size_t v_size){
    (*n)++;
    array = realloc(array, (*n)*v_size);
    if(!array){
        printf("realloc failed!\n");
    }
    
    memcpy((char*)array + (*n - 1) * v_size, v, v_size);

    return array;
}