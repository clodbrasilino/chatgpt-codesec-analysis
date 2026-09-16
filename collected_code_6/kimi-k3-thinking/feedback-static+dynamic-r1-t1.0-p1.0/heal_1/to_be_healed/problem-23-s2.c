#include <stdio.h>
#include <stdlib.h>

int max_list_sum(const int *const *lists, const size_t *sizes, size_t num_lists, long long *result)
{
    size_t i;
    size_t j;
    long long max_sum;
    /* Possible weaknesses found:
     *  The scope of the variable 'current_sum' can be reduced. [variableScope]
     */
    long long current_sum;

    if (lists == NULL || sizes == NULL || result == NULL)
    {
        return -1;
    }

    if (num_lists == 0)
    {
        return -1;
    }

    max_sum = 0;

    for (i = 0; i < num_lists; i++)
    {
        if (sizes[i] > 0 && lists[i] == NULL)
        {
            return -1;
        }

        current_sum = 0;

        for (j = 0; j < sizes[i]; j++)
        {
            current_sum += (long long)lists[i][j];
        }

        if (i == 0 || current_sum > max_sum)
        {
            max_sum = current_sum;
        }
    }

    *result = max_sum;
    return 0;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4};
    int list2[] = {10, 20, 30};
    int list3[] = {-5, -10, -3};
    int list4[] = {7, 8};

    const int *lists[4];
    size_t sizes[4];
    size_t num_lists;
    long long result;
    int status;

    lists[0] = list1;
    lists[1] = list2;
    lists[2] = list3;
    lists[3] = list4;

    sizes[0] = sizeof(list1) / sizeof(list1[0]);
    sizes[1] = sizeof(list2) / sizeof(list2[0]);
    sizes[2] = sizeof(list3) / sizeof(list3[0]);
    sizes[3] = sizeof(list4) / sizeof(list4[0]);

    num_lists = sizeof(lists) / sizeof(lists[0]);

    result = 0;

    status = max_list_sum(lists, sizes, num_lists, &result);

    if (status != 0)
    {
        fprintf(stderr, "Error: invalid input provided\n");
        return EXIT_FAILURE;
    }

    printf("Maximum sum: %lld\n", result);

    return EXIT_SUCCESS;
}