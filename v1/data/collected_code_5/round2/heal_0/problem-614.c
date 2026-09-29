#include <stdio.h>

// Function to calculate the cumulative sum.
int cumulativeSum(int numbers[], int size) {
    int sum = 0;
    for(int i = 0; i < size; ++i) {
        sum = sum + numbers[i];
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers)/sizeof(numbers[0]);
    int sum = cumulativeSum(numbers, size);
    printf("The cumulative sum is: %d\n", sum);
    return 0;
}