#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int sum_two_lists(const int *list1, const int *list2, size_t size, int **result)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    if (size == 0) {
        *result = NULL;
        return 0;
    }

    *result = malloc(size * sizeof(int));
    if (*result == NULL) {
        return -1;
    }

    for (i = 0; i < size; i++) {
        (*result)[i] = list1[i] + list2[i];
    }

    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {10, 20, 30, 40, 50};
    int *result = NULL;
    size_t size = sizeof(list1) / sizeof(list1[0]);
    size_t i;
    int status;

    if (sizeof(list2) / sizeof(list2[0]) != size) {
        fprintf(stderr, "Error: Lists have different sizes\n");
        return EXIT_FAILURE;
    }

    status = sum_two_lists(list1, list2, size, &result);
    if (status != 0) {
        fprintf(stderr, "Error: Failed to sum lists\n");
        return EXIT_FAILURE;
    }

    printf("Result: ");
    for (i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}