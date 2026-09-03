#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node {
    double data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    size_t size;
} List;

List *list_create(void) {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

int list_append(List *list, double value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = value;
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
    list->size++;
    return 0;
}

void list_destroy(List *list) {
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

List *map_power(const int *bases, size_t size) {
    List *result = list_create();
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        double value = pow((double)bases[i], (double)i);
        if (list_append(result, value) != 0) {
            list_destroy(result);
            return NULL;
        }
    }

    return result;
}

int main(void) {
    int bases[] = {2, 3, 4, 5, 6};
    size_t size = sizeof(bases) / sizeof(bases[0]);

    List *powers = map_power(bases, size);
    if (powers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    Node *current = powers->head;
    size_t index = 0;
    while (current != NULL) {
        printf("Index %zu: %.2f\n", index, current->data);
        current = current->next;
        index++;
    }

    list_destroy(powers);
    return EXIT_SUCCESS;
}