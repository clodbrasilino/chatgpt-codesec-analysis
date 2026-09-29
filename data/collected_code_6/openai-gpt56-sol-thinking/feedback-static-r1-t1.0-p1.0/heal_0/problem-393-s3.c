#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    size_t length;
} List;

static void destroy_list(List *list)
{
    Node *current = list->head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

static void destroy_lists(List *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        destroy_list(&lists[i]);
    }

    free(lists);
}

static int append_to_list(List *list, int value)
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

static const List *find_list_with_maximum_length(
    const List *lists,
    size_t count,
    size_t *maximum_index)
{
    size_t i;
    size_t best_index;

    if (lists == NULL || count == 0 || maximum_index == NULL) {
        return NULL;
    }

    best_index = 0;

    for (i = 1; i < count; ++i) {
        if (lists[i].length > lists[best_index].length) {
            best_index = i;
        }
    }

    *maximum_index = best_index;
    return &lists[best_index];
}

int main(void)
{
    List *lists;
    const List *maximum_list;
    const Node *current;
    size_t list_count;
    size_t maximum_index;
    size_t i;

    if (scanf("%zu", &list_count) != 1) {
        return EXIT_FAILURE;
    }

    if (list_count == 0) {
        printf("No lists\n");
        return EXIT_SUCCESS;
    }

    if (list_count > SIZE_MAX / sizeof(*lists)) {
        return EXIT_FAILURE;
    }

    lists = calloc(list_count, sizeof(*lists));
    if (lists == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < list_count; ++i) {
        size_t element_count;
        size_t j;

        if (scanf("%zu", &element_count) != 1) {
            destroy_lists(lists, list_count);
            return EXIT_FAILURE;
        }

        for (j = 0; j < element_count; ++j) {
            int value;

            if (scanf("%d", &value) != 1 ||
                !append_to_list(&lists[i], value)) {
                destroy_lists(lists, list_count);
                return EXIT_FAILURE;
            }
        }
    }

    maximum_list = find_list_with_maximum_length(
        lists,
        list_count,
        &maximum_index);

    if (maximum_list == NULL) {
        destroy_lists(lists, list_count);
        return EXIT_FAILURE;
    }

    printf("List index: %zu\n", maximum_index);
    printf("Maximum length: %zu\n", maximum_list->length);
    printf("List:");

    current = maximum_list->head;
    while (current != NULL) {
        printf(" %d", current->value);
        current = current->next;
    }
    putchar('\n');

    destroy_lists(lists, list_count);
    return EXIT_SUCCESS;
}