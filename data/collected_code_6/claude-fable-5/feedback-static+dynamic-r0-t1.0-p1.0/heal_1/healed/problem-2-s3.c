#include <stdio.h>
#include <stdlib.h>

int find_similar_elements(const int *list1, size_t len1,
                          const int *list2, size_t len2,
                          int *result, size_t result_capacity,
                          size_t *result_len)
{
    size_t count = 0;
    size_t i;
    size_t j;
    size_t k;

    if ((list1 == NULL) || (list2 == NULL) ||
        (result == NULL) || (result_len == NULL)) {
        return -1;
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
                if (count >= result_capacity) {
                    return -1;
                }
                result[count] = list1[i];
                count++;
            }
        }
    }

    *result_len = count;
    return 0;
}

int main(void)
{
    int tuple1[] = { 3, 4, 5, 6 };
    int tuple2[] = { 5, 7, 4, 10 };
    size_t len1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t len2 = sizeof(tuple2) / sizeof(tuple2[0]);
    int *result = NULL;
    size_t result_len = 0;
    size_t i;
    int status;

    result = malloc(len1 * sizeof(int));
    if (result == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    status = find_similar_elements(tuple1, len1, tuple2, len2,
                                   result, len1, &result_len);
    if (status != 0) {
        (void)fprintf(stderr, "Error finding similar elements\n");
        free(result);
        return EXIT_FAILURE;
    }

    (void)printf("Similar elements: (");
    for (i = 0; i < result_len; i++) {
        (void)printf("%d", result[i]);
        if (i < (result_len - 1U)) {
            (void)printf(", ");
        }
    }
    (void)printf(")\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}