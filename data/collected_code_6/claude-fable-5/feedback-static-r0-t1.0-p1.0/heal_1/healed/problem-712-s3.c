#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *items;
    size_t length;
} List;

static bool lists_equal(const List *a, const List *b)
{
    size_t i;

    if (a == NULL || b == NULL) {
        return false;
    }
    if (a->length != b->length) {
        return false;
    }
    for (i = 0; i < a->length; i++) {
        if (a->items[i] != b->items[i]) {
            return false;
        }
    }
    return true;
}

static bool copy_list(List *dest, const List *src)
{
    size_t i;

    if (dest == NULL || src == NULL) {
        return false;
    }
    dest->length = src->length;
    if (src->length == 0) {
        dest->items = NULL;
        return true;
    }
    dest->items = malloc(src->length * sizeof(int));
    if (dest->items == NULL) {
        return false;
    }
    for (i = 0; i < src->length; i++) {
        dest->items[i] = src->items[i];
    }
    return true;
}

static void free_list_array(List *lists, size_t count)
{
    size_t i;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(lists[i].items);
        lists[i].items = NULL;
        lists[i].length = 0;
    }
    free(lists);
}

static List *remove_duplicates(const List *lists, size_t count, size_t *out_count)
{
    List *result;
    size_t result_count;
    size_t i;
    size_t j;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;
    if (lists == NULL || count == 0) {
        return NULL;
    }

    result = malloc(count * sizeof(List));
    if (result == NULL) {
        return NULL;
    }

    result_count = 0;
    for (i = 0; i < count; i++) {
        bool duplicate = false;
        for (j = 0; j < result_count; j++) {
            if (lists_equal(&lists[i], &result[j])) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            if (!copy_list(&result[result_count], &lists[i])) {
                free_list_array(result, result_count);
                return NULL;
            }
            result_count++;
        }
    }

    *out_count = result_count;
    return result;
}

static void print_lists(const List *lists, size_t count)
{
    size_t i;
    size_t j;

    if (lists == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        printf("[");
        for (j = 0; j < lists[i].length; j++) {
            printf("%d", lists[i].items[j]);
            if (j + 1 < lists[i].length) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {1, 2, 3};
    int d[] = {4, 5, 6};
    int e[] = {4, 5};
    List input[5];
    List *unique;
    size_t unique_count;

    input[0].items = a;
    input[0].length = sizeof(a) / sizeof(a[0]);
    input[1].items = b;
    input[1].length = sizeof(b) / sizeof(b[0]);
    input[2].items = c;
    input[2].length = sizeof(c) / sizeof(c[0]);
    input[3].items = d;
    input[3].length = sizeof(d) / sizeof(d[0]);
    input[4].items = e;
    input[4].length = sizeof(e) / sizeof(e[0]);

    printf("Original lists:\n");
    print_lists(input, 5);

    unique = remove_duplicates(input, 5, &unique_count);
    if (unique == NULL) {
        fprintf(stderr, "Failed to remove duplicates\n");
        return EXIT_FAILURE;
    }

    printf("After removing duplicates:\n");
    print_lists(unique, unique_count);

    free_list_array(unique, unique_count);

    return EXIT_SUCCESS;
}