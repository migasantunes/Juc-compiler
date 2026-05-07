#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *type;           
    char *value;          
    struct node *child;   
    struct node *sibling; 
    int line;
    int col;
    char *annot;
} Node;

extern Node* program_root; 

Node* new_node_at(const char *type, const char *value, int line, int col);
Node* new_node(const char *type, const char *value);
void add_sibling(Node *node, Node *sibling);
void add_child(Node *parent, Node *child);
int count_siblings(Node *node);
Node* create_block(Node *list);
void print_tree(Node *node, int dots);
void print_tree_annotated(Node *node, int dots);
void free_tree(Node *node);

#endif
