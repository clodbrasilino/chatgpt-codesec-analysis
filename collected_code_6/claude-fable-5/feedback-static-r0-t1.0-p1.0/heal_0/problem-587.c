#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Tuple {
    int *items;
    size_t size;
} Tuple;

Node *list_append(Node *head, int value, int *error) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        *error = 1;
        return head;
    }
    node->value = value;
    node->next = NULL;
    *error = 0;
    if (head == NULL) {
        return node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

void list_free(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

Tuple *list_to_tuple(const Node *head) {
    size_t count = 0;
    const Node *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->size = count;
    if (count == 0) {
        tuple->items = NULL;
        return tuple;
    }
    tuple->items = malloc(count * sizeof(int));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    current = head;
    for (size_t i = 0; i < count; i++) {
        tuple->items[i] = current->value;
        current = current->next;
    }
    return tuple;
}

void tuple_free(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

void tuple_print(const Tuple *tuple) {
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->items[i]);
        if (i + 1 < tuple->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Node *head = NULL;
    int error = 0;
    int values[] = {10, 20, 30, 40, 50};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        head = list_append(head, values[i], &error);
        if (error != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            list_free(head);
            return EXIT_FAILURE;
        }
    }

    Tuple *tuple = list_to_tuple(head);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to convert list to tuple\n");
        list_free(head);
        return EXIT_FAILURE;
    }

    tuple_print(tuple);

    tuple_free(tuple);
    list_free(head);

    return EXIT_SUCCESS;
}