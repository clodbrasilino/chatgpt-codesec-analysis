#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static size_t list_length(const Node *head)
{
    size_t length = 0;

    while (head != NULL) {
        ++length;
        head = head->next;
    }

    return length;
}

static const Node *find_minimum_length_list(const Node *const lists[],
                                            size_t list_count,
                                            size_t *minimum_length)
{
    const Node *shortest;
    size_t shortest_length;
    size_t i;

    if (lists == NULL || minimum_length == NULL || list_count == 0) {
        return NULL;
    }

    shortest = lists[0];
    shortest_length = list_length(lists[0]);

    for (i = 1; i < list_count; ++i) {
        size_t current_length = list_length(lists[i]);

        if (current_length < shortest_length) {
            shortest = lists[i];
            shortest_length = current_length;
        }
    }

    *minimum_length = shortest_length;
    return shortest;
}

static Node *create_node(int value)
{
    Node *node = malloc(sizeof(*node));

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

static void print_list(const Node *head)
{
    printf("[");

    while (head != NULL) {
        printf("%d", head->value);
        head = head->next;

        if (head != NULL) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main(void)
{
    Node *list1 = NULL;
    Node *list2 = NULL;
    Node *list3 = NULL;
    Node *lists[3];
    const Node *shortest;
    size_t minimum_length;
    int status = EXIT_FAILURE;

    list1 = create_node(1);
    if (list1 == NULL) {
        goto cleanup;
    }

    list1->next = create_node(2);
    if (list1->next == NULL) {
        goto cleanup;
    }

    list1->next->next = create_node(3);
    if (list1->next->next == NULL) {
        goto cleanup;
    }

    list2 = create_node(4);
    if (list2 == NULL) {
        goto cleanup;
    }

    list3 = create_node(5);
    if (list3 == NULL) {
        goto cleanup;
    }

    list3->next = create_node(6);
    if (list3->next == NULL) {
        goto cleanup;
    }

    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;

    shortest = find_minimum_length_list(
        (const Node *const *)lists,
        sizeof(lists) / sizeof(lists[0]),
        &minimum_length
    );

    if (shortest == NULL) {
        goto cleanup;
    }

    printf("Minimum length: %zu\n", minimum_length);
    printf("Shortest list: ");
    print_list(shortest);
    status = EXIT_SUCCESS;

cleanup:
    free_list(list1);
    free_list(list2);
    free_list(list3);

    if (status != EXIT_SUCCESS) {
        fprintf(stderr, "An error occurred.\n");
    }

    return status;
}