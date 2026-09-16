#include <stdio.h>
#include <stdlib.h>

void print_positive_numbers(const int *list, size_t count)
{
    size_t i;

    if (list == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        if (list[i] > 0)
        {
            printf("%d\n", list[i]);
        }
    }
}

int main(void)
{
    int numbers[] = {3, -1, 4, 0, -5, 9, -2, 7};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_positive_numbers(numbers, count);

    return EXIT_SUCCESS;
}