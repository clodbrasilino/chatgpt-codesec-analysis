#include <stdio.h>
#include <stdlib.h>

int sum_range(const int *list, int start, int end) {
    if (list == NULL || start < 0 || (end >= 0 && start > end)) {
        return -1;
    }
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'arr' can be declared as const array [constVariable]
     */
    int arr[] = {1, 2, 3, 4, 5};
    int start = 1, end = 3;

    int result = sum_range(arr, start, end);
    if (result != -1) {
        printf("Sum from index %d to %d is: %d\n", start, end, result);
    } else {
        printf("Invalid range or null array.\n");
    }

    return 0;
}