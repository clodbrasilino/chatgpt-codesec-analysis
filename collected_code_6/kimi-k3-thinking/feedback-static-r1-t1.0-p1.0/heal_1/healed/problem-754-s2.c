#include <stdio.h>
#include <stdlib.h>

int *find_common_index_elements(const int *list1, const int *list2, const int *list3,
                                size_t size1, size_t size2, size_t size3, size_t *result_size)
{
    size_t count;
    size_t min_size;
    int *result;

    if (result_size == NULL)
    {
        return NULL;
    }
    *result_size = 0;

    if (list1 == NULL || list2 == NULL || list3 == NULL)
    {
        return NULL;
    }

    min_size = size1;
    if (size2 < min_size)
    {
        min_size = size2;
    }
    if (size3 < min_size)
    {
        min_size = size3;
    }

    if (min_size == 0)
    {
        return NULL;
    }

    result = (int *)malloc(min_size * sizeof(*result));
    if (result == NULL)
    {
        return NULL;
    }

    count = 0;
    for (size_t i = 0; i < min_size; i++)
    {
        if (list1[i] == list2[i] && list2[i] == list3[i])
        {
            result[count] = list1[i];
            count++;
        }
    }

    if (count == 0)
    {
        free(result);
        return NULL;
    }

    *result_size = count;
    return result;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5, 6};
    int list2[] = {1, 9, 3, 8, 5, 7};
    int list3[] = {1, 4, 3, 2, 5, 0};
    size_t result_size = 0;
    int *result;

    result = find_common_index_elements(list1, list2, list3,
                                        sizeof(list1) / sizeof(list1[0]),
                                        sizeof(list2) / sizeof(list2[0]),
                                        sizeof(list3) / sizeof(list3[0]),
                                        &result_size);

    if (result == NULL)
    {
        printf("No common index elements found.\n");
    }
    else
    {
        printf("Common index elements: ");
        for (size_t i = 0; i < result_size; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    return 0;
}