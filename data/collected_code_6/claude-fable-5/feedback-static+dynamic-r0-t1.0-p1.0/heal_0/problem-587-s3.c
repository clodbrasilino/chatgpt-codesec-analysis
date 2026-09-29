#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct Tuple {
    size_t size;
    int *items;
} Tuple;

Node *list_append(Node *head, int value, int *error)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        *error = 1;
        return head;
    }
    new_node->value = value;
    new_node->next = NULL;
    *error = 0;
    if (head == NULL) {
        return new_node;
    }
    Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

void list_free(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

size_t list_length(const Node *head)
{
    size_t count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

Tuple *list_to_tuple(const Node *head)
{
    Tuple *tuple = malloc(sizeof(Tuple));
    if (tuple == NULL) {
        return NULL;
    }
    tuple->size = list_length(head);
    if (tuple->size == 0) {
        tuple->items = NULL;
        return tuple;
    }
    tuple->items = malloc(tuple->size * sizeof(int));
    if (tuple->items == NULL) {
        free(tuple);
        return NULL;
    }
    size_t i = 0;
    while (head != NULL) {
        tuple->items[i] = head->value;
        i++;
        head = head->next;
    }
    return tuple;
}

void tuple_free(Tuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->items);
        free(tuple);
    }
}

void tuple_print(const Tuple *tuple)
{
    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        printf("%d", tuple->items[i]);
        if (i + 1 < tuple->size) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    Node *head = NULL;
    int error = 0;
    int values[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < count; i++) {
        head = list_append(head, values[i], &error);
        if (error != 0) {
            fprintf(stderr, "Memory allocation failed while building list\n");
            list_free(head);
            return EXIT_FAILURE;
        }
    }

    Tuple *tuple = list_to_tuple(head);
    if (tuple == NULL) {
        fprintf(stderr, "Memory allocation failed while creating tuple\n");
        list_free(head);
        return EXIT_FAILURE;
    }

    tuple_print(tuple);

    tuple_free(tuple);
    list_free(head);
    return EXIT_SUCCESS;
}