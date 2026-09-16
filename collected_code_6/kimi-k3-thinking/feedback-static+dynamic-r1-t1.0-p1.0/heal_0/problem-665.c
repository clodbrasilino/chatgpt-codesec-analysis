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

static int append_node(Node **head, int data)
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

static Node *shift_first_to_end(Node *head)
{
    Node *first;
    Node *last;

    if (head == NULL || head->next == NULL) {
        return head;
    }

    first = head;
    last = head;

    while (last->next != NULL) {
        last = last->next;
    }

    head = first->next;
    last->next = first;
    first->next = NULL;

    return head;
}

static void print_list(const Node *head)
{
    const Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

static void free_list(Node *head)
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
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        if (append_node(&head, values[i]) != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    printf("Original list: ");
    print_list(head);

    head = shift_first_to_end(head);

    printf("After shift:   ");
    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}