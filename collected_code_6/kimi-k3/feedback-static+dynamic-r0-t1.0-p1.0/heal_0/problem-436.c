#include <stdio.h>
#include <stdlib.h>

void print_negative_numbers(const int *list, size_t size)
{
    size_t i;

    if (list == NULL)
    {
        return;
    }

    for (i = 0; i < size; i++)
    {
        if (list[i] < 0)
        {
            printf("%d\n", list[i]);
        }
    }
}

int main(void)
{
    int numbers[] = {5, -3, 8, -12, 0, -7, 15};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_negative_numbers(numbers, count);

    return 0;
}