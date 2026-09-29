#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int append(Node **head, int data)
{
    Node *new_node;
    Node *current;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

int insert_before_each(Node **head, int element)
{
    Node *current;
    Node *prev = NULL;
    Node *new_node;

    if (head == NULL) {
        return -1;
    }

    current = *head;
    while (current != NULL) {
        new_node = create_node(element);
        if (new_node == NULL) {
            return -1;
        }
        new_node->next = current;
        if (prev == NULL) {
            *head = new_node;
        } else {
            prev->next = new_node;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head)
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
    int values[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < n; i++) {
        if (append(&head, values[i]) != 0) {
            fprintf(stderr, "Error: failed to append element\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        fprintf(stderr, "Error: failed to insert element\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("After insertion: ");
    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}