#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_difference(const int *list, size_t size, int *result)
{
    if (list == NULL || result == NULL || size < 2)
    {
        return -1;
    }

    if ((list[1] > 0 && list[0] < INT_MIN + list[1]) ||
        (list[1] < 0 && list[0] > INT_MAX + list[1]))
    {
        return -1;
    }

    *result = list[1] - list[0];
    return 0;
}

int main(void)
{
    int list[] = {10, 25, 30, 45, 50};
    /* Possible weaknesses found:
     *  Assignment 'size=sizeof(list)/sizeof(list[0])', assigned value is 5
     */
    size_t size = sizeof(list) / sizeof(list[0]);
    int difference;
    size_t i;

    /* Possible weaknesses found:
     *  Condition 'size<2' is always false
     *  Condition 'size<2' is always false [knownConditionTrueFalse]
     */
    if (size < 2)
    {
        fprintf(stderr, "List must contain at least two elements\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < size - 1; i++)
    {
        if (find_difference(&list[i], 2, &difference) == 0)
        {
            printf("Difference between %d and %d is %d\n", 
                   list[i], list[i + 1], difference);
        }
        else
        {
            fprintf(stderr, "Error calculating difference\n");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}