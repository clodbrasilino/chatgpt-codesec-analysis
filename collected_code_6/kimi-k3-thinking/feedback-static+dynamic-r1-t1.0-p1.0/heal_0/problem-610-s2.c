#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *node = malloc(sizeof *node);
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static int append_node(Node **head, int data)
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

static int remove_kth(Node **head, size_t k)
{
    Node *current;
    Node *previous;
    size_t i;

    if (head == NULL || *head == NULL) {
        return -1;
    }

    if (k == 0) {
        current = *head;
        *head = current->next;
        free(current);
        return 0;
    }

    previous = NULL;
    current = *head;
    for (i = 0; i < k; i++) {
        if (current == NULL) {
            return -1;
        }
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return -1;
    }

    previous->next = current->next;
    free(current);
    return 0;
}

static void print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    putchar('\n');
}

static void free_list(Node *head)
{
    Node *current = head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    Node *head = NULL;
    size_t k = 2;
    int i;

    for (i = 0; i < 5; i++) {
        if (append_node(&head, (i + 1) * 10) != 0) {
            fprintf(stderr, "failed to append node\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (remove_kth(&head, k) != 0) {
        fprintf(stderr, "failed to remove element at index %zu\n", k);
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("After removing index %zu: ", k);
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}