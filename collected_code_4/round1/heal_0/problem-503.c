#include <stdio.h>
#include <stdlib.h>

int consecutiveSum(int* list, size_t len) {
    int sum = 0;
    for (size_t i = 0; i < len; i++) {
        sum += list[i];
    }
    return sum;
}

int main () {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = consecutiveSum(numbers, length);

    printf("Sum of consecutive numbers is = %d\n", result);
    return 0;
}