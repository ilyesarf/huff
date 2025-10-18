#include "huff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_symbols(char* info, int n, Symbol** symbols, int *m){
    int i = 0;

    for (int i = 0; i < n; i++){
        int found = 0;
        for (int j = 0; j < *m; j++){
            if ((*symbols)[j].letter == info[i]){
                (*symbols)[j].occ++;
                found = 1;
                j=*m;
            } 
        }
        
        if(!found){
            //(*m)++;
            //symbols = realloc(symbols, (*m)*sizeof(Symbol));
            //symbols[(*m)-1].letter = info[i];
            //symbols[(*m)-1].occ = 1;
            Symbol s;
            s.letter = info[i];
            s.occ = 1;
            *symbols = append(*symbols, m, &s, sizeof(s));
        }
        
    }
    
}

void print_symbols(Symbol* symbols, int m){
    for (int i = 0; i < m; i++){
        printf("Letter: %c, Occurrences: %d\n", symbols[i].letter, symbols[i].occ);
    }
}

void sort_symbols(Symbol* symbols, int m){
    for (int i = 0; i < m; i++){
        Symbol temp;
        for (int j = i+1; j < m; j++){
            if (symbols[i].occ > symbols[j].occ){
                temp = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = temp;
            }
        }
    }
}

void create_children(Child** children, int *p, Symbol* symbols, int m){
    
    for (int i=0; i < m; i+=2){
        Child c;
        c.left = &symbols[i];
        c.val = c.left->occ;
        if (&symbols[i+1] != NULL){
            c.right = &symbols[i+1];
            c.val += c.right->occ;
        }

        *children = append(*children, p, &c, sizeof(Child));
    }
}

void print_children(Child* children, int p){
    for (int i = 0; i < p; i++){
        printf("Child %d: val = %d, left = %c, right = %c\n", i, children[i].val, children[i].left->letter, children[i].right ? children[i].right->letter : 'N');
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

    create_symbols(info, n, &symbols, &m);

    if (symbols != NULL && m > 0) {
        sort_symbols(symbols, m);
    }

    //print_symbols(symbols, m);

    int p=0;
    Child* children = NULL;

    create_children(&children, &p, symbols, m);
    print_children(children, p);

    free(symbols);
}
