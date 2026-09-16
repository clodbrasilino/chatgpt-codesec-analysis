#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail;
    size_t length;
} List;

typedef struct ListEntry {
    List *list;
    struct ListEntry *next;
} ListEntry;

typedef struct {
    ListEntry *head;
    ListEntry *tail;
} ListCollection;

static void list_destroy(List *list)
{
    ListNode *current;
    ListNode *next;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

static List *list_create(void)
{
    return calloc(1, sizeof(List));
}

static bool list_append(List *list, int value)
{
    ListNode *node;

    if (list == NULL || list->length == SIZE_MAX) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
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
    return true;
}

static List *list_create_from_array(const int *values, size_t count)
{
    List *list;
    size_t i;

    if (count > 0 && values == NULL) {
        return NULL;
    }

    list = list_create();
    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; ++i) {
        if (!list_append(list, values[i])) {
            list_destroy(list);
            return NULL;
        }
    }

    return list;
}

static bool collection_append(ListCollection *collection, List *list)
{
    ListEntry *entry;

    if (collection == NULL || list == NULL) {
        return false;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return false;
    }

    entry->list = list;
    entry->next = NULL;

    if (collection->tail == NULL) {
        collection->head = entry;
    } else {
        collection->tail->next = entry;
    }

    collection->tail = entry;
    return true;
}

static void collection_destroy(ListCollection *collection)
{
    ListEntry *current;
    ListEntry *next;

    if (collection == NULL) {
        return;
    }

    current = collection->head;
    while (current != NULL) {
        next = current->next;
        list_destroy(current->list);
        free(current);
        current = next;
    }

    collection->head = NULL;
    collection->tail = NULL;
}

static bool find_longest_lists(
    const ListCollection *collection,
    const List ***out_lists,
    size_t *out_count,
    size_t *out_length)
{
    const ListEntry *entry;
    const List **matches;
    size_t maximum_length = 0;
    size_t match_count = 0;
    size_t index = 0;
    bool found = false;

    if (collection == NULL || out_lists == NULL ||
        out_count == NULL || out_length == NULL) {
        return false;
    }

    *out_lists = NULL;
    *out_count = 0;
    *out_length = 0;

    for (entry = collection->head; entry != NULL; entry = entry->next) {
        if (entry->list == NULL) {
            return false;
        }

        if (!found || entry->list->length > maximum_length) {
            maximum_length = entry->list->length;
            match_count = 1;
            found = true;
        } else if (entry->list->length == maximum_length) {
            if (match_count == SIZE_MAX) {
                return false;
            }
            ++match_count;
        }
    }

    if (!found) {
        return true;
    }

    if (match_count > SIZE_MAX / sizeof(*matches)) {
        return false;
    }

    matches = malloc(match_count * sizeof(*matches));
    if (matches == NULL) {
        return false;
    }

    for (entry = collection->head; entry != NULL; entry = entry->next) {
        if (entry->list->length == maximum_length) {
            matches[index++] = entry->list;
        }
    }

    *out_lists = matches;
    *out_count = match_count;
    *out_length = maximum_length;
    return true;
}

static bool print_list(const List *list)
{
    const ListNode *node;
    const char *separator = "";

    if (list == NULL || putchar('[') == EOF) {
        return false;
    }

    for (node = list->head; node != NULL; node = node->next) {
        if (printf("%s%d", separator, node->value) < 0) {
            return false;
        }
        separator = ", ";
    }

    return putchar(']') != EOF;
}

int main(void)
{
    static const int first[] = {1, 2, 3};
    static const int second[] = {4, 5, 6, 7};
    static const int third[] = {8};
    static const int fourth[] = {9, 10, 11, 12};
    static const struct {
        const int *values;
        size_t count;
    } input[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };

    ListCollection collection = {NULL, NULL};
    const List **longest_lists = NULL;
    size_t longest_count = 0;
    size_t longest_length = 0;
    size_t i;
    int result = EXIT_FAILURE;

    for (i = 0; i < sizeof(input) / sizeof(input[0]); ++i) {
        List *list = list_create_from_array(input[i].values, input[i].count);

        if (list == NULL) {
            fprintf(stderr, "Failed to create list.\n");
            goto cleanup;
        }

        if (!collection_append(&collection, list)) {
            list_destroy(list);
            fprintf(stderr, "Failed to add list to collection.\n");
            goto cleanup;
        }
    }

    if (!find_longest_lists(
            &collection,
            &longest_lists,
            &longest_count,
            &longest_length)) {
        fprintf(stderr, "Failed to find longest lists.\n");
        goto cleanup;
    }

    if (printf("Maximum length: %zu\n", longest_length) < 0) {
        goto cleanup;
    }

    for (i = 0; i < longest_count; ++i) {
        if (!print_list(longest_lists[i]) || putchar('\n') == EOF) {
            goto cleanup;
        }
    }

    result = EXIT_SUCCESS;

cleanup:
    free(longest_lists);
    collection_destroy(&collection);
    return result;
}