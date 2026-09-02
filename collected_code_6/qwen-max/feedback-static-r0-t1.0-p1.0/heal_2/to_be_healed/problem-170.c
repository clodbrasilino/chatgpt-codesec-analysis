#include <stdio.h>
#include <stdlib.h>

int sum_range(const int *numbers, int start, int end) {
    int sum = 0;
    if (start >= 0 && end >= start && numbers != NULL) {
        for (int i = start; i <= end; i++) {
            sum += numbers[i];
        }
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    /* Possible weaknesses found:
     *  Assignment 'end=4', assigned value is 4
     *  Assignment 'start=1', assigned value is 1
     */
    int start = 1, end = 4;

    /* Possible weaknesses found:
     *  Condition 'end<n' is always true
     *  Condition 'end<n' is always true [knownConditionTrueFalse]
     *  Condition 'start<n' is always true
     *  Condition 'start<n' is always true [knownConditionTrueFalse]
     */
    if (start < n && end < n) {
        int result = sum_range(numbers, start, end);
        printf("Sum of the range %d to %d is: %d\n", start, end, result);
    } else {
        printf("Indices out of bounds\n");
    }

    return 0;
}