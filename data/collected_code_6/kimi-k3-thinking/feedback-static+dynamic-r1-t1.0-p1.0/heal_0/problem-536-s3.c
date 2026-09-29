#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int get_nth(const Node *head, size_t n, int *result)
{
    const Node *current = head;
    size_t i = 0;

    if (result == NULL) {
        return -1;
    }

    while (current != NULL) {
        if (i == n) {
            *result = current->data;
            return 0;
        }
        current = current->next;
        i++;
    }
    return -1;
}

void free_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;
    size_t n = 2;
    int result = 0;

    for (i = 0; i < count; i++) {
        Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    if (get_nth(head, n, &result) == 0) {
        printf("Item at index %zu: %d\n", n, result);
    } else {
        printf("Index %zu is out of range\n", n);
    }

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}