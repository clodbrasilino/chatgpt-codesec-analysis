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
} Sublist;

static void free_sublist(Sublist *sublist)
{
    Node *current;

    if (sublist == NULL) {
        return;
    }

    current = sublist->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    sublist->head = NULL;
    sublist->tail = NULL;
    sublist->length = 0;
}

static void free_sublists(Sublist *sublists, size_t count)
{
    size_t i;

    if (sublists == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free_sublist(&sublists[i]);
    }

    free(sublists);
}

static int append_value(Sublist *sublist, int value)
{
    Node *node;

    if (sublist == NULL || sublist->length == SIZE_MAX) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (sublist->tail == NULL) {
        sublist->head = node;
    } else {
        sublist->tail->next = node;
    }

    sublist->tail = node;
    ++sublist->length;
    return 1;
}

static const Sublist *find_max_length_sublist(const Sublist *sublists,
                                              size_t count)
{
    const Sublist *longest;
    size_t i;

    if (sublists == NULL || count == 0) {
        return NULL;
    }

    longest = &sublists[0];

    for (i = 1; i < count; ++i) {
        if (sublists[i].length > longest->length) {
            longest = &sublists[i];
        }
    }

    return longest;
}

static void print_sublist(const Sublist *sublist)
{
    const Node *current;
    const char *separator = "";

    if (sublist == NULL) {
        return;
    }

    current = sublist->head;
    while (current != NULL) {
        printf("%s%d", separator, current->value);
        separator = " ";
        current = current->next;
    }

    putchar('\n');
}

int main(void)
{
    Sublist *sublists;
    const Sublist *longest;
    size_t sublist_count;
    size_t i;

    if (scanf("%zu", &sublist_count) != 1 || sublist_count == 0 ||
        sublist_count > SIZE_MAX / sizeof(*sublists)) {
        return EXIT_FAILURE;
    }

    sublists = calloc(sublist_count, sizeof(*sublists));
    if (sublists == NULL) {
        return EXIT_FAILURE;
    }

    for (i = 0; i < sublist_count; ++i) {
        size_t item_count;
        size_t j;

        if (scanf("%zu", &item_count) != 1) {
            free_sublists(sublists, sublist_count);
            return EXIT_FAILURE;
        }

        for (j = 0; j < item_count; ++j) {
            int value;

            if (scanf("%d", &value) != 1 ||
                !append_value(&sublists[i], value)) {
                free_sublists(sublists, sublist_count);
                return EXIT_FAILURE;
            }
        }
    }

    longest = find_max_length_sublist(sublists, sublist_count);
    if (longest == NULL) {
        free_sublists(sublists, sublist_count);
        return EXIT_FAILURE;
    }

    printf("%zu\n", longest->length);
    print_sublist(longest);

    free_sublists(sublists, sublist_count);
    return EXIT_SUCCESS;
}