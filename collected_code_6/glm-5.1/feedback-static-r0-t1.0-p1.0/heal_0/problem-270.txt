#include <stdio.h>
#include <stdlib.h>

int sum_even_at_even_positions(const int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < size; i++) {
        if ((i % 2 == 0) && (arr[i] % 2 == 0)) {
            sum += arr[i];
        }
    }
    return sum;
}

int main(void) {
    int data[] = {1, 2, 4, 5, 6, 8, 10, 11};
    size_t size = sizeof(data) / sizeof(data[0]);

    int result = sum_even_at_even_positions(data, size);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}