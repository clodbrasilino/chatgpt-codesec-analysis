#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int *modulo_lists(const int *list1, const int *list2, size_t size);

int *modulo_lists(const int *list1, const int *list2, size_t size)
{
    size_t i;
    int *result;

    if (list1 == NULL || list2 == NULL || size == 0)
    {
        return NULL;
    }

    if (size > SIZE_MAX / sizeof(int))
    {
        return NULL;
    }

    result = (int *)malloc(size * sizeof(int));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < size; i++)
    {
        if (list2[i] == 0 || (list1[i] == INT_MIN && list2[i] == -1))
        {
            free(result);
            result = NULL;
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    return result;
}

int main(void)
{
    int list1[] = {10, 20, 30, 40, 50};
    int list2[] = {3, 4, 7, 6, 8};
    size_t size = sizeof(list1) / sizeof(list1[0]);
    int *result;
    size_t i;

    result = modulo_lists(list1, list2, size);
    if (result == NULL)
    {
        fprintf(stderr, "Error: modulo operation failed\n");
        return EXIT_FAILURE;
    }

    printf("Result: ");
    for (i = 0; i < size; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}