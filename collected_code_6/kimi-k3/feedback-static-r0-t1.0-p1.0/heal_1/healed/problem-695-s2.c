#include <stdio.h>
#include <stdlib.h>

int check_greater(const int *first, const int *second, size_t size)
{
    size_t i;

    if (first == NULL || second == NULL)
    {
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        if (second[i] <= first[i])
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int first[] = {1, 2, 3, 4, 5};
    const int second[] = {2, 3, 4, 5, 6};
    size_t size = sizeof(first) / sizeof(first[0]);
    int result;

    result = check_greater(first, second, size);

    if (result == 1)
    {
        printf("All elements in the second tuple are greater than the corresponding elements in the first tuple.\n");
    }
    else if (result == 0)
    {
        printf("Not all elements in the second tuple are greater than the corresponding elements in the first tuple.\n");
    }
    else
    {
        printf("Invalid input.\n");
    }

    return 0;
}