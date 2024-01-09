#include <stdio.h>

int multiplyConsecutive(int nums[], int size) {
    int result = 1;
    for (int i = 0; i < size; i++) {
        result *= nums[i];
    }
    return result;
}

int main() {
    int numbers[] = {2, 3, 4, 5, 6};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int product = multiplyConsecutive(numbers, size);
    printf("Product: %d", product);
    return 0;
}