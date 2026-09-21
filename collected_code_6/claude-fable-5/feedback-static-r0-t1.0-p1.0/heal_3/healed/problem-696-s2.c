#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int *values;
    size_t length;
} List;

typedef struct {
    List first;
    List second;
} Pair;

typedef struct {
    Pair *pairs;
    size_t length;
} ZipResult;

static int copy_list(List *dest, const List *src)
{
    size_t byte_count;

    if (dest == NULL || src == NULL) {
        return -1;
    }
    dest->length = src->length;
    if (src->length == 0U) {
        dest->values = NULL;
        return 0;
    }
    if (src->values == NULL) {
        return -1;
    }
    if (src->length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    byte_count = src->length * sizeof(int);
    dest->values = malloc(byte_count);
    if (dest->values == NULL) {
        return -1;
    }
    memcpy(dest->values, src->values, byte_count);
    return 0;
}

static void free_zip_result(ZipResult *result)
{
    if (result == NULL) {
        return;
    }
    if (result->pairs != NULL) {
        for (size_t i = 0U; i < result->length; i++) {
            free(result->pairs[i].first.values);
            free(result->pairs[i].second.values);
        }
        free(result->pairs);
        result->pairs = NULL;
    }
    result->length = 0U;
}

static int zip_lists(const List *a, size_t a_count,
                     const List *b, size_t b_count,
                     ZipResult *result)
{
    size_t min_count;

    if (result == NULL) {
        return -1;
    }
    result->pairs = NULL;
    result->length = 0U;

    if (a == NULL || b == NULL) {
        return -1;
    }

    min_count = (a_count < b_count) ? a_count : b_count;
    if (min_count == 0U) {
        return 0;
    }

    result->pairs = calloc(min_count, sizeof(Pair));
    if (result->pairs == NULL) {
        return -1;
    }
    result->length = min_count;

    for (size_t i = 0U; i < min_count; i++) {
        if (copy_list(&result->pairs[i].first, &a[i]) != 0) {
            free_zip_result(result);
            return -1;
        }
        if (copy_list(&result->pairs[i].second, &b[i]) != 0) {
            free_zip_result(result);
            return -1;
        }
    }
    return 0;
}

static void print_list(const List *list)
{
    printf("[");
    for (size_t i = 0U; i < list->length; i++) {
        printf("%d", list->values[i]);
        if (i + 1U < list->length) {
            printf(", ");
        }
    }
    printf("]");
}

static void print_zip_result(const ZipResult *result)
{
    printf("[");
    for (size_t i = 0U; i < result->length; i++) {
        printf("(");
        print_list(&result->pairs[i].first);
        printf(", ");
        print_list(&result->pairs[i].second);
        printf(")");
        if (i + 1U < result->length) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void)
{
    int a0[] = {1, 2, 3};
    int a1[] = {4, 5};
    int a2[] = {6};
    int b0[] = {7, 8};
    int b1[] = {9, 10, 11};

    List list_a[] = {
        {a0, sizeof(a0) / sizeof(a0[0])},
        {a1, sizeof(a1) / sizeof(a1[0])},
        {a2, sizeof(a2) / sizeof(a2[0])}
    };
    List list_b[] = {
        {b0, sizeof(b0) / sizeof(b0[0])},
        {b1, sizeof(b1) / sizeof(b1[0])}
    };

    ZipResult result;

    if (zip_lists(list_a, sizeof(list_a) / sizeof(list_a[0]),
                  list_b, sizeof(list_b) / sizeof(list_b[0]),
                  &result) != 0) {
        fprintf(stderr, "Failed to zip lists\n");
        return EXIT_FAILURE;
    }

    print_zip_result(&result);
    free_zip_result(&result);

    return EXIT_SUCCESS;
}