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

Node *remove_even_numbers(Node *head)
{
    Node **current = &head;

    while (*current != NULL) {
        if ((*current)->value % 2 == 0) {
            Node *removed = *current;
            *current = removed->next;
            free(removed);
        } else {
            current = &(*current)->next;
        }
    }

    return head;
}

static int print_list(const Node *head)
{
    const Node *current = head;
    int first = 1;

    while (current != NULL) {
        if (!first && putchar(' ') == EOF) {
            return 0;
        }

        if (printf("%d", current->value) < 0) {
            return 0;
        }

        first = 0;
        current = current->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t count;
    size_t index;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid list length\n");
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        int value;

        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid list element\n");
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_node(&head, &tail, value)) {
            fprintf(stderr, "Unable to allocate memory\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    head = remove_even_numbers(head);

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}