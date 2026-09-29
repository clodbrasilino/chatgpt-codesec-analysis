#include <stdio.h>

int count_negatives(const int *numbers, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0) {
            ++count;
        }
    }
    return count;
}

int main() {
    int numbers[] = {1, -3, 4, -2, 0, -5};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int negative_count = count_negatives(numbers, length);
    printf("Number of negative numbers: %d\n", negative_count);
    return 0;
}