#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t length;
} List;

static void list_init(List *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
    }
}

static int list_append(List *list, int value)
{
    Node *node;

    if (list == NULL || list->length == SIZE_MAX) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    ++list->length;

    return 1;
}

static void list_destroy(List *list)
{
    Node *current;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list_init(list);
}

static const List *find_longest_list(const List *lists, size_t count)
{
    const List *longest;
    size_t i;

    if (lists == NULL || count == 0) {
        return NULL;
    }

    longest = &lists[0];

    for (i = 1; i < count; ++i) {
        if (lists[i].length > longest->length) {
            longest = &lists[i];
        }
    }

    return longest;
}

int main(void)
{
    List lists[3];
    const int values[][5] = {
        {1, 2, 0, 0, 0},
        {3, 4, 5, 6, 7},
        {8, 9, 10, 0, 0}
    };
    const size_t value_counts[] = {2, 5, 3};
    const size_t list_count = sizeof(lists) / sizeof(lists[0]);
    const List *longest;
    size_t i;
    size_t j;

    for (i = 0; i < list_count; ++i) {
        list_init(&lists[i]);
    }

    for (i = 0; i < list_count; ++i) {
        for (j = 0; j < value_counts[i]; ++j) {
            if (!list_append(&lists[i], values[i][j])) {
                fprintf(stderr, "Failed to allocate list node\n");
                for (j = 0; j < list_count; ++j) {
                    list_destroy(&lists[j]);
                }
                return EXIT_FAILURE;
            }
        }
    }

    longest = find_longest_list(lists, list_count);
    if (longest == NULL) {
        fprintf(stderr, "No lists were provided\n");
        for (i = 0; i < list_count; ++i) {
            list_destroy(&lists[i]);
        }
        return EXIT_FAILURE;
    }

    printf("Maximum length: %zu\n", longest->length);

    for (i = 0; i < list_count; ++i) {
        list_destroy(&lists[i]);
    }

    return EXIT_SUCCESS;
}