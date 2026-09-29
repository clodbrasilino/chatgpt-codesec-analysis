#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} IntList;

typedef struct {
    IntList *items;
    size_t count;
    size_t capacity;
} ListOfLists;

static int safe_int_copy(int *dst, size_t dst_capacity, const int *src, size_t count)
{
    size_t bytes;

    if (count == 0) {
        return 0;
    }
    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (count > dst_capacity) {
        return -1;
    }
    if (count > SIZE_MAX / sizeof(*dst)) {
        return -1;
    }
    bytes = count * sizeof(*dst);
    if (dst_capacity > SIZE_MAX / sizeof(*dst)) {
        return -1;
    }
    if (bytes > dst_capacity * sizeof(*dst)) {
        return -1;
    }
#ifdef __STDC_LIB_EXT1__
    if (memcpy_s(dst, dst_capacity * sizeof(*dst), src, bytes) != 0) {
        return -1;
    }
#else
    {
        size_t i;

        for (i = 0; i < count; i++) {
            dst[i] = src[i];
        }
    }
#endif
    return 0;
}

static int int_list_init(IntList *list, const int *data, size_t size)
{
    size_t bytes;

    if (list == NULL) {
        return -1;
    }
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
    if (size == 0) {
        return 0;
    }
    if (data == NULL) {
        return -1;
    }
    if (size > SIZE_MAX / sizeof(*list->data)) {
        return -1;
    }
    bytes = size * sizeof(*list->data);
    if (bytes / sizeof(*list->data) != size) {
        return -1;
    }
    list->data = malloc(bytes);
    if (list->data == NULL) {
        return -1;
    }
    list->capacity = size;
    if (safe_int_copy(list->data, list->capacity, data, size) != 0) {
        free(list->data);
        list->data = NULL;
        list->size = 0;
        list->capacity = 0;
        return -1;
    }
    list->size = size;
    return 0;
}

static void int_list_destroy(IntList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
    list->capacity = 0;
}

static int int_list_equal(const IntList *a, const IntList *b)
{
    size_t bytes;

    if (a == NULL || b == NULL) {
        return 0;
    }
    if (a->size != b->size) {
        return 0;
    }
    if (a->size == 0) {
        return 1;
    }
    if (a->data == NULL || b->data == NULL) {
        return 0;
    }
    if (a->size > SIZE_MAX / sizeof(*a->data)) {
        return 0;
    }
    bytes = a->size * sizeof(*a->data);
    return memcmp(a->data, b->data, bytes) == 0;
}

static int list_of_lists_init(ListOfLists *lol)
{
    if (lol == NULL) {
        return -1;
    }
    lol->items = NULL;
    lol->count = 0;
    lol->capacity = 0;
    return 0;
}

static int list_of_lists_append(ListOfLists *lol, const int *data, size_t size)
{
    if (lol == NULL) {
        return -1;
    }
    if (lol->count == lol->capacity) {
        size_t new_capacity;
        IntList *grown;

        if (lol->capacity > SIZE_MAX / 2) {
            return -1;
        }
        new_capacity = (lol->capacity == 0) ? 4 : lol->capacity * 2;
        if (new_capacity < lol->capacity ||
            new_capacity > SIZE_MAX / sizeof(IntList)) {
            return -1;
        }
        grown = realloc(lol->items, new_capacity * sizeof(IntList));
        if (grown == NULL) {
            return -1;
        }
        memset(grown + lol->capacity, 0,
               (new_capacity - lol->capacity) * sizeof(IntList));
        lol->items = grown;
        lol->capacity = new_capacity;
    }
    if (lol->count >= lol->capacity) {
        return -1;
    }
    if (int_list_init(&lol->items[lol->count], data, size) != 0) {
        return -1;
    }
    lol->count++;
    return 0;
}

static void list_of_lists_destroy(ListOfLists *lol)
{
    size_t i;

    if (lol == NULL) {
        return;
    }
    for (i = 0; i < lol->count; i++) {
        int_list_destroy(&lol->items[i]);
    }
    free(lol->items);
    lol->items = NULL;
    lol->count = 0;
    lol->capacity = 0;
}

int remove_duplicate_lists(ListOfLists *lol)
{
    size_t i;
    size_t j;
    size_t out;

    if (lol == NULL) {
        return -1;
    }
    out = 0;
    for (i = 0; i < lol->count; i++) {
        int duplicate = 0;

        for (j = 0; j < out; j++) {
            if (int_list_equal(&lol->items[i], &lol->items[j])) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) {
            int_list_destroy(&lol->items[i]);
        } else {
            if (out != i) {
                lol->items[out] = lol->items[i];
                lol->items[i].data = NULL;
                lol->items[i].size = 0;
                lol->items[i].capacity = 0;
            }
            out++;
        }
    }
    lol->count = out;
    return 0;
}

static void list_of_lists_print(const ListOfLists *lol)
{
    size_t i;
    size_t j;

    if (lol == NULL) {
        return;
    }
    for (i = 0; i < lol->count; i++) {
        printf("{");
        for (j = 0; j < lol->items[i].size; j++) {
            printf("%s%d", (j == 0) ? "" : ", ", lol->items[i].data[j]);
        }
        printf("}\n");
    }
}

int main(void)
{
    ListOfLists lol;
    const int values1[] = {1, 2, 3};
    const int values2[] = {4, 5};
    const int values3[] = {1, 2, 3};
    const int values4[] = {6, 7, 8, 9};
    const int values5[] = {4, 5};
    const int values6[] = {1, 2, 3};
    const int values7[] = {7};

    if (list_of_lists_init(&lol) != 0) {
        fprintf(stderr, "error: initialization failed\n");
        return EXIT_FAILURE;
    }
    if (list_of_lists_append(&lol, values1, 3) != 0 ||
        list_of_lists_append(&lol, values2, 2) != 0 ||
        list_of_lists_append(&lol, values3, 3) != 0 ||
        list_of_lists_append(&lol, values4, 4) != 0 ||
        list_of_lists_append(&lol, values5, 2) != 0 ||
        list_of_lists_append(&lol, values6, 3) != 0 ||
        list_of_lists_append(&lol, values7, 1) != 0) {
        fprintf(stderr, "error: append failed\n");
        list_of_lists_destroy(&lol);
        return EXIT_FAILURE;
    }

    printf("Original list of lists (%zu):\n", lol.count);
    list_of_lists_print(&lol);

    if (remove_duplicate_lists(&lol) != 0) {
        fprintf(stderr, "error: deduplication failed\n");
        list_of_lists_destroy(&lol);
        return EXIT_FAILURE;
    }

    printf("After removing duplicates (%zu):\n", lol.count);
    list_of_lists_print(&lol);

    list_of_lists_destroy(&lol);
    return EXIT_SUCCESS;
}