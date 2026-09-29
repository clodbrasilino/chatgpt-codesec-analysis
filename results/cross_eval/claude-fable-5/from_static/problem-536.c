#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node *next;
};

static struct Node *create_node(int value)
{
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    return node;
}

static struct Node *append(struct Node *head, int value, int *status)
{
    struct Node *node = create_node(value);
    if (node == NULL) {
        *status = -1;
        return head;
    }
    *status = 0;
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

static int get_nth(const struct Node *head, size_t n, int *out)
{
    if (out == NULL) {
        return -1;
    }
    const struct Node *current = head;
    size_t index = 0;
    while (current != NULL) {
        if (index == n) {
            *out = current->value;
            return 0;
        }
        index++;
        current = current->next;
    }
    return -1;
}

static void free_list(struct Node *head)
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
    int status = 0;
    int i;

    for (i = 10; i <= 50; i += 10) {
        head = append(head, i, &status);
        if (status != 0) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    size_t n = 2;
    int value = 0;

    if (get_nth(head, n, &value) == 0) {
        printf("Item at index %zu is %d\n", n, value);
    } else {
        fprintf(stderr, "Index %zu is out of range\n", n);
        free_list(head);
        return EXIT_FAILURE;
    }

    if (get_nth(head, 10, &value) != 0) {
        printf("Index 10 is out of range as expected\n");
    }

    free_list(head);
    return EXIT_SUCCESS;
}