#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    size_t frequency;
} Tuple;

int assign_frequency(Tuple *tuples, size_t length)
{
    if (tuples == NULL)
    {
        return -1;
    }

    for (size_t i = 0; i < length; i++)
    {
        size_t count = 0;
        for (size_t j = 0; j < length; j++)
        {
            if (tuples[i].value == tuples[j].value)
            {
                count++;
            }
        }
        tuples[i].frequency = count;
    }

    return 0;
}

int main(void)
{
    Tuple tuples[] = {
        {10, 0}, {20, 0}, {10, 0}, {30, 0},
        {20, 0}, {10, 0}, {40, 0}, {20, 0}
    };
    const size_t length = sizeof(tuples) / sizeof(tuples[0]);

    if (assign_frequency(tuples, length) != 0)
    {
        fprintf(stderr, "Error: failed to assign frequencies\n");
        return EXIT_FAILURE;
    }

    printf("Value\tFrequency\n");
    for (size_t i = 0; i < length; i++)
    {
        printf("%d\t%zu\n", tuples[i].value, tuples[i].frequency);
    }

    return EXIT_SUCCESS;
}