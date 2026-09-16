#include <stdio.h>
#include <stdlib.h>

void countConsecutiveDuplicates(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }

    size_t i = 0;
    while (i < size) {
        int current = arr[i];
        size_t count = 1;
        while (i + count < size && arr[i + count] == current) {
            count++;
        }
        printf("Element %d appears %zu consecutive time(s)\n", current, count);
        i += count;
    }
}

int main(void) {
    int numbers[] = {1, 1, 2, 2, 2, 3, 4, 4, 5, 5, 5, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    countConsecutiveDuplicates(numbers, size);

    return 0;
}