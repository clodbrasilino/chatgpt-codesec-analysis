#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple tuple;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

int add_tuple(List *list, Tuple tuple) {
    if (list == NULL) {
        return -1;
    }

    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }

    new_node->tuple = tuple;
    new_node->next = list->head;
    list->head = new_node;

    return 0;
}

void list_free(List *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
}

void list_print(const List *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        printf("(%d, %d)\n", current->tuple.first, current->tuple.second);
        current = current->next;
    }
}

int main(void) {
    List list = { NULL };
    Tuple t1 = { 10, 20 };
    Tuple t2 = { 30, 40 };

    if (add_tuple(&list, t1) != 0) {
        return EXIT_FAILURE;
    }

    if (add_tuple(&list, t2) != 0) {
        list_free(&list);
        return EXIT_FAILURE;
    }

    list_print(&list);
    list_free(&list);

    return EXIT_SUCCESS;
}