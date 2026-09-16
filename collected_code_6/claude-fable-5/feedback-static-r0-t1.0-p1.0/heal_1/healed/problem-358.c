#include <stdio.h>
#include <stdlib.h>

int modulo_lists(const int *list1, const int *list2, int *result, size_t n)
{
    size_t i;

    if (list1 == NULL || list2 == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (list2[i] == 0) {
            return -1;
        }
        result[i] = list1[i] % list2[i];
    }

    return 0;
}

int main(void)
{
    const int list1[] = {10, 4, 5, 6};
    const int list2[] = {5, 6, 7, 9};
    size_t n = sizeof(list1) / sizeof(list1[0]);
    int *result;
    size_t i;

    result = malloc(n * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (modulo_lists(list1, list2, result, n) != 0) {
        fprintf(stderr, "Modulo operation failed\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        printf("%d", result[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}