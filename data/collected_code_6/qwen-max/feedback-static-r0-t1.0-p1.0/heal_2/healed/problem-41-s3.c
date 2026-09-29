#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_even(int num) {
    return (num % 2 == 0);
}

void filter_even_numbers(const int *array, int size, int **result, int *result_size) {
    int even_count = 0;
    for (int i = 0; i < size; i++) {
        if (is_even(array[i])) {
            even_count++;
        }
    }

    *result = (int *)malloc(even_count * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }

    *result_size = even_count;
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (is_even(array[i])) {
            (*result)[index++] = array[i];
        }
    }
}

int main() {
    const int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int size = 10;
    int *even_numbers;
    int even_size;

    filter_even_numbers(numbers, size, &even_numbers, &even_size);

    for (int i = 0; i < even_size; i++) {
        printf("%d ", even_numbers[i]);
    }

    free(even_numbers);
    return 0;
}