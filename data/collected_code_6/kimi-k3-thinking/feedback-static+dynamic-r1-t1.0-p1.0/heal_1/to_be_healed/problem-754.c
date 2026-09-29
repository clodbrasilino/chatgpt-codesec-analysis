#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t find_common_index_elements(const int *list1, const int *list2, const int *list3,
                                  size_t size1, size_t size2, size_t size3,
                                  int **result)
{
    size_t min_size;
    size_t count = 0;
    size_t i;
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

    for (i = 0; i < min_size; i++)
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
    int list2[] = {1, 5, 3, 7, 5};
    int list3[] = {1, 9, 3, 8, 5};
    int *result = NULL;
    size_t count;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    size_t i;

    count = find_common_index_elements(list1, list2, list3,
                                       sizeof(list1) / sizeof(list1[0]),
                                       sizeof(list2) / sizeof(list2[0]),
                                       sizeof(list3) / sizeof(list3[0]),
                                       &result);

    if (count > 0 && result != NULL)
    {
        printf("Common index elements: ");
        for (i = 0; i < count; i++)
        {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    else
    {
        printf("No common index elements found.\n");
    }

    free(result);

    return 0;
}