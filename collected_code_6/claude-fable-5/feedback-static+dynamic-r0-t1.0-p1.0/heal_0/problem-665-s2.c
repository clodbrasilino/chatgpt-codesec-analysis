#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

int append_node(struct Node **head, int value)
{
    struct Node *node = create_node(value);
    if (node == NULL) {
        return -1;
    }
    if (*head == NULL) {
        *head = node;
        return 0;
    }
    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 0;
}

void shift_first_to_end(struct Node **head)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }
    struct Node *first = *head;
    struct Node *current = first;
    while (current->next != NULL) {
        current = current->next;
    }
    *head = first->next;
    first->next = NULL;
    current->next = first;
}

void print_list(const struct Node *head)
{
    const struct Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct Node **head)
{
    if (head == NULL) {
        return;
    }
    struct Node *current = *head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(void)
{
    struct Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(&head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    shift_first_to_end(&head);

    printf("Shifted list:  ");
    print_list(head);

    free_list(&head);
    return EXIT_SUCCESS;
}