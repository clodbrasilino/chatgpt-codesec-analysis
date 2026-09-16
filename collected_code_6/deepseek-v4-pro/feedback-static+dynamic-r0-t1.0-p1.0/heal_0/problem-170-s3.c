#include <stdio.h>
#include <stdlib.h>

int sum_in_range(const int *arr, int size, int start, int end) {
    if (arr == NULL || size <= 0) {
        return 0;
    }
    if (start < 0) start = 0;
    if (end >= size) end = size - 1;
    if (start > end) {
        int temp = start;
        start = end;
        end = temp;
    }
    
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += arr[i];
    }
    return sum;
}

int main(void) {
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int result = sum_in_range(numbers, size, 2, 5);
    printf("%d\n", result);
    
    result = sum_in_range(numbers, size, -1, 3);
    printf("%d\n", result);
    
    result = sum_in_range(numbers, size, 7, 12);
    printf("%d\n", result);
    
    result = sum_in_range(numbers, size, 5, 2);
    printf("%d\n", result);
    
    return 0;
}