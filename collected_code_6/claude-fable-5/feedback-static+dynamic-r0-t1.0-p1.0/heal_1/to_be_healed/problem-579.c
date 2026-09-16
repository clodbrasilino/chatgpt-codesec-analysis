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
 /* Possible weaknesses found:
  *  test case 2 failed: expected [34, 36, 11, 25], got <no output>
  *  test case 0 failed: expected [3, 6, 7, 10], got <no output>
  *  test case 1 failed: expected [1, 4, 7, 9], got <no output>
  */

static int *find_dissimilar(const int *tuple1, size_t len1,
                            const int *tuple2, size_t len2,
                            size_t *result_len)
{
    if (tuple1 == NULL || tuple2 == NULL || result_len == NULL) {
        return NULL;
    }

    size_t max_len = len1 + len2;
    if (max_len < len1) {
        return NULL;
    }

    int *result = malloc(max_len * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    size_t count = 0;

    for (size_t i = 0; i < len1; i++) {
        if (!contains(tuple2, len2, tuple1[i]) &&
            !contains(result, count, tuple1[i])) {
            result[count] = tuple1[i];
            count++;
        }
    }

    for (size_t i = 0; i < len2; i++) {
        if (!contains(tuple1, len1, tuple2[i]) &&
            !contains(result, count, tuple2[i])) {
            result[count] = tuple2[i];
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