#include <stdio.h>
#include <stdlib.h>

int contains(const int *list, size_t size, int value)
{
    size_t i;
    for (i = 0; i < size; i++) {
        if (list[i] == value) {
            return 1;
        }
    }
    return 0;
}

int *list_difference(const int *list1, size_t size1,
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
        *result_size = 0;
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
    int list1[] = { 1, 2, 3, 4, 5, 6 };
    int list2[] = { 2, 4, 6 };
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    size_t diff_size = 0;
    size_t i;
    int *diff;

    diff = list_difference(list1, size1, list2, size2, &diff_size);

    if (diff == NULL && diff_size > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Difference: ");
    for (i = 0; i < diff_size; i++) {
        printf("%d ", diff[i]);
    }
    printf("\n");

    free(diff);
    return EXIT_SUCCESS;
}