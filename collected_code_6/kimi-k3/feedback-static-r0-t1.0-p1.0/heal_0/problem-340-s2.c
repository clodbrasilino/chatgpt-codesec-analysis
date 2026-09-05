#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int sum_of_three_lowest_positive(const int *arr, size_t size, int *result) {
    if (arr == NULL || result == NULL || size < 3) {
        return -1;
    }

    int lowest[3] = {INT_MAX, INT_MAX, INT_MAX};
    int count = 0;

    for (size_t i = 0; i < size; i++) {
        if (arr[i] > 0) {
            if (count < 3) {
                lowest[count++] = arr[i];
                if (count == 3) {
                    if (lowest[0] > lowest[1]) {
                        int temp = lowest[0];
                        lowest[0] = lowest[1];
                        lowest[1] = temp;
                    }
                    if (lowest[1] > lowest[2]) {
                        int temp = lowest[1];
                        lowest[1] = lowest[2];
                        lowest[2] = temp;
                    }
                    if (lowest[0] > lowest[1]) {
                        int temp = lowest[0];
                        lowest[0] = lowest[1];
                        lowest[1] = temp;
                    }
                }
            } else if (arr[i] < lowest[2]) {
                lowest[2] = arr[i];
                if (lowest[1] > lowest[2]) {
                    int temp = lowest[1];
                    lowest[1] = lowest[2];
                    lowest[2] = temp;
                }
                if (lowest[0] > lowest[1]) {
                    int temp = lowest[0];
                    lowest[0] = lowest[1];
                    lowest[1] = temp;
                }
            }
        }
    }

    if (count < 3) {
        return -1;
    }

    if (lowest[0] > INT_MAX - lowest[1] || 
        lowest[0] + lowest[1] > INT_MAX - lowest[2]) {
        return -1;
    }

    *result = lowest[0] + lowest[1] + lowest[2];
    return 0;
}

int main(void) {
    int numbers[] = {5, -2, 8, 1, -3, 9, 2, 7, -1, 3};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);
    int result = 0;

    if (sum_of_three_lowest_positive(numbers, size, &result) == 0) {
        printf("Sum of three lowest positive numbers: %d\n", result);
    } else {
        printf("Error: Not enough positive numbers or invalid input\n");
    }

    return 0;
}