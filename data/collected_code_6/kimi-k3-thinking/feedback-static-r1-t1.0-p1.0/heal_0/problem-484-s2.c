#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int contains_string(char *const *arr, size_t size, const char *str)
{
    size_t i;

    if (arr == NULL || str == NULL) {
        return 0;
    }

    for (i = 0; i < size; i++) {
        if (arr[i] != NULL && strcmp(arr[i], str) == 0) {
            return 1;
        }
    }

    return 0;
}

void free_tuple(char **tuple, size_t size)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    for (i = 0; i < size; i++) {
        free(tuple[i]);
    }
    free(tuple);
}

static int filter_unmatched(char *const *tuple, size_t size,
                            char *const *other, size_t other_size,
                            char ***out, size_t *out_size)
{
    char **filtered;
    size_t i;
    size_t count = 0;

    *out = NULL;
    *out_size = 0;

    if (size == 0) {
        return 0;
    }

    if (tuple == NULL || (other == NULL && other_size > 0) ||
        size > SIZE_MAX / sizeof(*filtered)) {
        return -1;
    }

    filtered = malloc(size * sizeof(*filtered));
    if (filtered == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            continue;
        }
        if (contains_string(other, other_size, tuple[i])) {
            continue;
        }
        filtered[count] = malloc(strlen(tuple[i]) + 1);
        if (filtered[count] == NULL) {
            while (count > 0) {
                count--;
                free(filtered[count]);
            }
            free(filtered);
            return -1;
        }
        strcpy(filtered[count], tuple[i]);
        count++;
    }

    if (count == 0) {
        free(filtered);
        return 0;
    }

    *out = filtered;
    *out_size = count;
    return 0;
}

int remove_matching_tuples(char *const *tuple1, size_t size1,
                           char *const *tuple2, size_t size2,
                           char ***result1, size_t *result_size1,
                           char ***result2, size_t *result_size2)
{
    if (result1 == NULL || result_size1 == NULL ||
        result2 == NULL || result_size2 == NULL) {
        return -1;
    }

    *result1 = NULL;
    *result_size1 = 0;
    *result2 = NULL;
    *result_size2 = 0;

    if (filter_unmatched(tuple1, size1, tuple2, size2,
                         result1, result_size1) != 0) {
        return -1;
    }

    if (filter_unmatched(tuple2, size2, tuple1, size1,
                         result2, result_size2) != 0) {
        free_tuple(*result1, *result_size1);
        *result1 = NULL;
        *result_size1 = 0;
        return -1;
    }

    return 0;
}

static void print_tuple(char *const *tuple, size_t size)
{
    size_t i;

    printf("(");
    for (i = 0; i < size; i++) {
        printf("%s%s", tuple[i], (i + 1 < size) ? ", " : "");
    }
    printf(")\n");
}

int main(void)
{
    char *tuple1[] = {"apple", "banana", "cherry", "date"};
    char *tuple2[] = {"banana", "date", "fig", "grape"};
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    char **result1 = NULL;
    char **result2 = NULL;
    size_t result_size1 = 0;
    size_t result_size2 = 0;

    printf("Tuple 1: ");
    print_tuple(tuple1, size1);
    printf("Tuple 2: ");
    print_tuple(tuple2, size2);

    if (remove_matching_tuples(tuple1, size1, tuple2, size2,
                               &result1, &result_size1,
                               &result2, &result_size2) != 0) {
        fprintf(stderr, "Error: failed to remove matching tuples\n");
        return EXIT_FAILURE;
    }

    printf("Tuple 1 after removal: ");
    print_tuple(result1, result_size1);
    printf("Tuple 2 after removal: ");
    print_tuple(result2, result_size2);

    free_tuple(result1, result_size1);
    free_tuple(result2, result_size2);

    return EXIT_SUCCESS;
}