#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_STRING_LEN 4096u

typedef struct {
    char **items;
    size_t count;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }

    len = strnlen(src, MAX_STRING_LEN);
    if (len >= MAX_STRING_LEN) {
        return NULL;
    }

    copy = malloc(len + 1u);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, src, len);
    copy[len] = '\0';
    return copy;
}

static void free_tuple(Tuple *t)
{
    size_t i;

    if (t == NULL) {
        return;
    }
    for (i = 0; i < t->count; i++) {
        free(t->items[i]);
        t->items[i] = NULL;
    }
    free(t->items);
    t->items = NULL;
    t->count = 0;
}

static void free_tuple_list(TupleList *list)
{
    size_t i;

    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->count; i++) {
        free_tuple(&list->tuples[i]);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

static int add_tuple(TupleList *list, const char **items, size_t item_count)
{
    Tuple *new_array;
    Tuple *slot;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    if (list == NULL) {
        return -1;
    }

    if (list->count >= SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    new_array = realloc(list->tuples, (list->count + 1u) * sizeof(Tuple));
    if (new_array == NULL) {
        return -1;
    }
    list->tuples = new_array;
    slot = &list->tuples[list->count];
    slot->items = NULL;
    slot->count = 0;

    if (item_count > 0u) {
        if (items == NULL) {
            return -1;
        }
        if (item_count > SIZE_MAX / sizeof(char *)) {
            return -1;
        }
        slot->items = malloc(item_count * sizeof(char *));
        if (slot->items == NULL) {
            return -1;
        }
        for (i = 0; i < item_count; i++) {
            slot->items[i] = duplicate_string(items[i]);
            if (slot->items[i] == NULL) {
                slot->count = i;
                free_tuple(slot);
                return -1;
            }
        }
        slot->count = item_count;
    }

    list->count++;
    return 0;
}

static int remove_empty_tuples(TupleList *list)
{
    size_t read_index;
    size_t write_index;
    Tuple *shrunk;

    if (list == NULL) {
        return -1;
    }

    write_index = 0;
    for (read_index = 0; read_index < list->count; read_index++) {
        if (list->tuples[read_index].count == 0u) {
            free_tuple(&list->tuples[read_index]);
        } else {
            if (write_index != read_index) {
                list->tuples[write_index] = list->tuples[read_index];
                list->tuples[read_index].items = NULL;
                list->tuples[read_index].count = 0;
            }
            write_index++;
        }
    }

    list->count = write_index;

    if (write_index == 0u) {
        free(list->tuples);
        list->tuples = NULL;
        return 0;
    }

    shrunk = realloc(list->tuples, write_index * sizeof(Tuple));
    if (shrunk != NULL) {
        list->tuples = shrunk;
    }
    return 0;
}

static void print_tuple_list(const TupleList *list)
{
    size_t i;
    size_t j;

    if (list == NULL) {
        return;
    }
    printf("[");
    for (i = 0; i < list->count; i++) {
        printf("(");
        for (j = 0; j < list->tuples[i].count; j++) {
            printf("'%s'", list->tuples[i].items[j]);
            if (j + 1u < list->tuples[i].count) {
                printf(", ");
            }
        }
        printf(")");
        if (i + 1u < list->count) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    TupleList list;
    const char *t1[] = {"a", "b"};
    const char *t3[] = {"c"};
    const char *t5[] = {"d", "e", "f"};

    list.tuples = NULL;
    list.count = 0;

    if (add_tuple(&list, t1, 2) != 0 ||
        add_tuple(&list, NULL, 0) != 0 ||
        add_tuple(&list, t3, 1) != 0 ||
        add_tuple(&list, NULL, 0) != 0 ||
        add_tuple(&list, t5, 3) != 0) {
        fprintf(stderr, "Failed to build tuple list\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("Before: ");
    print_tuple_list(&list);

    if (remove_empty_tuples(&list) != 0) {
        fprintf(stderr, "Failed to remove empty tuples\n");
        free_tuple_list(&list);
        return EXIT_FAILURE;
    }

    printf("After:  ");
    print_tuple_list(&list);

    free_tuple_list(&list);
    return EXIT_SUCCESS;
}