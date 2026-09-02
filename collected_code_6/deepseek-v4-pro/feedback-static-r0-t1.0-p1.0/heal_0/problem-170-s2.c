#include <stdio.h>
#include <stdlib.h>

int sum_in_range(const int *list, int size, int start, int end, int *result) {
    if (list == NULL || result == NULL) {
        return -1;
    }
    if (size <= 0) {
        return -1;
    }
    if (start < 0 || end < start || end >= size) {
        return -1;
    }
    
    int sum = 0;
    for (int i = start; i <= end; i++) {
        if (sum > 2147483647 - list[i]) {
            return -1;
        }
        sum += list[i];
    }
    
    *result = sum;
    return 0;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int result;
    
    if (sum_in_range(numbers, size, 2, 5, &result) == 0) {
        printf("Sum: %d\n", result);
    } else {
        printf("Error: Invalid range or overflow occurred\n");
    }
    
    return 0;
}