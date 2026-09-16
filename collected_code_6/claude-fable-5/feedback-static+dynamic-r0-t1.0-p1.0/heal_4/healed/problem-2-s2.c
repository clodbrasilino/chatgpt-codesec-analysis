#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

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

    qsort(result, count, sizeof(int), compare_ints);

    *result_len = count;
    return result;
}

static int print_result(const int *result, size_t result_len)
{
    size_t i;

    if (result == NULL || result_len == 0) {
        if (printf("[]\n") < 0) {
            return -1;
        }
        return 0;
    }

    if (printf("[") < 0) {
        return -1;
    }

    for (i = 0; i < result_len; i++) {
        if (i > 0) {
            if (printf(", ") < 0) {
                return -1;
            }
        }
        if (printf("%d", result[i]) < 0) {
            return -1;
        }
    }

    if (printf("]\n") < 0) {
        return -1;
    }

    return 0;
}

int main(void)
{
    int test0_a[] = {3, 4, 5, 6};
    int test0_b[] = {5, 7, 4, 10};
    int test1_a[] = {1, 2, 3, 4};
    int test1_b[] = {5, 4, 3, 7};
    int test2_a[] = {11, 12, 14, 13};
    int test2_b[] = {17, 15, 14, 13};
    const int *tests_a[] = {test0_a, test1_a, test2_a};
    const int *tests_b[] = {test0_b, test1_b, test2_b};
    const size_t lens_a[] = {
        sizeof(test0_a) / sizeof(test0_a[0]),
        sizeof(test1_a) / sizeof(test1_a[0]),
        sizeof(test2_a) / sizeof(test2_a[0])
    };
    const size_t lens_b[] = {
        sizeof(test0_b) / sizeof(test0_b[0]),
        sizeof(test1_b) / sizeof(test1_b[0]),
        sizeof(test2_b) / sizeof(test2_b[0])
    };
    size_t num_tests = sizeof(tests_a) / sizeof(tests_a[0]);
    size_t t;

    for (t = 0; t < num_tests; t++) {
        size_t result_len = 0;
        int *similar = find_similar_elements(tests_a[t], lens_a[t],
                                             tests_b[t], lens_b[t],
                                             &result_len);

        if (print_result(similar, result_len) != 0) {
            free(similar);
            return EXIT_FAILURE;
        }

        free(similar);

        if (fflush(stdout) != 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}