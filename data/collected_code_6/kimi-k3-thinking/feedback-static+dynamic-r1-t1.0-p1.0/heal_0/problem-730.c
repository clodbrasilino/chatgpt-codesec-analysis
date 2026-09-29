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

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int append_node(Node **head, int data)
{
    Node *node = create_node(data);
    Node *cur;

    if (node == NULL) {
        return -1;
    }

    if (*head == NULL) {
        *head = node;
        return 0;
    }

    cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return 0;
}

void remove_consecutive_duplicates(Node *head)
{
    Node *cur = head;

    while (cur != NULL && cur->next != NULL) {
        if (cur->data == cur->next->data) {
            Node *dup = cur->next;
            cur->next = dup->next;
            free(dup);
        } else {
            cur = cur->next;
        }
    }
}

static void print_list(const Node *head)
{
    const Node *cur = head;

    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf("\n");
}

int main(void)
{
    int values[] = {1, 1, 2, 2, 2, 3, 1, 1, 4, 4, 5};
    size_t n = sizeof values / sizeof values[0];
    size_t i;
    Node *head = NULL;

    for (i = 0; i < n; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Error: memory allocation failed\n");
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