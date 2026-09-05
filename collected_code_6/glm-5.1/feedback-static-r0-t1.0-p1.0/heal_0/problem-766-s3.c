#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} List;

void iterate_consecutive_pairs(List *list) {
    if (list == NULL || list->head == NULL) {
        return;
    }

    Node *current = list->head;
    while (current->next != NULL) {
        printf("(%d, %d)\n", current->data, current->next->data);
        current = current->next;
    }
}

List *create_list() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void append_list(List *list, int data) {
    if (list == NULL) {
        return;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        Node *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void free_list(List *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main(void) {
    List *list = create_list();
    append_list(list, 1);
    append_list(list, 2);
    append_list(list, 3);
    append_list(list, 4);

    iterate_consecutive_pairs(list);

    free_list(list);
    list = NULL;

    return 0;
}