#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

static struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

static int append_node(struct Node **head, int data)
{
    struct Node *node;
    struct Node *current;

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

static int remove_kth(struct Node **head, size_t k)
{
    struct Node *current;
    struct Node *previous;
    size_t index;

    if (head == NULL || *head == NULL || k == 0) {
        return -1;
    }
    current = *head;
    previous = NULL;
    index = 1;
    while (current != NULL && index < k) {
        previous = current;
        current = current->next;
        index++;
    }
    if (current == NULL) {
        return -1;
    }
    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    return 0;
}

static void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

static void free_list(struct Node *head)
{
    struct Node *current = head;
    struct Node *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    struct Node *head = NULL;
    size_t i;
    size_t k = 3;

    for (i = 1; i <= 5; i++) {
        if (append_node(&head, (int)(i * 10)) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (remove_kth(&head, k) != 0) {
        fprintf(stderr, "Could not remove element at position %zu\n", k);
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("List after removal: ");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}