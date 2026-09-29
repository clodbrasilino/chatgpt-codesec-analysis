#include <stdio.h>
#include <stdlib.h>

typedef struct tuple {
    int first;
    int second;
} tuple_t;

typedef struct list_node {
    tuple_t tuple;
    struct list_node *next;
} list_node_t;

int add_tuple_to_list(list_node_t **head, const tuple_t *tuple) {
    list_node_t *new_node = NULL;

    if (head == NULL || tuple == NULL) {
        return -1;
    }

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->tuple = *tuple;
    new_node->next = *head;
    *head = new_node;

    return 0;
}

void free_list(list_node_t *head) {
    list_node_t *current = head;

    while (current != NULL) {
        list_node_t *next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    list_node_t *list = NULL;
    tuple_t tuple = { 42, 84 };

    if (add_tuple_to_list(&list, &tuple) != 0) {
        return EXIT_FAILURE;
    }

    for (list_node_t *current = list; current != NULL; current = current->next) {
        printf("%d %d\n", current->tuple.first, current->tuple.second);
    }

    free_list(list);
    return EXIT_SUCCESS;
}