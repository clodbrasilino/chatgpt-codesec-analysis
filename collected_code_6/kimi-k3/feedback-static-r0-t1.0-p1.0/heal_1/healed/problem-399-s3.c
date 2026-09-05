#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *xor_tuples(const int *t1, const int *t2, size_t len)
{
    int *result;
    size_t i;

    if (t1 == NULL || t2 == NULL || len == 0)
    {
        return NULL;
    }

    result = (int *)malloc(len * sizeof(int));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len; i++)
    {
        result[i] = t1[i] ^ t2[i];
    }

    return result;
}

int main(void)
{
    const int t1[] = {10, 4, 6, 9};
    const int t2[] = {5, 2, 3, 3};
    size_t len = sizeof(t1) / sizeof(t1[0]);
    int *res;
    size_t i;

    res = xor_tuples(t1, t2, len);
    if (res == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < len; i++)
    {
        printf("%d", res[i]);
        if (i < len - 1)
        {
            printf(", ");
        }
    }
    printf(")\n");

    free(res);
    res = NULL;

    return EXIT_SUCCESS;
}