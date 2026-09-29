#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static size_t list_length(const Node *head)
{
    size_t length = 0;

    while (head != NULL) {
        if (length == SIZE_MAX) {
            fprintf(stderr, "List length overflow\n");
            exit(EXIT_FAILURE);
        }

        ++length;
        head = head->next;
    }

    return length;
}

/* Possible weaknesses found:
 *  Parameter 'lists' can be declared as const array [constParameter]
 */
static size_t find_shortest_list(Node *const lists[const], size_t count)
{
    if (lists == NULL || count == 0) {
        fprintf(stderr, "Invalid list collection\n");
        exit(EXIT_FAILURE);
    }

    size_t shortest_index = 0;
    size_t shortest_length = list_length(lists[0]);

    for (size_t i = 1; i < count; ++i) {
        const size_t current_length = list_length(lists[i]);

        if (current_length < shortest_length) {
            shortest_length = current_length;
            shortest_index = i;
        }
    }

    return shortest_index;
}

static Node *create_list(const int values[const], size_t count)
{
    if (values == NULL && count != 0) {
        return NULL;
    }

    Node *head = NULL;
    Node **tail = &head;

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            while (head != NULL) {
                Node *next = head->next;
                free(head);
                head = next;
            }

            return NULL;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return head;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    const int values1[] = {1, 2, 3, 4};
    const int values2[] = {5, 6};
    const int values3[] = {7, 8, 9};

    Node *lists[] = {
        create_list(values1, sizeof(values1) / sizeof(values1[0])),
        create_list(values2, sizeof(values2) / sizeof(values2[0])),
        create_list(values3, sizeof(values3) / sizeof(values3[0]))
    };

    const size_t count = sizeof(lists) / sizeof(lists[0]);

    for (size_t i = 0; i < count; ++i) {
        if (lists[i] == NULL) {
            fprintf(stderr, "Failed to create list\n");

            for (size_t j = 0; j < count; ++j) {
                free_list(lists[j]);
            }

            return EXIT_FAILURE;
        }
    }

    const size_t shortest_index = find_shortest_list(lists, count);

    printf("Shortest list: %zu, length: %zu\n",
           shortest_index,
           list_length(lists[shortest_index]));

    for (size_t i = 0; i < count; ++i) {
        free_list(lists[i]);
    }

    return EXIT_SUCCESS;
}