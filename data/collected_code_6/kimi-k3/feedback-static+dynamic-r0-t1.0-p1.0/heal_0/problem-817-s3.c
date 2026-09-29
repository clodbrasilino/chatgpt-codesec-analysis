#include <stdio.h>
#include <stdlib.h>

int *find_divisible_numbers(const int *numbers, size_t count, int m, int n, size_t *result_count)
{
    int *result;
    size_t i;
    size_t index = 0;

    if (numbers == NULL || result_count == NULL || m == 0 || n == 0)
    {
        return NULL;
    }

    result = malloc(count * sizeof(int));
    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < count; i++)
    {
        if (numbers[i] % m == 0 || numbers[i] % n == 0)
        {
            result[index] = numbers[i];
            index++;
        }
    }

    *result_count = index;
    return result;
}

int main(void)
{
    int numbers[] = {10, 15, 20, 25, 30, 35, 40};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    int m = 5;
    int n = 10;
    size_t result_count = 0;
    size_t i;
    int *result = find_divisible_numbers(numbers, count, m, n, &result_count);

    if (result == NULL)
    {
        fprintf(stderr, "Error: failed to find divisible numbers\n");
        return EXIT_FAILURE;
    }

    printf("Numbers divisible by %d or %d:\n", m, n);
    for (i = 0; i < result_count; i++)
    {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}