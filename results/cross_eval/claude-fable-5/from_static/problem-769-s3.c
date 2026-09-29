#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static bool contains(const int *list, size_t size, int value)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

static int *list_difference(const int *list1, size_t size1,
                            const int *list2, size_t size2,
                            size_t *result_size)
{
    int *result;
    size_t i;
    size_t count = 0;

    if (list1 == NULL || result_size == NULL) {
        return NULL;
    }
    if (size2 > 0 && list2 == NULL) {
        return NULL;
    }
    if (size1 == 0) {
        *result_size = 0;
        return NULL;
    }

    result = malloc(size1 * sizeof(int));
    if (result == NULL) {
        return NULL;
    }

    for (i = 0; i < size1; i++) {
        if (!contains(list2, size2, list1[i])) {
            result[count] = list1[i];
            count++;
        }
    }

    *result_size = count;

    if (count == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6};
    int list2[] = {2, 4, 6};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t result_size = 0;
    size_t i;
    int *diff;

    diff = list_difference(list1, size1, list2, size2, &result_size);

    if (diff == NULL && result_size == 0) {
        if (printf("Difference is empty or an error occurred.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (printf("Difference: ") < 0) {
        free(diff);
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_size; i++) {
        if (printf("%d ", diff[i]) < 0) {
            free(diff);
            return EXIT_FAILURE;
        }
    }

    if (printf("\n") < 0) {
        free(diff);
        return EXIT_FAILURE;
    }

    free(diff);
    return EXIT_SUCCESS;
}