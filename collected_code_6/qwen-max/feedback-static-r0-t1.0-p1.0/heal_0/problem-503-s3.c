#include <stdio.h>
#include <stdlib.h>

int add_consecutive_numbers(int *numbers, int count) {
    if (numbers == NULL || count <= 0) {
        return 0;
    }
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int size = sizeof(list) / sizeof(list[0]);
    int result = add_consecutive_numbers(list, size);
    printf("Sum: %d\n", result);
    return 0;
}