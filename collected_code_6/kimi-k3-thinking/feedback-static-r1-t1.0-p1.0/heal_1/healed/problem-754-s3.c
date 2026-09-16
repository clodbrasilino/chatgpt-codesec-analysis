#include <stdio.h>
#include <stdlib.h>

size_t find_common_index_elements(const int *list1, const int *list2, const int *list3,
                                  size_t size1, size_t size2, size_t size3,
                                  int **result);

size_t find_common_index_elements(const int *list1, const int *list2, const int *list3,
                                  size_t size1, size_t size2, size_t size3,
                                  int **result)
{
    size_t min_size;
    size_t count;
    int *temp;

    if (list1 == NULL || list2 == NULL || list3 == NULL || result == NULL)
    {
        return 0;
    }

    *result = NULL;

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
        return 0;
    }

    temp = (int *)malloc(min_size * sizeof(int));
    if (temp == NULL)
    {
        return 0;
    }

    count = 0;
    for (size_t i = 0; i < min_size; i++)
    {
        if (list1[i] == list2[i] && list2[i] == list3[i])
        {
            temp[count] = list1[i];
            count++;
        }
    }

    if (count == 0)
    {
        free(temp);
        return 0;
    }

    *result = temp;
    return count;
}

int main(void)
{
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 9, 3, 8, 5};
    int list3[] = {1, 7, 3, 2, 5};
    int *result = NULL;
    size_t count;

    count = find_common_index_elements(list1, list2, list3,
                                       sizeof(list1) / sizeof(list1[0]),
                                       sizeof(list2) / sizeof(list2[0]),
                                       sizeof(list3) / sizeof(list3[0]),
                                       &result);

    if (result != NULL && count > 0)
    {
        printf("Common index elements: ");
        for (size_t i = 0; i < count; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
        result = NULL;
    }
    else
    {
        printf("No common index elements found.\n");
    }

    return 0;
}