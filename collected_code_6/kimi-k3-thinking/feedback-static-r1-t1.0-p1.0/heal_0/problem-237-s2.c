#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_ints(const void *first, const void *second)
{
    const int value_first = *(const int *)first;
    const int value_second = *(const int *)second;

    if (value_first < value_second)
    {
        return -1;
    }
    if (value_first > value_second)
    {
        return 1;
    }
    return 0;
}

int check_similar_occurrences(const int *tuple, size_t length)
{
    if (tuple == NULL || length == 0U)
    {
        return -1;
    }

    if (length > SIZE_MAX / sizeof(int))
    {
        return -1;
    }

    int *sorted = (int *)malloc(length * sizeof(*sorted));
    if (sorted == NULL)
    {
        return -1;
    }

    for (size_t i = 0U; i < length; i++)
    {
        sorted[i] = tuple[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    int status = 1;
    size_t reference_count = 0U;
    size_t current_count = 1U;

    for (size_t i = 1U; i < length; i++)
    {
        if (sorted[i] == sorted[i - 1U])
        {
            current_count++;
        }
        else
        {
            if (reference_count == 0U)
            {
                reference_count = current_count;
            }
            else if (current_count != reference_count)
            {
                status = 0;
                break;
            }
            current_count = 1U;
        }
    }

    if (status == 1 && reference_count != 0U && current_count != reference_count)
    {
        status = 0;
    }

    free(sorted);
    sorted = NULL;

    return status;
}

int main(void)
{
    const int tuple_a[] = {5, 2, 5, 2, 8, 8};
    const int tuple_b[] = {1, 1, 2, 2, 2, 3};
    const int tuple_c[] = {7, 7, 7, 7};

    const int result_a = check_similar_occurrences(tuple_a, sizeof(tuple_a) / sizeof(tuple_a[0]));
    const int result_b = check_similar_occurrences(tuple_b, sizeof(tuple_b) / sizeof(tuple_b[0]));
    const int result_c = check_similar_occurrences(tuple_c, sizeof(tuple_c) / sizeof(tuple_c[0]));

    if (result_a < 0 || result_b < 0 || result_c < 0)
    {
        fprintf(stderr, "Error: invalid input or memory allocation failure.\n");
        return EXIT_FAILURE;
    }

    printf("Tuple A: %s\n", (result_a == 1) ? "all records occur similar times" : "records occur different times");
    printf("Tuple B: %s\n", (result_b == 1) ? "all records occur similar times" : "records occur different times");
    printf("Tuple C: %s\n", (result_c == 1) ? "all records occur similar times" : "records occur different times");

    return EXIT_SUCCESS;
}