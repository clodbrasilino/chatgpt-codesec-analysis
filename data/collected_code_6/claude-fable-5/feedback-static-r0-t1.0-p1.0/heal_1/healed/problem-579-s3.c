#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *arr, size_t len, int value)
{
    for (size_t i = 0; i < len; i++) {
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
    if (tup1 == NULL || tup2 == NULL || result_len == NULL) {
        return NULL;
    }

    size_t max_len = len1 + len2;
    if (max_len < len1) {
        return NULL;
    }

    int *result = NULL;
    size_t count = 0;

    if (max_len > 0) {
        result = malloc(max_len * sizeof(int));
        if (result == NULL) {
            return NULL;
        }
    }

    for (size_t i = 0; i < len1; i++) {
        if (!contains(tup2, len2, tup1[i]) && !contains(result, count, tup1[i])) {
            result[count] = tup1[i];
            count++;
        }
    }

    for (size_t i = 0; i < len2; i++) {
        if (!contains(tup1, len1, tup2[i]) && !contains(result, count, tup2[i])) {
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

    int *result = find_dissimilar(tuple1, len1, tuple2, len2, &result_len);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute dissimilar elements\n");
        return EXIT_FAILURE;
    }

    printf("Dissimilar elements: ");
    for (size_t i = 0; i < result_len; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}