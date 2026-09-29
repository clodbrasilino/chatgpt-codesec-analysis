#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    struct node *child;
    struct node *next;
} node;

node* create_node(char *key) {
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;  
    }
    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        free(new_node);
        return NULL;
    }
    new_node->child = NULL;
    new_node->next = NULL;
    return new_node;
}

void add_child(node *parent, node *child) {
    if(parent->child == NULL) {
        parent->child = child;
    } else {
        node *temp = parent->child;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = child;
    }
}

void print_dict(node *root, int level) {
    if (root == NULL || root->key == NULL) return;
    for(int i = 0; i < level; i++) printf("\t");
    printf("%s\n", root->key);
    print_dict(root->child, level + 1);
    print_dict(root->next, level);
}

int main() {
    node *root = create_node("root");
    node *child1 = create_node("child1");
    node *child2 = create_node("child2");
    node *child3 = create_node("child3");
    node *child4 = create_node("child4");
    node *child5 = create_node("child5");

    if ( root == NULL || child1 == NULL || child2 == NULL || child3 == NULL || child4 == NULL || child5 == NULL ) {
        return -1;  
    }

    add_child(root, child1);
    add_child(root, child2);
    add_child(child1, child3);
    add_child(child1, child4);
    add_child(child2, child5);

    print_dict(root, 0);

    return 0;
}