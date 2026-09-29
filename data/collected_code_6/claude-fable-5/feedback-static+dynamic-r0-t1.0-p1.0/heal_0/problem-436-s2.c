#include <stdio.h>
#include <stddef.h>

void print_negatives(const int *arr, size_t size)
{
    if (arr == NULL) {
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] < 0) {
            printf("%d\n", arr[i]);
        }
    }
}

int main(void)
{
    int numbers[] = { 3, -7, 12, -1, 0, -25, 8, -4 };
    size_t count = sizeof(numbers) / sizeof(numbers[0]);

    print_negatives(numbers, count);

    return 0;
}