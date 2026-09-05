#include <stdio.h>
#include <stdlib.h>

int sum_negative(const int *numbers, size_t count) {
    if (numbers == NULL || count == 0) {
        return 0;
    }

    int sum = 0;
    for (size_t i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            sum += numbers[i];
        }
    }

    return sum;
}

int main(void) {
    int data[] = {5, -2, 0, -7, 3, -1};
    size_t count = sizeof(data) / sizeof(data[0]);

    int result = sum_negative(data, count);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}