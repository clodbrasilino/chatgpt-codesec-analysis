#include <stdio.h>
#include <stdlib.h>

long long sum_range(const int *list, size_t size, size_t start, size_t end) {
    long long sum = 0;
    if (list == NULL) {
        return 0;
    }
    if (start > end) {
        size_t temp = start;
        start = end;
        end = temp;
    }
    if (start >= size) {
        return 0;
    }
    if (end >= size) {
        end = size - 1;
    }
    for (size_t i = start; i <= end; i++) {
        sum += list[i];
    }
    return sum;
}

int main(void) {
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t start = 2;
    size_t end = 6;
    
    long long result = sum_range(list, size, start, end);
    
    printf("%lld\n", result);
    
    return 0;
}