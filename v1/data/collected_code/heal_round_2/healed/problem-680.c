#include <stdio.h>
#include <stdbool.h>

bool isIncreasing(const int numbers[], int length) {
    for (int i = 1; i < length; i++) {
        if (numbers[i] <= numbers[i - 1]) {
            return false;
        }
    }
    return true;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    if (isIncreasing(numbers, length)) {
        printf("The array is increasing.\n");
    } else {
        printf("The array is not increasing.\n");
    }

    return 0;
}