#include <stdio.h>

int calculate_sum(int* array, int start_index, int end_index, int array_size) {
    int sum = 0;

    if (array == NULL || start_index < 0 || end_index >= array_size || start_index > end_index) {
        return -1;
    }

    for (int i = start_index; i <= end_index; i++) {
        sum += array[i];
    }

    return sum;
}

int main() {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int array_size = sizeof(array) / sizeof(int);

    int start_index = 2;
    int end_index = 5;

    int sum = calculate_sum(array, start_index, end_index, array_size);

    if (sum == -1) {
        printf("Invalid parameters given to the 'calculate_sum' function.\n");
    } else {
        printf("The sum of elements between indexes %d and %d is: %d\n", start_index, end_index, sum);
    }

    return 0;
}