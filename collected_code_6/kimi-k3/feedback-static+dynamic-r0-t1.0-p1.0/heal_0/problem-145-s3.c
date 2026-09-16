#include <stdio.h>
#include <limits.h>
#include <stddef.h>

int find_max_difference(const int *array, size_t size)
{
    if (array == NULL || size < 2)
    {
        return 0;
    }

    int min_element = array[0];
    int max_difference = 0;

    for (size_t i = 1; i < size; i++)
    {
        int current_difference = array[i] - min_element;
        if (current_difference > max_difference)
        {
            max_difference = current_difference;
        }
        if (array[i] < min_element)
        {
            min_element = array[i];
        }
    }

    return max_difference;
}

int main(void)
{
    int array[] = {2, 3, 10, 6, 4, 8, 1};
    size_t size = sizeof(array) / sizeof(array[0]);

    int result = find_max_difference(array, size);
    printf("Maximum difference: %d\n", result);

    return 0;
}