#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool check_valid(const int *tup, size_t size)
{
    if (tup == NULL || size == 0U)
    {
        return false;
    }

    for (size_t i = 0U; i < size; i++)
    {
        if (tup[i] == 0)
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int tuple1[] = {1, 1, 1, 1};
    int tuple2[] = {1, 0, 1, 1};
    int tuple3[] = {1, 1, 1};

    size_t size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    size_t size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    size_t size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    if (check_valid(tuple1, size1))
    {
        (void)printf("Tuple 1: all values are valid\n");
    }
    else
    {
        (void)printf("Tuple 1: contains invalid values\n");
    }

    if (check_valid(tuple2, size2))
    {
        (void)printf("Tuple 2: all values are valid\n");
    }
    else
    {
        (void)printf("Tuple 2: contains invalid values\n");
    }

    if (check_valid(tuple3, size3))
    {
        (void)printf("Tuple 3: all values are valid\n");
    }
    else
    {
        (void)printf("Tuple 3: contains invalid values\n");
    }

    /* Possible weaknesses found:
     *  Condition 'check_valid(NULL,5U)' is always false
     *  Condition 'check_valid(NULL,5U)' is always false [knownConditionTrueFalse]
     *  Calling function 'check_valid' returns 0
     */
    if (check_valid(NULL, 5U))
    {
        (void)printf("NULL tuple: all values are valid\n");
    }
    else
    {
        (void)printf("NULL tuple: contains invalid values\n");
    }

    return 0;
}