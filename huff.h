#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    int val;
    char is_leaf; // 1 = Symbol, 0 = internal
    char letter;  // only valid if is_leaf==1
    struct Node* left;
    struct Node* right;
} Node;

void* append(void* array, int* n, void* v, size_t v_size){
    (*n)++;
    array = realloc(array, (*n)*v_size);
    if(!array){
        printf("realloc failed!\n");
    }
    
    memcpy((char*)array + (*n - 1) * v_size, v, v_size);

    return array;
}