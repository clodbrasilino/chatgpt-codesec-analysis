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
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = value;
    node->next = NULL;
    return node;
}

struct Node *append_node(struct Node *head, int value)
{
    struct Node *node = create_node(value);
    if (head == NULL) {
        return node;
    }
    struct Node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return head;
}

struct Node *shift_first_to_end(struct Node *head)
{
    if (head == NULL || head->next == NULL) {
        return head;
    }
    struct Node *first = head;
    struct Node *new_head = head->next;
    struct Node *current = new_head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = first;
    first->next = NULL;
    return new_head;
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
    while (head != NULL) {
        struct Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    struct Node *head = NULL;

    head = append_node(head, 1);
    head = append_node(head, 2);
    head = append_node(head, 3);
    head = append_node(head, 4);
    head = append_node(head, 5);

    printf("Original list: ");
    print_list(head);

    head = shift_first_to_end(head);

    printf("Shifted list:  ");
    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}