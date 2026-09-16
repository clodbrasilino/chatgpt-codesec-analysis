#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *modulo_lists(const int *list1, const int *list2, size_t size)
{
    if (list1 == NULL || list2 == NULL || size == 0)
    {
        return NULL;
    }

    int *result = malloc(size * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < size; i++)
    {
        if (list2[i] == 0 || (list1[i] == INT_MIN && list2[i] == -1))
        {
            free(result);
            return NULL;
        }
        result[i] = list1[i] % list2[i];
    }

    return result;
}

int main(void)
{
    int list1[] = {10, 20, 30, 40, 50};
    int list2[] = {3, 7, 9, 6, 11};
    size_t size = sizeof(list1) / sizeof(list1[0]);

    int *result = modulo_lists(list1, list2, size);
    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to compute modulo division\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < size; i++)
    {
        printf("%d %% %d = %d\n", list1[i], list2[i], result[i]);
    }

    free(result);
    result = NULL;

    return EXIT_SUCCESS;
}