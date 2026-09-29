#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int append_node(Node **head, Node **tail, int value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 1;
}

static void remove_even_numbers(Node **head)
{
    Node **current;

    if (head == NULL) {
        return;
    }

    current = head;

    while (*current != NULL) {
        Node *node = *current;

        if (node->value % 2 == 0) {
            *current = node->next;
            free(node);
        } else {
            current = &node->next;
        }
    }
}

static int print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d%s", current->value,
                   current->next != NULL ? " " : "\n") < 0) {
            return 0;
        }
        current = current->next;
    }

    if (head == NULL && putchar('\n') == EOF) {
        return 0;
    }

    return 1;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const size_t count = sizeof(values) / sizeof(values[0]);
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0; i < count; ++i) {
        if (!append_node(&head, &tail, values[i])) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    remove_even_numbers(&head);

    if (!print_list(head)) {
        status = EXIT_FAILURE;
    }

    free_list(head);
    return status;
}