#include <stdio.h>
#include <stdlib.h>

int sum_between_indices(int *numbers, int start_index, int end_index) {
    if (start_index < 0 || end_index >= 0 && end_index < start_index) {
        return -1;
    }

    int sum = 0;
    for (int i = start_index; i <= end_index; ++i) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    int start_index, end_index;
    printf("Enter the start index: ");
    scanf("%d", &start_index);
    printf("Enter the end index: ");
    scanf("%d", &end_index);

    int result = sum_between_indices(numbers, start_index, end_index);
    if (result == -1) {
        printf("Invalid indices.\n");
    } else {
        printf("Sum between indices %d and %d is: %d\n", start_index, end_index, result);
    }

    return 0;
}