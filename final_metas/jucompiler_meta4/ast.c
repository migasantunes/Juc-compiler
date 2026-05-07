/*
 * Abstract Syntax Tree (AST) management for the Juc programming language
 * Provides functions for creating and manipulating AST nodes
 * Supports tree construction for program structure and expressions
 */

#include "ast.h"

Node* program_root = NULL;

/* Create new AST node with position information */
Node* new_node_at(const char *type, const char *value, int line, int col) {
    Node *n = (Node*)malloc(sizeof(Node));
    n->type = strdup(type);
    n->value = value ? strdup(value) : NULL;
    n->child = NULL;
    n->sibling = NULL;
    n->line = line;
    n->col = col;
    n->annot = NULL;
    return n;
}

/* Create new AST node with default position */
Node* new_node(const char *type, const char *value) {
    return new_node_at(type, value, 0, 0);
}

void add_sibling(Node *node, Node *sibling) {
    if (node == NULL || sibling == NULL) return;
    Node *current = node;
    while (current->sibling != NULL) {
        current = current->sibling;
    }
    current->sibling = sibling;
}

void add_child(Node *parent, Node *child) {
    if (parent == NULL || child == NULL) return;
    if (parent->child == NULL) {
        parent->child = child;
    } else {
        add_sibling(parent->child, child);
    }
}

int count_siblings(Node *node) {
    int count = 0;
    while (node != NULL) {
        count++;
        node = node->sibling;
    }
    return count;
}

Node* create_block(Node *list) {
    int count = count_siblings(list);
    if (count == 1) {
        return list; 
    }
    Node *block = new_node("Block", NULL);
    add_child(block, list);
    return block;
}

void print_tree(Node *node, int dots) {
    if (node == NULL) return;
    for (int i = 0; i < dots; i++) {
        printf(".");
    }
    if (node->value != NULL) {
        printf("%s(%s)\n", node->type, node->value);
    } else {
        printf("%s\n", node->type);
    }
    print_tree(node->child, dots + 2);
    print_tree(node->sibling, dots);
}

void print_tree_annotated(Node *node, int dots) {
    if (node == NULL) return;
    for (int i = 0; i < dots; i++) {
        printf(".");
    }
    if (node->value != NULL) {
        printf("%s(%s)", node->type, node->value);
    } else {
        printf("%s", node->type);
    }
    if (node->annot != NULL) {
        printf(" - %s", node->annot);
    }
    printf("\n");
    print_tree_annotated(node->child, dots + 2);
    print_tree_annotated(node->sibling, dots);
}

void free_tree(Node *node) {
    if (node == NULL) return;
    free_tree(node->child);
    free_tree(node->sibling);
    free(node->type);
    if (node->value) free(node->value);
    /* annot points to static strings, do not free */
    free(node);
}
