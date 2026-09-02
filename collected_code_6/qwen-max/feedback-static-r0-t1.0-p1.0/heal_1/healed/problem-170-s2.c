#include <stdio.h>
#include <stdlib.h>

int sum_range(const int *numbers, int start, int end) {
    if (start < 0 || (end >= 0 && end < start) || numbers == NULL) {
        return -1;
    }
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += numbers[i];
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int start = 2;
    int end = 5;
    int result = sum_range(numbers, start, end);
    if (result != -1) {
        printf("Sum between indices %d and %d is: %d\n", start, end, result);
    } else {
        printf("Invalid range or array.\n");
    }
    return 0;
}