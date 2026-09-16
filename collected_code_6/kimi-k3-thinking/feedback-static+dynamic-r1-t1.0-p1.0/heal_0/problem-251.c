#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int append(Node **head, int data)
{
    if (head == NULL) {
        return -1;
    }

    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return 0;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return 0;
}

int insert_before_each(Node **head, int value)
{
    if (head == NULL) {
        return -1;
    }

    Node **pp = head;
    while (*pp != NULL) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            return -1;
        }
        new_node->data = value;
        new_node->next = *pp;
        *pp = new_node;
        pp = &(*pp)->next->next;
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
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void)
{
    Node *head = NULL;

    for (int i = 1; i <= 5; i++) {
        if (append(&head, i) != 0) {
            fprintf(stderr, "Failed to append %d\n", i);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        fprintf(stderr, "Failed to insert before each element\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("After inserting 0 before each element: ");
    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}