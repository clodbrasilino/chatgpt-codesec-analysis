#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

long long list_sum(const struct Node *head)
{
    if (head == NULL) {
        return 0;
    }
    return (long long)head->value + list_sum(head->next);
}

struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
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
    struct Node *tail = NULL;
    const int values[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        struct Node *node = create_node(values[i]);
        if (node == NULL) {
            free_list(head);
            fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    if (printf("Sum: %lld\n", list_sum(head)) < 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}