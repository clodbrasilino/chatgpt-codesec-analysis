#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected [13, 14], got <no output>
  *  test case 0 failed: expected [4, 5], got <no output>
  *  test case 1 failed: expected [3, 4], got <no output>
  */

int *find_similar_elements(const int *list1, size_t len1,
                           const int *list2, size_t len2,
                           size_t *result_len)
{
    int *result = NULL;
    size_t count = 0;
    size_t i;
    size_t j;
    size_t k;

    if (result_len == NULL) {
        return NULL;
    }

    *result_len = 0;

    if (list1 == NULL || list2 == NULL || len1 == 0 || len2 == 0) {
        return NULL;
    }

    result = malloc(len1 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < len1; i++) {
        int found = 0;
        for (j = 0; j < len2; j++) {
            if (list1[i] == list2[j]) {
                found = 1;
                break;
            }
        }
        if (found == 1) {
            int duplicate = 0;
            for (k = 0; k < count; k++) {
                if (result[k] == list1[i]) {
                    duplicate = 1;
                    break;
                }
            }
            if (duplicate == 0) {
                result[count] = list1[i];
                count++;
            }
        }
    }

    if (count == 0) {
        free(result);
        return NULL;
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
    int *similar = NULL;

    similar = find_similar_elements(tuple1, len1, tuple2, len2, &result_len);

    if (similar == NULL || result_len == 0) {
        if (printf("No similar elements found.\n") < 0) {
            free(similar);
            return EXIT_FAILURE;
        }
        free(similar);
        return EXIT_SUCCESS;
    }

    if (printf("Similar elements: ") < 0) {
        free(similar);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_len; i++) {
        if (printf("%d ", similar[i]) < 0) {
            free(similar);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(similar);
        return EXIT_FAILURE;
    }

    free(similar);
    return EXIT_SUCCESS;
}