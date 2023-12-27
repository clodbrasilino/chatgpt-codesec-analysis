#include <stdio.h>

int findEven(const int *numbers, int size) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] % 2 == 0) {
            return numbers[i];
        }
    }
    return -1; 
}

int main() {
    int numbers[] = {1, 3, 5, 2, 4, 6, 7, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int firstEven = findEven(numbers, size);
    printf("First even number: %d\n", firstEven);

    return 0;
}