#include "huff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_symbols(char* info, int n, Node** symbols, int *m){
    int i = 0;

    for (int i = 0; i < n; i++){
        int found = 0;
        for (int j = 0; j < *m; j++){
            if ((*symbols)[j].letter == info[i]){
                (*symbols)[j].val++;
                found = 1;
                j=*m;
            } 
        }
        
        if(!found){
            Node s;
            s.letter = info[i];
            s.is_leaf = 1;
            s.val = 1;
            s.left = NULL;
            s.right = NULL;
            *symbols = append(*symbols, m, &s, sizeof(s));
        }
        
    }
    
}

void print_symbols(Node* symbols, int m){
    for (int i = 0; i < m; i++){
        if (symbols[i].letter != ' '){

            printf("%c, %d\t", symbols[i].letter, symbols[i].val);
        } else{
            printf("space, %d\t", symbols[i].val);
        }
    }
    printf("\n");
}

void sort_symbols(Node* symbols, int m){
    for (int i = 0; i < m; i++){
        Node temp;
        for (int j = i+1; j < m; j++){
            if (symbols[i].val > symbols[j].val){
                temp = symbols[i];
                symbols[i] = symbols[j];
                symbols[j] = temp;
            }
        }
    }
}

Node* create_tree(Node* symbols, int n) {
    if (n == 0) return NULL;

    Node** nodes = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        Node* leaf = malloc(sizeof(Node));
        *leaf = symbols[i];
        nodes[i] = leaf;
    }

    int remaining = n;

    while (remaining > 1) {
        Node* left = nodes[0];
        Node* right = nodes[1];

        Node* parent = malloc(sizeof(Node));
        parent->left = left;
        parent->right = right;
        parent->val = left->val + right->val;
        parent->is_leaf = 0;
        parent->letter = 0;

        
        for (int i = 2; i < remaining; i++) nodes[i - 2] = nodes[i];
        nodes[remaining - 2] = parent;
        remaining--; 
    }

    Node* root = nodes[0];
    free(nodes);

    return root;
}

void print_tree(Node* n, int depth){
    if (!n) return;
    for(int i=0;i<depth;i++) printf("  ");
    if (n->is_leaf)
        printf("Symbol '%c' (%d)\n", n->letter, n->val);
    else
        printf("Node (val=%d)\n", n->val);

    print_tree(n->left, depth+1);
    print_tree(n->right, depth+1);
}

int main(){
    char info[100];
    printf("info = ");
    scanf("%s", info);

    int n = strlen(info);
    printf("n = %d\n", n);

    int m=0;
    Node* symbols = NULL;

    create_symbols(info, n, &symbols, &m);

    if (symbols != NULL && m > 0) {
        sort_symbols(symbols, m);
    }

    print_symbols(symbols, m);

    Node* tree = create_tree(symbols, m);
    
    print_tree(tree, 0);

    free(symbols);
    free(tree);
}
