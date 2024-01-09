#include <stdio.h>

void printPositiveNumbers(int* numbers, int length) {
    for (int i = 0; i < length; i++) {
        if (numbers[i] > 0) {
            printf("%d\n", numbers[i]);
        }
    }
}

int main() {
    int numbers[] = {-1, 5, -3, 10, -7};
    int length = sizeof(numbers) / sizeof(numbers[0]);

    printPositiveNumbers(numbers, length);
    
    return 0;
}