#include <stdio.h>
#include <stddef.h>

size_t count_in_range(const int *list, size_t size, int min_val, int max_val) {
    size_t count = 0;

    if (list == NULL || size == 0 || min_val > max_val) {
        return 0;
    }

    for (size_t i = 0; i < size; i++) {
        if (list[i] >= min_val && list[i] <= max_val) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const int numbers[] = { 4, 7, 12, 15, 18, 21, 25, 30 };
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int min_range = 10;
    int max_range = 20;

    size_t count = count_in_range(numbers, size, min_range, max_range);
    
    printf("%zu\n", count);

    return 0;
}