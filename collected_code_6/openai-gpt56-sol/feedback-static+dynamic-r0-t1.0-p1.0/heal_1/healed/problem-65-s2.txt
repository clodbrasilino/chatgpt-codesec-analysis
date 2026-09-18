#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int64_t value;
    struct Node *next;
} Node;

static int list_sum(const Node *head, int64_t *sum)
{
    int64_t total = 0;

    while (head != NULL) {
        if ((head->value > 0 && total > INT64_MAX - head->value) ||
            (head->value < 0 && total < INT64_MIN - head->value)) {
            return 0;
        }

        total += head->value;
        head = head->next;
    }

    *sum = total;
    return 1;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int append(Node **head, Node **tail, int64_t value)
{
    Node *node = malloc(sizeof(*node));

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

int main(void)
{
    Node *head = NULL;
    Node *tail = NULL;
    int64_t value;
    int result;
    int64_t sum;

    while ((result = scanf("%" SCNd64, &value)) == 1) {
        if (!append(&head, &tail, value)) {
            fprintf(stderr, "Memory allocation failed.\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (result != EOF) {
        fprintf(stderr, "Invalid input.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!list_sum(head, &sum)) {
        fprintf(stderr, "Integer overflow.\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", sum);
    free_list(head);

    return EXIT_SUCCESS;
}