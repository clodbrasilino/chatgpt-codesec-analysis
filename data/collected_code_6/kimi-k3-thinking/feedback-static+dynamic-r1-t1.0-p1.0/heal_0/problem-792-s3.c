#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append_node(Node **head, int data)
{
    Node *node;
    Node *current;

    if (head == NULL) {
        return -1;
    }

    node = create_node(data);
    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

size_t count_list(const Node *head)
{
    size_t count = 0;
    const Node *current = head;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void free_list(Node *head)
{
    Node *next;

    while (head != NULL) {
        next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Node *head = NULL;
    int values[] = {10, 20, 30, 40, 50};
    size_t n = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < n; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Error: failed to allocate memory for node\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Number of elements in the list: %zu\n", count_list(head));

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}