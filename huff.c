#include "huff.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_symbols(char* info, int n, Node*** symbols, int *m){
    int i = 0;
    for (int i = 0; i < n; i++){
        int found = 0;
        for (int j = 0; j < *m; j++){
            if ((*symbols)[j]->letter == info[i]){
                (*symbols)[j]->val++;
                found = 1;
                j=*m;
            } 
        }
        
        if(!found){
            Node* s = malloc(sizeof(Node));
            s->letter = info[i];
            s->is_leaf = 1;
            s->val = 1;
            s->left = NULL;
            s->right = NULL;
            *symbols = append(*symbols, m, &s, sizeof(Node*));
        }
    }
}

void print_symbols(Node** symbols, int m){
    for (int i = 0; i < m; i++){
        if (symbols[i]->letter != ' '){
            printf("%c, %d\t", symbols[i]->letter, symbols[i]->val);
        } else{
            printf("space, %d\t", symbols[i]->val);
        }
    }
    printf("\n");
}

void sort_nodes(Node** nodes, int m){
    for (int i = 0; i < m; i++){
        Node* temp;
        for (int j = i+1; j < m; j++){
            if (nodes[i]->val > nodes[j]->val){
                temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
    }
}

Node* create_tree(Node** symbols, int n) {
    if (n == 0) return NULL;

    Node** nodes = malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        nodes[i] = symbols[i];
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

        
        nodes[0] = parent;
        for (int i = 1; i < remaining - 1; i++) {
            nodes[i] = nodes[i + 1];
        }
        remaining--;
        
        sort_nodes(nodes, remaining);
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

void generate_codes(Node* tree, char* code, int depth){
    if(!tree) return;

    if (tree->is_leaf){
        code[depth] = '\0';
        strcpy(tree->code, code);
        printf("%c = %s\n", tree->letter, tree->code);
        return;
    }
    
    code[depth] = '1';
    generate_codes(tree->left, code, depth+1);

    code[depth] = '0';
    generate_codes(tree->right, code, depth+1);
    
}

void encode(Node** symbols, int m, char* info) {
    int n = strlen(info);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (symbols[j]->letter == info[i]) {
                printf("%s", symbols[j]->code);
                break;
            }
        }
    }
    
}

void decode(Node* tree, char* code){
    int i = 0;
    Node* n = tree;
    while(i<strlen(code)+1){
        if (n->is_leaf){
            printf("%c", n->letter);
            n=tree;
        } else{ 
            if (code[i] == '1'){
                //printf("left\n");
                n = n->left;
            } else {
                //printf("right\n");
                n = n->right;
            }
            i++;
        }
    }
}

void free_tree(Node* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(){
    char info[100];
    printf("info = ");
    scanf("%s", info);

    int n = strlen(info);
    printf("n = %d\n", n);

    int m=0;
    Node** symbols = NULL;

    create_symbols(info, n, &symbols, &m);

    if (symbols != NULL && m > 0) {
        sort_nodes(symbols, m);
    }

    print_symbols(symbols, m);

    Node* tree = create_tree(symbols, m);
    
    print_tree(tree, 0);

    char code[10];

    generate_codes(tree, code, 0);
    printf("compressed code: ");
    encode(symbols, m, info);
    printf("\n");

    char bin_code[100];
    printf("enter binary code to decode: \n");
    scanf("%s", bin_code);

    decode(tree, bin_code);
    printf("\n");

    free(symbols);
    free_tree(tree);
}

