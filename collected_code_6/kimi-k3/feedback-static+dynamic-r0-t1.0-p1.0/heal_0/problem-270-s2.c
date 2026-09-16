#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

long long sumEvenAtEvenPositions(const int *arr, size_t size)
{
    long long sum = 0;
    size_t i;

    if (arr == NULL)
    {
        return 0;
    }

    for (i = 0; i < size; i += 2)
    {
        if (arr[i] % 2 == 0)
        {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void)
{
    size_t n;
    size_t i;
    int *arr;
    long long result;

    printf("Enter the number of elements: ");
    if (scanf("%zu", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n == 0)
    {
        printf("Sum: 0\n");
        return EXIT_SUCCESS;
    }

    arr = malloc(n * sizeof(*arr));
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Enter %zu elements: ", n);
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return EXIT_FAILURE;
        }
    }

    result = sumEvenAtEvenPositions(arr, n);
    printf("Sum of even numbers at even positions: %lld\n", result);

    free(arr);
    return EXIT_SUCCESS;
}