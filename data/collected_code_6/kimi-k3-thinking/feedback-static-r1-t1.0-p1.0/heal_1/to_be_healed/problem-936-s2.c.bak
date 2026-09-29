#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char *key;
    int value;
} Tuple;

static char *duplicate_string(const char *src)
{
    size_t len;
    char *copy;

    if (src == NULL) {
        return NULL;
    }
    len = strlen(src) + 1;
    copy = (char *)malloc(len);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, src, len);
    return copy;
}

static size_t find_key_index(const Tuple *tuples, size_t count, const char *key, const int *used)
{
    size_t i;

    for (i = 0; i < count; i++) {
        if (!used[i] && tuples[i].key != NULL && strcmp(tuples[i].key, key) == 0) {
            return i;
        }
    }
    return count;
}

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const char **order, size_t order_count)
{
    Tuple *result;
    int *used;
    size_t i;
    size_t out;
    size_t idx;

    if (tuple_count == 0) {
        return 0;
    }
    if (tuples == NULL) {
        return -1;
    }
    if (order_count > 0 && order == NULL) {
        return -1;
    }
    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }

    result = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    if (result == NULL) {
        return -1;
    }
    used = (int *)calloc(tuple_count, sizeof(int));
    if (used == NULL) {
        free(result);
        return -1;
    }

    out = 0;
    for (i = 0; i < order_count; i++) {
        if (order[i] == NULL) {
            continue;
        }
        idx = find_key_index(tuples, tuple_count, order[i], used);
        if (idx < tuple_count) {
            result[out] = tuples[idx];
            used[idx] = 1;
            out++;
        }
    }
    for (i = 0; i < tuple_count; i++) {
        if (!used[i]) {
            result[out] = tuples[i];
            out++;
        }
    }

    memcpy(tuples, result, tuple_count * sizeof(Tuple));
    free(result);
    free(used);
    return 0;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tuples[i].key);
    }
    free(tuples);
}

static void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;

    for (i = 0; i < count; i++) {
        printf("(%s, %d)\n", tuples[i].key, tuples[i].value);
    }
}

int main(void)
{
    const char *keys[] = {"apple", "banana", "cherry", "mango"};
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {3, 1, 2, 7};
    const char *order[] = {"banana", "cherry", "apple"};
    size_t tuple_count = sizeof(keys) / sizeof(keys[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);
    Tuple *tuples;
    size_t i;
    int status;

    tuples = (Tuple *)calloc(tuple_count, sizeof(Tuple));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < tuple_count; i++) {
        tuples[i].key = duplicate_string(keys[i]);
        if (tuples[i].key == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free_tuples(tuples, tuple_count);
            return EXIT_FAILURE;
        }
        tuples[i].value = values[i];
    }

    printf("Before:\n");
    print_tuples(tuples, tuple_count);

    status = rearrange_tuples(tuples, tuple_count, order, order_count);
    if (status != 0) {
        fprintf(stderr, "Failed to rearrange tuples\n");
        free_tuples(tuples, tuple_count);
        return EXIT_FAILURE;
    }

    printf("After:\n");
    print_tuples(tuples, tuple_count);

    free_tuples(tuples, tuple_count);
    return EXIT_SUCCESS;
}