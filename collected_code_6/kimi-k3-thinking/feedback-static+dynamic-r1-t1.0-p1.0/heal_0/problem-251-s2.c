#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

static Node *create_node(int data)
{
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

static int append(Node **head, int data)
{
    Node *new_node;
    Node **link;

    if (head == NULL) {
        return -1;
    }

    new_node = create_node(data);
    if (new_node == NULL) {
        return -1;
    }

    link = head;
    while (*link != NULL) {
        link = &(*link)->next;
    }
    *link = new_node;
    return 0;
}

static int insert_before_each(Node **head, int element)
{
    Node **link;
    Node *new_node;

    if (head == NULL) {
        return -1;
    }

    link = head;
    while (*link != NULL) {
        new_node = create_node(element);
        if (new_node == NULL) {
            return -1;
        }
        new_node->next = *link;
        *link = new_node;
        link = &new_node->next->next;
    }
    return 0;
}

static void print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

static void free_list(Node **head)
{
    Node *current;
    Node *next;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

int main(void)
{
    Node *head = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (append(&head, values[i]) != 0) {
            fprintf(stderr, "Error: failed to append element\n");
            free_list(&head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        fprintf(stderr, "Error: failed to insert elements\n");
        free_list(&head);
        return EXIT_FAILURE;
    }

    printf("Modified list: ");
    print_list(head);

    free_list(&head);
    return EXIT_SUCCESS;
}