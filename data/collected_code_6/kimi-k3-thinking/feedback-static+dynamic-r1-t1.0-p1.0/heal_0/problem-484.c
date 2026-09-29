#include <stdio.h>
#include <stdlib.h>

static int contains_value(const int *arr, size_t size, int value)
{
    size_t i;

    if (arr == NULL)
    {
        return 0;
    }

    for (i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return 1;
        }
    }

    return 0;
}

int remove_matching(const int *tuple1, size_t size1,
                    const int *tuple2, size_t size2,
                    int **out1, size_t *out_size1,
                    int **out2, size_t *out_size2)
{
    int *res1 = NULL;
    int *res2 = NULL;
    size_t count1 = 0;
    size_t count2 = 0;
    size_t i;

    if (out1 == NULL || out_size1 == NULL || out2 == NULL || out_size2 == NULL)
    {
        return -1;
    }

    *out1 = NULL;
    *out2 = NULL;
    *out_size1 = 0;
    *out_size2 = 0;

    if ((tuple1 == NULL && size1 > 0) || (tuple2 == NULL && size2 > 0))
    {
        return -1;
    }

    if (size1 > 0)
    {
        res1 = (int *)malloc(size1 * sizeof(int));
        if (res1 == NULL)
        {
            return -1;
        }
    }

    if (size2 > 0)
    {
        res2 = (int *)malloc(size2 * sizeof(int));
        if (res2 == NULL)
        {
            free(res1);
            return -1;
        }
    }

    for (i = 0; i < size1; i++)
    {
        if (!contains_value(tuple2, size2, tuple1[i]))
        {
            res1[count1] = tuple1[i];
            count1++;
        }
    }

    for (i = 0; i < size2; i++)
    {
        if (!contains_value(tuple1, size1, tuple2[i]))
        {
            res2[count2] = tuple2[i];
            count2++;
        }
    }

    *out1 = res1;
    *out_size1 = count1;
    *out2 = res2;
    *out_size2 = count2;

    return 0;
}

static void print_tuple(const int *tuple, size_t size)
{
    size_t i;

    printf("(");
    for (i = 0; i < size; i++)
    {
        printf("%d", tuple[i]);
        if (i + 1 < size)
        {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void)
{
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7, 8};
    int *result1 = NULL;
    int *result2 = NULL;
    size_t result_size1 = 0;
    size_t result_size2 = 0;
    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    printf("Original tuple 1: ");
    print_tuple(tuple1, size1);
    printf("Original tuple 2: ");
    print_tuple(tuple2, size2);

    if (remove_matching(tuple1, size1, tuple2, size2,
                        &result1, &result_size1,
                        &result2, &result_size2) != 0)
    {
        fprintf(stderr, "Error: failed to remove matching tuples\n");
        free(result1);
        free(result2);
        return EXIT_FAILURE;
    }

    printf("Tuple 1 after removing matches: ");
    print_tuple(result1, result_size1);
    printf("Tuple 2 after removing matches: ");
    print_tuple(result2, result_size2);

    free(result1);
    free(result2);

    return EXIT_SUCCESS;
}