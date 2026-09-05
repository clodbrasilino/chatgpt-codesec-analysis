#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int list_sum(const struct Node *head);
struct Node *create_node(int data);
void free_list(struct Node *head);

int list_sum(const struct Node *head)
{
    if (head == NULL) {
        return 0;
    }
    return head->data + list_sum(head->next);
}

struct Node *create_node(int data)
{
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void free_list(struct Node *head)
{
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;
    int values[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;
    int sum;

    for (i = 0; i < count; i++) {
        struct Node *node = create_node(values[i]);
        if (node == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    sum = list_sum(head);
    printf("Sum: %d\n", sum);

    free_list(head);
    return EXIT_SUCCESS;
}