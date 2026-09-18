#include <stdio.h>

long long multiply(int* array, int size) {
    int i;
    long long result;
    if (array == NULL || size <= 0) {
        printf("Invalid input\n");
        return -1;
    }
    result = array[0];
    for (i = 1; i < size; i++) {
        result *= array[i];
    }
    return result;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    long long result = multiply(numbers, size);
    printf("The product of consecutive numbers is: %lld\n", result);
    return 0;
}