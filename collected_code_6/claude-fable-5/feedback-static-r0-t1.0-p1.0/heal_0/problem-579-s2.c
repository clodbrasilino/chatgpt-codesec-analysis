#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    size_t i;

    if (arr == NULL) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (arr[i] == value) {
            return true;
        }
    }
    return false;
}

static int *find_dissimilar(const int *tup1, size_t len1,
                            const int *tup2, size_t len2,
                            size_t *result_len)
{
    int *result;
    size_t capacity;
    size_t count;
    size_t i;

    if (result_len == NULL) {
        return NULL;
    }
    *result_len = 0;

    if (tup1 == NULL || tup2 == NULL) {
        return NULL;
    }

    if (len1 > (SIZE_MAX / sizeof(int)) - len2) {
        return NULL;
    }

    capacity = len1 + len2;
    if (capacity == 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    count = 0;

    for (i = 0; i < len1; i++) {
        if (!contains(tup2, len2, tup1[i]) &&
            !contains(result, count, tup1[i])) {
            result[count] = tup1[i];
            count++;
        }
    }

    for (i = 0; i < len2; i++) {
        if (!contains(tup1, len1, tup2[i]) &&
            !contains(result, count, tup2[i])) {
            result[count] = tup2[i];
            count++;
        }
    }

    *result_len = count;
    return result;
}

int main(void)
{
    int tuple1[] = {3, 4, 5, 6};
    int tuple2[] = {5, 7, 4, 10};
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t result_len = 0;
    size_t i;
    int *result;

    result = find_dissimilar(tuple1, len1, tuple2, len2, &result_len);
    if (result == NULL) {
        if (fprintf(stderr, "Failed to compute dissimilar elements\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Dissimilar elements: ") < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_len; i++) {
        if (printf("%d ", result[i]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}