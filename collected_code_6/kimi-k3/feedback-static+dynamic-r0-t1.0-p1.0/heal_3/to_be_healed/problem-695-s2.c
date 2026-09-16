#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected True, got <no output>
  *  test case 1 failed: expected False, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

bool check_greater(const int *first, const int *second, size_t size)
{
    size_t i;

    if (first == NULL || second == NULL)
    {
        return false;
    }

    for (i = 0; i < size; i++)
    {
        if (second[i] <= first[i])
        {
            return false;
        }
    }

    return true;
}

int main(void)
{
    int first[] = {1, 2, 3, 4, 5};
    const int second[] = {2, 3, 4, 5, 6};
    size_t size = sizeof(first) / sizeof(first[0]);
    bool result;

    result = check_greater(first, second, size);

    if (result)
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }

    return 0;
}