#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t* create_node(int data) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if(new_node != NULL) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}

void replace_last_node(node_t **head_ref, node_t *new_list) {
    if(head_ref == NULL || *head_ref == NULL || new_list == NULL)
        return;

    node_t *last = *head_ref;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_list;
    free(last);
}

node_t* create_sample_list(int num_nodes, int start_val) {
    node_t* node = create_node(start_val);
    node_t* current = node;
    for(int i=1; i<num_nodes; i++) {
        current->next = create_node(start_val + i);
        current = current->next;
    }
    return node;
}

void print_list(node_t *node) {
    while(node != NULL) {
        printf(" %d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {
    node_t* list1 = create_sample_list(5, 1);
    node_t* list2 = create_sample_list(3, 6);
    printf("List1 before replacing last node:");
    print_list(list1);
    replace_last_node(&list1, list2);
    printf("List1 after replacing last node:");
    print_list(list1);
    return 0;
}