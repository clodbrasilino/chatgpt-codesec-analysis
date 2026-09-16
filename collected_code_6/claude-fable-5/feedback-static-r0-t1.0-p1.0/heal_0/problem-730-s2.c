#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

int append(struct Node **head, int data)
{
    struct Node *node = create_node(data);
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

void remove_consecutive_duplicates(struct Node *head)
{
    if (head == NULL) {
        return;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct Node *duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
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

void free_list(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    struct Node *head = NULL;
    int values[] = {1, 1, 2, 3, 3, 3, 4, 5, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (append(&head, values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    remove_consecutive_duplicates(head);

    printf("After removing consecutive duplicates: ");
    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}