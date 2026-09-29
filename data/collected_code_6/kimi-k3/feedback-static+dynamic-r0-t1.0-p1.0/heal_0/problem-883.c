#include <stdio.h>
#include <stdlib.h>

void find_divisible(const int *arr, size_t size, int m, int n)
{
    size_t i;

    if (arr == NULL || m == 0 || n == 0)
    {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    printf("Numbers divisible by %d and %d:\n", m, n);
    for (i = 0; i < size; i++)
    {
        if (arr[i] % m == 0 && arr[i] % n == 0)
        {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

int main(void)
{
    int numbers[] = {10, 15, 20, 30, 40, 45, 60, 75, 90, 100};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int m = 3;
    int n = 5;

    find_divisible(numbers, size, m, n);

    return 0;
}