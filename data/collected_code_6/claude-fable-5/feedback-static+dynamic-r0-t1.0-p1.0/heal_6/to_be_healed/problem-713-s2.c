#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got 0
  *  test case 0 failed: expected True, got 0
  */

bool check_valid(const bool *tup, size_t size)
{
    if (tup == NULL)
    {
        return false;
    }

    if (size == 0U)
    {
        return true;
    }

    for (size_t i = 0U; i < size; i++)
    {
        if (!tup[i])
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    bool tup1[] = { true, true, true, true };
    bool tup2[] = { true, false, true, true };
    bool tup3[] = { true, true, true };

    size_t size1 = sizeof(tup1) / sizeof(tup1[0]);
    size_t size2 = sizeof(tup2) / sizeof(tup2[0]);
    size_t size3 = sizeof(tup3) / sizeof(tup3[0]);

    if (check_valid(tup1, size1))
    {
        (void)printf("Tuple 1: True\n");
    }
    else
    {
        (void)printf("Tuple 1: False\n");
    }

    if (check_valid(tup2, size2))
    {
        (void)printf("Tuple 2: True\n");
    }
    else
    {
        (void)printf("Tuple 2: False\n");
    }

    if (check_valid(tup3, size3))
    {
        (void)printf("Tuple 3: True\n");
    }
    else
    {
        (void)printf("Tuple 3: False\n");
    }

    return 0;
}