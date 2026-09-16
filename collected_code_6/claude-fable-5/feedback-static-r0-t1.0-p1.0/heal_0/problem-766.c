#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef void (*PairCallback)(int first, int second);

static Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
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

static Node *build_list(const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    for (i = 0; i < count; i++) {
        Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    return head;
}

static int iterate_pairs(const Node *head, PairCallback callback)
{
    const Node *current;

    if (callback == NULL) {
        return -1;
    }
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    current = head;
    while (current->next != NULL) {
        callback(current->value, current->next->value);
        current = current->next;
    }
    return 0;
}

static void print_pair(int first, int second)
{
    printf("(%d, %d)\n", first, second);
}

int main(void)
{
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    Node *head;

    head = build_list(values, count);
    if (head == NULL) {
        fprintf(stderr, "Failed to allocate list\n");
        return EXIT_FAILURE;
    }

    if (iterate_pairs(head, print_pair) != 0) {
        fprintf(stderr, "Failed to iterate pairs\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}