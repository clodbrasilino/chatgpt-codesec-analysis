#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} IntList;

typedef struct {
    IntList *items;
    size_t size;
} ListOfLists;

typedef struct {
    IntList first;
    IntList second;
} ListPair;

typedef struct {
    ListPair *pairs;
    size_t size;
} ZippedResult;

int init_int_list(IntList *list, const int *values, size_t size);
int zip_lists_of_lists(const ListOfLists *a, const ListOfLists *b, ZippedResult *result);
void free_int_list(IntList *list);
void free_list_of_lists(ListOfLists *list);
void free_zipped_result(ZippedResult *result);
void print_zipped_result(const ZippedResult *result);

static int safe_copy_ints(int *dst, size_t dst_capacity, const int *src, size_t src_count)
{
    size_t bytes;

    if (src_count == 0) {
        return 0;
    }
    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (src_count > dst_capacity) {
        return -1;
    }
    if (src_count > SIZE_MAX / sizeof(*dst)) {
        return -1;
    }
    bytes = src_count * sizeof(*dst);
    if (bytes > dst_capacity * sizeof(*dst)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst, src, bytes);
    return 0;
}

int init_int_list(IntList *list, const int *values, size_t size)
{
    size_t bytes;

    if (list == NULL || (size > 0 && values == NULL)) {
        return -1;
    }
    list->data = NULL;
    list->size = 0;
    if (size == 0) {
        return 0;
    }
    if (size > SIZE_MAX / sizeof(*list->data)) {
        return -1;
    }
    bytes = size * sizeof(*list->data);
    list->data = malloc(bytes);
    if (list->data == NULL) {
        return -1;
    }
    if (safe_copy_ints(list->data, size, values, size) != 0) {
        free(list->data);
        list->data = NULL;
        return -1;
    }
    list->size = size;
    return 0;
}

void free_int_list(IntList *list)
{
    if (list == NULL) {
        return;
    }
    free(list->data);
    list->data = NULL;
    list->size = 0;
}

void free_list_of_lists(ListOfLists *list)
{
    if (list == NULL) {
        return;
    }
    if (list->items != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            free_int_list(&list->items[i]);
        }
        free(list->items);
        list->items = NULL;
    }
    list->size = 0;
}

void free_zipped_result(ZippedResult *result)
{
    if (result == NULL) {
        return;
    }
    if (result->pairs != NULL) {
        for (size_t i = 0; i < result->size; i++) {
            free_int_list(&result->pairs[i].first);
            free_int_list(&result->pairs[i].second);
        }
        free(result->pairs);
        result->pairs = NULL;
    }
    result->size = 0;
}

static int copy_int_list(IntList *dst, const IntList *src)
{
    size_t bytes;

    if (dst == NULL || src == NULL) {
        return -1;
    }
    dst->data = NULL;
    dst->size = 0;
    if (src->size == 0) {
        return 0;
    }
    if (src->data == NULL) {
        return -1;
    }
    if (src->size > SIZE_MAX / sizeof(*dst->data)) {
        return -1;
    }
    bytes = src->size * sizeof(*dst->data);
    dst->data = malloc(bytes);
    if (dst->data == NULL) {
        return -1;
    }
    if (safe_copy_ints(dst->data, src->size, src->data, src->size) != 0) {
        free(dst->data);
        dst->data = NULL;
        return -1;
    }
    dst->size = src->size;
    return 0;
}

int zip_lists_of_lists(const ListOfLists *a, const ListOfLists *b, ZippedResult *result)
{
    size_t count;

    if (a == NULL || b == NULL || result == NULL) {
        return -1;
    }
    if ((a->size > 0 && a->items == NULL) || (b->size > 0 && b->items == NULL)) {
        return -1;
    }

    result->pairs = NULL;
    result->size = 0;

    count = (a->size < b->size) ? a->size : b->size;
    if (count == 0) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(*result->pairs)) {
        return -1;
    }

    result->pairs = calloc(count, sizeof(*result->pairs));
    if (result->pairs == NULL) {
        return -1;
    }
    result->size = count;

    for (size_t i = 0; i < count; i++) {
        if (copy_int_list(&result->pairs[i].first, &a->items[i]) != 0 ||
            copy_int_list(&result->pairs[i].second, &b->items[i]) != 0) {
            free_zipped_result(result);
            return -1;
        }
    }

    return 0;
}

void print_zipped_result(const ZippedResult *result)
{
    if (result == NULL || (result->size > 0 && result->pairs == NULL)) {
        return;
    }

    printf("[");
    for (size_t i = 0; i < result->size; i++) {
        const IntList *first = &result->pairs[i].first;
        const IntList *second = &result->pairs[i].second;

        printf("([");
        for (size_t j = 0; j < first->size; j++) {
            printf("%d%s", first->data[j], (j + 1 < first->size) ? ", " : "");
        }
        printf("], [");
        for (size_t j = 0; j < second->size; j++) {
            printf("%d%s", second->data[j], (j + 1 < second->size) ? ", " : "");
        }
        printf("])%s", (i + 1 < result->size) ? ", " : "");
    }
    printf("]\n");
}

int main(void)
{
    ListOfLists a = {NULL, 0};
    ListOfLists b = {NULL, 0};
    ZippedResult zipped = {NULL, 0};

    int values_a0[] = {1, 2, 3};
    int values_a1[] = {4, 5};
    int values_b0[] = {10, 20};
    int values_b1[] = {30, 40, 50};

    int status = EXIT_FAILURE;

    a.items = calloc(2, sizeof(*a.items));
    if (a.items == NULL) {
        goto cleanup;
    }
    a.size = 2;

    b.items = calloc(2, sizeof(*b.items));
    if (b.items == NULL) {
        goto cleanup;
    }
    b.size = 2;

    if (init_int_list(&a.items[0], values_a0, sizeof(values_a0) / sizeof(values_a0[0])) != 0) {
        goto cleanup;
    }
    if (init_int_list(&a.items[1], values_a1, sizeof(values_a1) / sizeof(values_a1[0])) != 0) {
        goto cleanup;
    }
    if (init_int_list(&b.items[0], values_b0, sizeof(values_b0) / sizeof(values_b0[0])) != 0) {
        goto cleanup;
    }
    if (init_int_list(&b.items[1], values_b1, sizeof(values_b1) / sizeof(values_b1[0])) != 0) {
        goto cleanup;
    }

    if (zip_lists_of_lists(&a, &b, &zipped) != 0) {
        goto cleanup;
    }

    print_zipped_result(&zipped);
    status = EXIT_SUCCESS;

cleanup:
    free_zipped_result(&zipped);
    free_list_of_lists(&a);
    free_list_of_lists(&b);
    return status;
}