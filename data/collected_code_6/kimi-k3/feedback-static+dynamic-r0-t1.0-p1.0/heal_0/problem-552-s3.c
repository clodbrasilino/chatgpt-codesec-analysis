#include <stdio.h>
#include <stdlib.h>

int is_linear(const int *sequence, size_t length)
{
    if (sequence == NULL || length < 2)
    {
        return 0;
    }

    int difference = sequence[1] - sequence[0];

    for (size_t i = 2; i < length; i++)
    {
        if (sequence[i] - sequence[i - 1] != difference)
        {
            return 0;
        }
    }

    return 1;
}

int main(void)
{
    int sequence[] = {2, 4, 6, 8, 10};
    size_t length = sizeof(sequence) / sizeof(sequence[0]);

    if (is_linear(sequence, length))
    {
        printf("The sequence is linear.\n");
    }
    else
    {
        printf("The sequence is not linear.\n");
    }

    return 0;
}