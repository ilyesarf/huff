#include "huff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Symbol* parse_info(char* info, int n, Symbol* symbols, int *m){
    int i = 0;

    for (int i = 0; i < n; i++){
        int found = 0;
        for (int j = 0; j < *m; j++){
            if (symbols[j].letter == info[i]){
                (symbols[j]).occ++;
                found = 1;
                j=*m;
            } 
        }
        
        if(!found){
            (*m)++;
            symbols = realloc(symbols, (*m)*sizeof(Symbol));
            symbols[(*m)-1].letter = info[i];
            symbols[(*m)-1].occ = 1;
        }
        
    }
    
    return symbols;
}

void print_symbols(Symbol* symbols, int m){
    for (int i = 0; i < m; i++){
        printf("Letter: %c, Occurrences: %d\n", symbols[i].letter, symbols[i].occ);
    }
}

int main(){
    char info[100];
    printf("info = ");
    scanf("%s", info);

    int n = strlen(info);
    printf("n = %d\n", n);

    int m=0;
    Symbol* symbols = NULL;

    symbols = parse_info(info, n, symbols, &m);

    print_nodes(symbols, m);

    free(symbols);
}
