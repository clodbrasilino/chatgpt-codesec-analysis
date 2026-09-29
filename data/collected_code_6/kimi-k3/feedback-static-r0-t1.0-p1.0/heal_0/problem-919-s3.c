#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int multiply_list(const int *list, size_t size, int *result)
{
    size_t i;
    int product;

    if (list == NULL || result == NULL || size == 0)
    {
        return -1;
    }

    product = 1;
    for (i = 0; i < size; i++)
    {
        if (list[i] != 0 && product > INT_MAX / list[i])
        {
            return -1;
        }
        product *= list[i];
    }

    *result = product;
    return 0;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    int result;

    if (multiply_list(list, size, &result) == 0)
    {
        printf("Product: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error: multiplication failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}