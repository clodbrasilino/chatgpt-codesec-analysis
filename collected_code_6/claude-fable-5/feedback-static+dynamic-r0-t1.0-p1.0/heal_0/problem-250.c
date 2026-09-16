#include <stdio.h>
#include <stddef.h>

size_t count_occurrences(const int *tuple, size_t length, int element)
{
    size_t count = 0;
    size_t i;

    if (tuple == NULL)
    {
        return 0;
    }

    for (i = 0; i < length; i++)
    {
        if (tuple[i] == element)
        {
            count++;
        }
    }

    return count;
}

int main(void)
{
    int tuple[] = {1, 3, 5, 3, 7, 3, 9, 2, 3};
    size_t length = sizeof(tuple) / sizeof(tuple[0]);
    int element = 3;
    size_t result;

    result = count_occurrences(tuple, length, element);

    if (printf("Element %d occurs %zu times in the tuple.\n", element, result) < 0)
    {
        return 1;
    }

    return 0;
}