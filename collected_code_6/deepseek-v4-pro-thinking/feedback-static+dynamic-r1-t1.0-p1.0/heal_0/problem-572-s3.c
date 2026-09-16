#include <stdio.h>
#include <stdlib.h>

static int remove_two_duplicate_numbers_from_list(int *list, size_t *size)
{
    if (size == NULL)
        return 0;
    if (*size == 0)
        return 1;
    if (list == NULL)
        return 0;
    if (*size > (size_t)-1 / sizeof(int))
        return 0;

    int *result = malloc(*size * sizeof(int));
    if (result == NULL)
        return 0;

    size_t new_size = 0;

    for (size_t i = 0; i < *size; ++i)
    {
        int seen = 0;
        for (size_t k = 0; k < i; ++k)
        {
            if (list[k] == list[i])
            {
                seen = 1;
                break;
            }
        }
        if (seen)
            continue;

        size_t count = 0;
        for (size_t j = 0; j < *size; ++j)
        {
            if (list[j] == list[i])
                ++count;
        }

        if (count != 2)
        {
            for (size_t j = 0; j < *size; ++j)
            {
                if (list[j] == list[i])
                    result[new_size++] = list[j];
            }
        }
    }

    for (size_t i = 0; i < new_size; ++i)
        list[i] = result[i];

    *size = new_size;
    free(result);
    return 1;
}

int remove_two_duplicate_numbers_from_lists(int **lists, size_t *sizes, size_t list_count)
{
    if (list_count == 0)
        return 1;
    if (lists == NULL || sizes == NULL)
        return 0;

    for (size_t i = 0; i < list_count; ++i)
    {
        if (!remove_two_duplicate_numbers_from_list(lists[i], &sizes[i]))
            return 0;
    }

    return 1;
}

int main(void)
{
    int list1[] = {1, 2, 2, 3, 4, 4, 5};
    int list2[] = {1, 1, 2, 3, 4, 5, 5};
    int list3[] = {2, 3, 4, 4, 5, 6, 6};

    int *lists[] = {list1, list2, list3};
    size_t sizes[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };
    size_t list_count = sizeof(lists) / sizeof(lists[0]);

    if (!remove_two_duplicate_numbers_from_lists(lists, sizes, list_count))
        return 1;

    for (size_t i = 0; i < list_count; ++i)
    {
        for (size_t j = 0; j < sizes[i]; ++j)
            printf("%d ", lists[i][j]);
        printf("\n");
    }

    return 0;
}